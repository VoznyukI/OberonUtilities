// ViewOberon.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

typedef int LONGINT;
typedef unsigned char CHAR;
typedef signed char SHORTINT;
typedef short int INTEGER;

#define __LSHL(x, n, t)   ((t)((unsigned)(x)<<(n)))
#define __LSHR(x, n, t)   ((t)((unsigned)(x)>>(n)))
#define __LSH(x, n, t)   ((n)>=0? __LSHL(x, n, t): __LSHR(x, -(n), t))

#define __ASH(x, n)   ((n)>=0?__ASHL(x,n):__ASHR(x,-(n)))
#define __ASHL(x, n)   ((long)(x)<<(n))
#define __ASHR(x, n)   ((long)(x)>>(n))


void Kernel_ReadNum( std::ifstream& filetempl, LONGINT *x )
{
	CHAR ch;
	INTEGER n;
	LONGINT y;
	n = 0;
	y = 0;

    //ch = 0xff; //TODO
    char c;
	filetempl.read( &c, 1);
    ch = c;

	while (ch >= 0x80) 
    {
		y += __LSH((LONGINT)ch - 128, n, LONGINT);
		n += 7;

        //ch = 0xff; //TODO
	    filetempl.read( &c, 1);
        ch = c;
	}
	*x = __ASH(__LSHL((LONGINT)ch, 25, LONGINT), n - 25) + y;
}

void Kernel_ReadString( std::ifstream& filetempl, std::string& str )
{
	INTEGER i;
	CHAR ch;
	i = 0;
	for (;;) 
    {
		//ch = 0xff;
        char c;
        filetempl.read( &c, 1);
        ch = c;

		//x[i] = ch;
		//i += 1;

        str.push_back( ch );

		if (ch == 0x00) 
        {
			break;
		}

		//if ( (LONGINT)i == x__len ) 
  //      {
		//	x[i - 1] = 0x00;

		//	do 
  //          {
		//		ch = 0xff;
		//	} 
  //          while (!(ch == 0x00));

		//	break;
		//}
	}
}

static void Kernel_ReadString_0( std::ifstream& filetempl, std::string& str )
{
    str = "";

    CHAR cc = 0x00;

	INTEGER i;
	CHAR ch;
	i = 0;
	for (;;)
    {
		//ch = 0xff;
        char c;
        filetempl.read( &c, 1);
        ch = c;

		if ( ch == 0x00 ) 
        {
			//string[i] = 0x00;
            
            str.push_back( cc );

			return;
		} 
        else if ( ch > 0x7f ) 
        {
			//string[i] = (CHAR)((int)ch - 128);
			//string[i + 1] = 0x00;
            
            str.push_back( ( CHAR )( ( int ) ch - 128 ) );
            str.push_back( cc );

            return;
		}
        else 
        {
			//string[i] = ch;
			//i += 1;

            str.push_back( ch );
        }
	}
}


#pragma pack (push, 1)
union ShortToByte
{
    short s;
    unsigned char c[ 2 ]; 
};

union IntToByte
{
    int i;
    unsigned char c[ 4 ]; 
};
#pragma pack (pop)

void Kernel_ReadLInt( std::ifstream& filetempl, LONGINT& number )
{
    IntToByte i2b;
	CHAR ch;
    for ( int i = 0; i < 4; ++i ) 
    {
        char c;
        filetempl.read( &c, 1);
        ch = c;

        i2b.c[ i ] = ch;
	}

    number = i2b.i;
}

void Kernel_ReadInt( std::ifstream& filetempl, INTEGER& number )
{
    ShortToByte s2b;
	CHAR ch;
    for ( int i = 0; i < 2; ++i ) 
    {
        char c;
        filetempl.read( &c, 1);
        ch = c;

        s2b.c[ i ] = ch;
	}

    number = s2b.s;
}

void ExportRecord( std::ifstream& filetempl, bool is_Exports )
{
    char c;
    unsigned char uc;

    LONGINT oldref_tdentry;
    Kernel_ReadNum( filetempl, &oldref_tdentry );

    if ( oldref_tdentry < 0 )
    {
        if ( is_Exports )
        {
            cout << std::hex << "oldref = 0x" << oldref_tdentry << std::dec;
            cout << "\n";
        }

        return;
    }
    else
    {
        ////tdentry [1X ExportRecord] nofFPs 2 {FP [1X ExportRecord]} 0X
        //tdentry nofFPs 2 [1X ExportRecord] {FP [1X ExportRecord]} 0X

        if ( is_Exports )
        {
            cout << std::hex << "tdentry = 0x" << oldref_tdentry << std::dec;
            cout << "\n";
        }

        INTEGER nofFPs;
        Kernel_ReadInt( filetempl, nofFPs );

        if ( is_Exports )
        {
            cout << std::hex << "nofFPs = 0x" << nofFPs << std::dec;
            cout << "\n";
        }

        c = filetempl.peek( );
        uc = c;
        if ( 0x1 == uc )
        {
	        filetempl.read( &c, 1);
            ExportRecord( filetempl, is_Exports );
        }

        //for ( int i = 0; i < nofFPs; ++i )
        // TODO
        uc = 1;
        while ( 0x0 != uc )
        {
            LONGINT FP;
            Kernel_ReadNum( filetempl, &FP );

            if ( is_Exports )
            {
                cout << std::hex << "FP = 0x" << FP << std::dec;
                cout << "\n";
            }

            c = filetempl.peek( );
            uc = c;
            if ( 0x1 == uc )
            {
	            filetempl.read( &c, 1);
                ExportRecord( filetempl, is_Exports );
            }

            c = filetempl.peek( );
            uc = c;
        }

	    filetempl.read( &c, 1);
        if ( 0x0 != uc )
        {
            cerr << "ExportRecord 0X != 00X";
            cerr << "\n";
            return; 
        }
    }
}

void ExportEntry( std::ifstream& filetempl, bool is_Exports )
{
    char c;
    unsigned char uc;

    LONGINT FP;
    Kernel_ReadNum( filetempl, &FP );

    LONGINT fixup;
    Kernel_ReadNum( filetempl, &fixup );

    if ( is_Exports )
    {
        cout << "ExportEntry: " << "FP = " << FP << "; fixup = " << fixup << std::hex << "; fixup = 0x" << fixup << std::dec;
        cout << "\n";
    }

    //if ( fixup < 0 )
    {
        c = filetempl.peek( );
        uc = c;
        if ( 0x1 == uc )
        {
	        filetempl.read( &c, 1);
            ExportRecord( filetempl, is_Exports );
        }
    }
    //else if ( 0 == fixup )
    //{
    //    if ( is_Exports )
    //    {
    //        cout << "fixup = " << fixup;
    //        cout << "\n";
    //    }
    //    return;
    //}
    //else if ( fixup > 0 )
    //{
    //    if ( is_Exports )
    //    {
    //        //cout << "fixup = " << fixup;
    //        //cout << "\n";
    //    }
    //    return;
    //}
}

void UsedRecord( std::ifstream& filetempl, bool is_Use )
{
    char c;
	filetempl.read( &c, 1);
    unsigned char uc = c;
    if ( 0x1 != uc )
    {
        cerr << "ExportRecord != 01X";
        cerr << "\n";
        return; 
    }

    LONGINT tdentry;
    Kernel_ReadNum( filetempl, &tdentry );
    if ( is_Use )
    {
        cout << "UsedRecord: " << "tdentry = " << tdentry;
        cout << "\n";
    }

    c = filetempl.peek( );
    uc = c;
    if ( 0x0 != uc )
    {
        LONGINT FP;
        Kernel_ReadNum( filetempl, &FP );
        if ( is_Use )
        {
            cout << "UsedRecord: " << std::hex << "FP = 0x" << FP << std::dec;
            cout << "\n";
        }

        std::string name;
        Kernel_ReadString_0( filetempl, name );
        if ( is_Use )
        {
            cout << "UsedRecord: " << "name = " << name;
            cout << "\n";
        }
    }

	filetempl.read( &c, 1);
    uc = c;
    if ( 0x0 != uc )
    {
        cerr << "ExportRecord != 00X";
        cerr << "\n";
        return; 
    }
}

void ReadUse( std::ifstream& filetempl, bool is_Use )
{
    char c;
    unsigned char uc;

    std::string moduleName0;
    Kernel_ReadString_0( filetempl, moduleName0 );
    if ( is_Use )
    {
        cout << "UsedModules: " << "moduleName0 = " << moduleName0;
        cout << "\n";
    }

    // UsedModules 	= 	moduleName0 {UsedVar |UsedProc |UsedType} 0X
    c = filetempl.peek( );
    uc = c;
    while ( 0x0 != uc )
    {
        LONGINT FP;
        Kernel_ReadNum( filetempl, &FP );

        std::string Name0;
        Kernel_ReadString_0( filetempl, Name0 );

        if ( is_Use )
        {
            cout << "UsedModules: " << "FP = " << FP;
            cout << "\n";
        }

        if ( FP > 0 )
        {
            LONGINT fixlist;
            Kernel_ReadNum( filetempl, &fixlist );

            if ( is_Use )
            {
                cout << "UsedModules: " << "varName0  = " << Name0;
                cout << "\n";

                cout << "UsedModules: " << "fixlist  = " << fixlist;
                cout << "\n";
            }

            c = filetempl.peek( );
            uc = c;
            if ( 0x1 == uc )
            {
                UsedRecord( filetempl, is_Use );
            }
        }
        else if ( FP < 0 )
        {
            LONGINT offset;
            Kernel_ReadNum( filetempl, &offset );

            if ( is_Use )
            {
                cout << "UsedModules: " << "procName0  = " << Name0  << std::hex << "; offset = 0x" << offset << std::dec;
                cout << "\n";
            }
        }
        else
        {
            if ( is_Use )
            {
                cout << "UsedModules: " << "typeName0  = " << Name0;
                cout << "\n";
            }

            filetempl.read(  &c, 1 );
            uc = c;
            if ( 0x0 != uc )
            {
                cerr << "typeName0 != 00X";
                cerr << "\n";
                return; 
            }

            c = filetempl.peek( );
            uc = c;
            if ( 0x1 == uc )
            {
                UsedRecord( filetempl, is_Use );
            }
        }

        c = filetempl.peek( );
        uc = c;
    }

	filetempl.read( &c, 1);
    uc = c;
    if ( 0x0 != uc )
    {
        cerr << "ReadUse != 00X";
        cerr << "\n";
        return; 
    }
}

void ReadTypes( std::ifstream& filetempl, bool is_Types )
{
    LONGINT size;
    Kernel_ReadLInt( filetempl, size );

    INTEGER tdaddr;
    Kernel_ReadInt( filetempl, tdaddr );

    INTEGER module;
    Kernel_ReadInt( filetempl, module );

    LONGINT entry;
    Kernel_ReadLInt( filetempl, entry );

    INTEGER nofMethods;
    Kernel_ReadInt( filetempl, nofMethods );

    INTEGER nofInheritedMethods;
    Kernel_ReadInt( filetempl, nofInheritedMethods );

    INTEGER nofNewMethods;
    Kernel_ReadInt( filetempl, nofNewMethods );

    INTEGER nofPointers;
    Kernel_ReadInt( filetempl, nofPointers );

    std::string name;
    Kernel_ReadString( filetempl, name );

    if ( is_Types )
    {
        cout << "TypeEntry: " << "size  = " << size << "; tdaddr = 0x" << std::hex << tdaddr << std::dec << "; module = " << module << "; entry = " << entry;
        cout << "\n";
        cout << "TypeEntry: " << "nofMethods = " << nofMethods << "; nofInheritedMethods = " << nofInheritedMethods << "; nofNewMethods = " << nofNewMethods << "; nofPointers = " << nofPointers;
        cout << "\n";
        cout << "TypeEntry: " << "name = " << name;
        cout << "\n";
    }


    for( int i = 0; i < nofMethods + nofInheritedMethods + nofNewMethods; ++i )
    {
        INTEGER methodNumber;
        Kernel_ReadInt( filetempl, methodNumber );

        INTEGER entryNumber;
        Kernel_ReadInt( filetempl, entryNumber );

        if ( is_Types )
        {
            cout << "Methods: " << "methodNumber  = " << methodNumber << "; entryNumber = " << entryNumber;
            cout << "\n";
        }
    }

    for( int i = 0; i < nofPointers; ++i )
    {
        LONGINT pointerOffset;
        Kernel_ReadLInt( filetempl, pointerOffset );

        if ( is_Types )
        {
            cout << "Pointers: " << "pointerOffset  = " << std::hex << pointerOffset << std::dec;
            cout << "\n";
        }
    }
}

void ReadVariable( std::ifstream& filetempl, bool is_References )
{
    char c;
    unsigned char uc;

	filetempl.read( &c, 1);
    uc = c;
    if ( 0x1 == uc )
    {
        if ( is_References )
        {
            cout << "VarMode = 1X (direct)";
            cout << "\n";
        }
    }
    else if( 0x3 == uc )
    {
        if ( is_References )
        {
            cout << "VarMode = 3X (indirect)";
            cout << "\n";
        }
    }
    //else if( 0x81 <= uc && uc <= 0x8E ) // 81X..8EX
    //{
    //    LONGINT dim;
    //    Kernel_ReadNum( filetempl, &dim );
    //    if ( is_References )
    //    {
    //        cout << "ArrayVar: 0x" << std::hex << uc << std::dec;
    //        cout << "\n";
    //        cout << "ArrayVar: dim = " << dim;
    //        cout << "\n";
    //    }
    //}
    //else if( 0x16 == uc || 0x1D == uc )
    //{
    //    if( 0x16 == uc )
    //    {
    //        if ( is_References )
    //        {
    //            cout << "RecordVar = 16X record";
    //            cout << "\n";
    //        }
    //    }
    //    else if( 0x1D == uc )
    //    {
    //        if ( is_References )
    //        {
    //            cout << "RecordVar = 1DX recordpointer";
    //            cout << "\n";
    //        }
    //    }

    //    LONGINT tdadr;
    //    Kernel_ReadNum( filetempl, &tdadr );
    //    if ( is_References )
    //    {
    //        cout << "RecordVar: tdadr = " << tdadr;
    //        cout << "\n";
    //    }
    //}
    else
    {
        cerr << "ReadVariable";
        cerr << "\n";
        return; 
    }

	filetempl.read( &c, 1);
    uc = c;
    if ( 0x1 <= uc && uc <= 0xf )
    {
        if ( is_References )
        {
            cout << "VarType = 0x" << std::hex << uc << std::dec;
            cout << "\n";
        }
    }
    else if ( 0x81 <= uc && uc <= 0x8E )
    {
        LONGINT dim;
        Kernel_ReadNum( filetempl, &dim );

        if ( is_References )
        {
            cout << "ArrayVar = 0x" << std::hex << uc << std::dec;
            cout << "\n";
            cout << "ArrayVar: dim = " << dim;
            cout << "\n";
        }
    }
    else if ( 0x16 == uc && uc == 0x1D )
    {
        LONGINT tdadr;
        Kernel_ReadNum( filetempl, &tdadr );

        if ( is_References )
        {
            cout << "RecordVar = 0x" << std::hex << uc << std::dec;
            cout << "\n";
            cout << "RecordVar: tdadr = 0c" << std::hex << tdadr << std::dec;
            cout << "\n";
        }
    }

    LONGINT offset;
    Kernel_ReadNum( filetempl, &offset );

    std::string name;
    Kernel_ReadString( filetempl, name );

    if ( is_References )
    {
        cout << "Variable: " << "offset  = 0x" << std::hex << offset << std::dec << "; name  = " << name;
        cout << "\n";
    }
}

void ReadProcRef( std::ifstream& filetempl, bool is_References )
{
    char c;
    unsigned char uc;

	filetempl.read( &c, 1);
    uc = c;
    if ( 0xF9 != uc )
    {
        cerr << "ReadProcRef != 0F9X";
        cerr << "\n";
        return; 
    }

    LONGINT offset;
    Kernel_ReadNum( filetempl, &offset );

    char nofPars;
	filetempl.read( &nofPars, 1);

    if ( is_References )
    {
        cout << "ReadProcRef: " << "offset  = 0x" << std::hex << offset << std::dec << "; nofPars  = " << nofPars;
        cout << "\n";
    }


    char RetType;
	filetempl.read( &RetType, 1);
    uc = RetType;
    if ( 0x00 == uc )
    {
        if ( is_References )
        {
            cout << "RetType = 0X";
            cout << "\n";
        }
    }
    else if ( 0x1 <= uc && uc <= 0xf )
    {
        if ( is_References )
        {
            cout << "VarType = 0x" << std::hex << uc << std::dec;
            cout << "\n";
        }
    }
    else if ( 0x12 == uc || 0x14 == uc || 0x15 == uc )
    {
        if ( is_References )
        {
            cout << "ArrayType = 0x" << std::hex << uc << std::dec;
            cout << "\n";
        }
    }
    else if ( 0x16 == uc )
    {
        if ( is_References )
        {
            cout << "Record";
            cout << "\n";
        }
    }
    else 
    {
        cerr << "RetType ERROR";
        cerr << "\n";
        return; 
    }

    char procLev;
	filetempl.read( &procLev, 1);
    {
        if ( is_References )
        {
            cout << "procLev =  " << procLev;
            cout << "\n";
        }
    }

    char slFlag;
	filetempl.read( &slFlag, 1);
    {
        if ( is_References )
        {
            cout << "slFlag =  " << procLev;
            cout << "\n";
        }
    }

    std::string name;
    Kernel_ReadString( filetempl, name );
    if ( is_References )
    {
        cout << "name =  " << name;
        cout << "\n";
    }

    //ReadVariable( filetempl, is_References );

	c = filetempl.peek( );
    uc = c;
    while ( 0xF9 != uc && ! filetempl.eof() )
    {
        ReadVariable( filetempl, is_References );
	    c = filetempl.peek( );
        uc = c;
    }
}

void ReadReference( std::ifstream& filetempl, bool is_References )
{
    char c;
    unsigned char uc;

	filetempl.read( &c, 1);
    uc = c;
    if ( 0xF8 != uc )
    {
        cerr << "ReadReference != 0F8X";
        cerr << "\n";
        return; 
    }

    LONGINT offset;
    Kernel_ReadNum( filetempl, &offset );

    std::string name;
    Kernel_ReadString( filetempl, name );

    //ReadVariable( filetempl, is_References );

	c = filetempl.peek( );
    uc = c;
    while ( 0xF9 != uc )
    {
        ReadVariable( filetempl, is_References );
	    c = filetempl.peek( );
        uc = c;
    }

    ReadProcRef( filetempl, is_References );

	c = filetempl.peek( );
    uc = c;
    while ( 0xF9 == uc )
    {
        ReadProcRef( filetempl, is_References );

	    c = filetempl.peek( );
        uc = c;
    }
}

void ReadEntries( std::ifstream& filetempl, INTEGER nofEntries, bool is_Entries )
{
    int current = filetempl.tellg();
    if ( is_Entries )
    {
        cout << "Entries: position = 0x" << std::hex << current << std::dec;
        cout << "\n";
    }

    char c;
    unsigned char uc;
	filetempl.read( &c, 1);
    uc = c;
    if ( 0x82 != uc )
    {
        cerr << "Entries != 082X";
        cerr << "\n";
        return; 
    }

    for( int i = 0; i < nofEntries; ++i )
    {
        INTEGER Entry;
        Kernel_ReadInt( filetempl, Entry );

        if ( is_Entries )
        {
            cout << "Entry = 0x" << std::hex << Entry << std::dec;
            cout << "\n";
        }
    }
}

void ReadCommands( std::ifstream& filetempl, INTEGER nofCommands, bool is_Commands )
{
    int current = filetempl.tellg();
    if ( is_Commands )
    {
        cout << "Commands: position = 0x" << std::hex << current << std::dec;
        cout << "\n";
    }

    char c;
    unsigned char uc;
	filetempl.read( &c, 1);
    uc = c;
    if ( 0x83 != uc )
    {
        cerr << "Commands != 083X";
        cerr << "\n";
        return; 
    }

    for( int i = 0; i < nofCommands; ++i )
    {
        std::string cmdName;
        Kernel_ReadString( filetempl, cmdName );

        INTEGER Command;
        Kernel_ReadInt( filetempl, Command );

        if ( is_Commands )
        {
            cout << "Command " << cmdName << " = 0x" << std::hex << Command << std::dec;
            cout << "\n";
        }
    }
}

void ReadPointers( std::ifstream& filetempl, INTEGER nofPointers, bool is_Pointers )
{
    int current = filetempl.tellg();
    if ( is_Pointers )
    {
        cout << "Pointers: position = 0x" << std::hex << current << std::dec;
        cout << "\n";
    }

    char c;
    unsigned char uc;
	filetempl.read( &c, 1);
    uc = c;
    if ( 0x84 != uc )
    {
        cerr << "Pointers != 084X";
        cerr << "\n";
        return; 
    }

    for( int i = 0; i < nofPointers; ++i )
    {
        LONGINT Pointer;
        Kernel_ReadLInt( filetempl, Pointer );
    }
}

void ReadImports( std::ifstream& filetempl, INTEGER nofImports, bool is_Imports )
{
    int current = filetempl.tellg();
    if ( is_Imports )
    {
        cout << "Imports: position = 0x" << std::hex << current << std::dec;
        cout << "\n";
    }

    char c;
    unsigned char uc;
	filetempl.read( &c, 1);
    uc = c;
    if ( 0x85 != uc )
    {
        cerr << "Imports != 085X";
        cerr << "\n";
        return; 
    }

    for( int i = 0; i < nofImports; ++i )
    {
        std::string importName;
        Kernel_ReadString( filetempl, importName );

        if ( is_Imports )
        {
            cout << "Import " << importName;
            cout << "\n";
        }
    }
}

void ReadConstLinks( std::ifstream& filetempl, INTEGER nofVarConsLinks, bool is_VarConsLinks )
{
    if ( is_VarConsLinks )
    {
        int current = filetempl.tellg();
        cout << "VarConsLinks: position = 0x" << std::hex << current << std::dec;
        cout << "\n";
    }

    char c;
    unsigned char uc;
	filetempl.read( &c, 1);
    uc = c;
    if ( 0x8D != uc )
    {
        cerr << "VarConstLinks != 08DX";
        cerr << "\n";
        return; 
    }

    for( int i = 0; i < nofVarConsLinks; ++i )
    {
	    filetempl.read( &c, 1);
        char mod = c;

        INTEGER entry;
        Kernel_ReadInt( filetempl, entry );

        INTEGER count;
        Kernel_ReadInt( filetempl, count );

        if ( is_VarConsLinks )
        {
            cout << std::hex << "VarConstLink: mod = 0x" << (int)mod << "; entry = 0x" << entry << "; count = 0x" << count << "; offset =";
        }

        for( int j = 0; j < count; ++j )
        {
            INTEGER offset;
            Kernel_ReadInt( filetempl, offset );

            if ( is_VarConsLinks )
                cout << " 0x" << offset << "; ";
        }

        if ( is_VarConsLinks )
            cout << std::dec << "\n";
    }
}

void ReadLinks( std::ifstream& filetempl, INTEGER nofLinks, bool is_Links )
{
    if ( is_Links )
    {
        int current = filetempl.tellg();
        cout << "Links: position = 0x" << std::hex << current << std::dec;
        cout << "\n";
    }

    char c;
    unsigned char uc;
	filetempl.read( &c, 1);
    uc = c;
    if ( 0x86 != uc )
    {
        cerr << "Links != 086X";
        cerr << "\n";
        return; 
    }

    for( int i = 0; i < nofLinks; ++i )
    {
	    filetempl.read( &c, 1);
        char mod = c;

	    filetempl.read( &c, 1);
        char entry = c;

        INTEGER offset;
        Kernel_ReadInt( filetempl, offset );

        if ( is_Links )
        {
            cout << std::hex << "LinkEntry: mod = 0x" << (int)mod << "; entry = 0x" << (int)entry << "; offset = 0x" << offset;
            cout << std::dec << "\n";
        }
    }
}

void ReadConsts( std::ifstream& filetempl, INTEGER constSize, bool is_Consts )
{
    if ( is_Consts )
    {
        int current = filetempl.tellg();
        cout << "Consts: position = 0x" << std::hex << current << std::dec;
        cout << "\n";
        cout << "constSize= " << constSize;
        cout << "\n";
    }

    char c;
    unsigned char uc;
	filetempl.read( &c, 1);
    uc = c;
    if ( 0x87 != uc )
    {
        cerr << "Consts != 087X";
        cerr << "\n";
        return; 
    }

    for( int i = 0; i < constSize; ++i )
    {
	    filetempl.read( &c, 1);
        uc = c;
    }
}

void ReadExports( std::ifstream& filetempl, bool is_Exports )
{
    int current = filetempl.tellg();
    if ( is_Exports )
    {
        cout << "Exports: position = 0x" << std::hex << current << std::dec;
        cout << "\n";
    }

    char c;
    unsigned char uc;

	filetempl.read( &c, 1);
    uc = c;
    if ( 0x88 != uc )
    {
        cerr << "Exports != 088X";
        cerr << "\n";
        return; 
    }

    INTEGER nofExports;
    Kernel_ReadInt( filetempl, nofExports );

    if ( is_Exports )
    {
        cout << "Exports: nofExports = " << nofExports;
        cout << "\n";
    }

    for( int i = 0; i < nofExports; ++i )
    {
        ExportEntry( filetempl, is_Exports );
    }

	filetempl.read( &c, 1);
    uc = c;
    if ( 0x00 != uc )
    {
        cerr << "Exports end != 00X";
        cerr << "\n";
        return; 
    }
}

void ReadCode( std::ifstream& filetempl, INTEGER codeSize, bool is_Code )
{
    if ( is_Code )
    {
        int current = filetempl.tellg();
        cout << "Code: position = 0x" << std::hex << current << std::dec;
        cout << "\n";
        cout << "codeSize= " << codeSize;
        cout << "\n";
    }

    char c;
    unsigned char uc;

	filetempl.read( &c, 1);
    uc = c;
    if ( 0x89 != uc )
    {
        cerr << "Code != 089X";
        return; 
    }

    for( int i = 0; i < codeSize; ++i )
    {
	    filetempl.read( &c, 1);
        uc = c;
    }
}

void ReadAllUse( std::ifstream& filetempl, bool is_Use )
{
    int current = filetempl.tellg();
    if ( is_Use )
    {
        cout << "Use position = 0x" << std::hex << current << std::dec;
        cout << "\n";
    }

    char c;
    unsigned char uc;

	filetempl.read( &c, 1);
    uc = c;
    if ( 0x8A != uc )
    {
        cerr << "Use != 08AX";
        cerr << "\n";
        return; 
    }

    c = filetempl.peek( );
    uc = c;
    while ( 0x0 != uc )
    {
        ReadUse( filetempl, is_Use );

        c = filetempl.peek( );
        uc = c;
    }

    // Use 		= 	08AX {UsedModules} 0X
	filetempl.read( &c, 1);
    uc = c;
    if ( 0x00 != uc )
    {
        cerr << "ReadUse != 00X";
        cerr << "\n";
        return; 
    }
}

void ReadAllTypes( std::ifstream& filetempl, INTEGER nofTypes, bool is_Types )
{
    int current = filetempl.tellg();
    if ( is_Types )
    {
        cout << "Types position = 0x" << std::hex << current << std::dec;
        cout << "\n";
    }

    char c;
    unsigned char uc;

	filetempl.read( &c, 1);
    uc = c;
    if ( 0x8B != uc )
    {
        cerr << "Types != 8BX";
        cerr << "\n";
        return; 
    }
    for( int i = 0; i < nofTypes; ++i )
    {
        ReadTypes( filetempl, is_Types );
    }
}

void ReadAllReferences( std::ifstream& filetempl, bool is_References )
{
    int current = filetempl.tellg();
    if ( is_References )
    {
        cout << "References position = 0x" << std::hex << current << std::dec;
        cout << "\n";
    }

    char c;
    unsigned char uc;

	filetempl.read( &c, 1);
    uc = c;
    if ( 0x8C != uc )
    {
        cerr << "Use != 8CX";
        cerr << "\n";
        return; 
    }
    ReadReference( filetempl, is_References );
}

////////////////////////

//Section Delimiters 	  	 
const unsigned char SFconst_37X = 0x37;
const unsigned char SFvar_38X =  0x38;
const unsigned char SFlproc_39X =  0x39;
const unsigned char SFxproc_3AX =  0x3A;
const unsigned char SFoperator_3BX =  0x3B;
const unsigned char SFtproc_3CX =  0x3C;
const unsigned char SFalias_3DX =  0x3D;
const unsigned char SFtyp_3EX =  0x3E;
const unsigned char SFend_3FX =  0x3F;

void SFConst( std::ifstream& filetempl )
{
}

void ParList( std::ifstream& filetempl, bool is_Symbols );

void Structure( std::ifstream& filetempl, bool is_Symbols )
{
//Structure 	= 	Basic | UserStr | oldstr | modno (name0 | 0X oldimpstrn)
//Basic 	= 	SFtypBool .. SFtypNilTyp
//UserStr 	= 	[SFinvisible][SFsysflag flag] UserStr2
//UserStr2 	= 	(SFtypOpenArr | SFtypDynArr) Structure name0
//  	| 	SFtypArray Structure name0 size
//  	| 	SFtypPointer Structure name0
//  	| 	SFtypProcTyp Structure name0 ParList
//  	| 	SFtypRecord Structure name0 prio flags RecStr

//SFtypBool 	= 	01X
//SFtypChar 	= 	02X
//SFtypSInt 	= 	03X
//SFtypInt 	    = 	04X
//SFtypLInt 	= 	05X
//SFtypHInt 	= 	06X
//SFtypReal 	= 	07X
//SFtypLReal 	= 	08X
//SFtypSet 	    = 	09X
//SFtypString 	= 	0AX
//SFtypNoTyp 	= 	0BX
//SFtypNilTyp 	= 	0CX


    char c;
    unsigned char uc;

	c = filetempl.peek( );
    unsigned char peek_uc = c;

    if ( 0x01 <= peek_uc && peek_uc <= 0x0C )  //Basic
    {
        filetempl.read( &c, 1);
        uc = c;
        switch ( uc )
        {
            //Basic
        case 0x01 : // SFtypBool
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypBool";
                cout << "\n";
            }
            break;
        case 0x02 : // SFtypChar
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypChar";
                cout << "\n";
            }
            break;
        case 0x03 : // SFtypSInt
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypSInt";
                cout << "\n";
            }
            break;
        case 0x04 : // SFtypInt
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypInt";
                cout << "\n";
            }
            break;
        case 0x05 : // SFtypLInt
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypLInt";
                cout << "\n";
            }
            break;
        case 0x06 : // SFtypHInt
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypHInt";
                cout << "\n";
            }
            break;
        case 0x07 : // SFtypReal
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypReal";
                cout << "\n";
            }
            break;
        case 0x08 : // SFtypLReal
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypLReal";
                cout << "\n";
            }
            break;
        case 0x09 : // SFtypSet
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypSet";
                cout << "\n";
            }
            break;
        case 0x0A : // SFtypString
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypString";
                cout << "\n";
            }
            break;
        case 0x0B : // SFtypNoTyp
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypNoTyp";
                cout << "\n";
            }
            break;
        case 0x0C : // SFtypBool
            if ( is_Symbols )
            {
                cout << "Structure Basic = SFtypBool";
                cout << "\n";
            }
            break;
        }
    } //UserStr : [SFinvisible][SFsysflag flag] UserStr2
    else if ( 0x35 == peek_uc || 0x34 == peek_uc || 0x2E == peek_uc || 0x2F == peek_uc ) 
    {
        if ( 0x35 == peek_uc ) // [SFinvisible]
        {
            filetempl.read( &c, 1);

            if ( is_Symbols )
            {
                cout << "Structure UserStr = SFinvisible";
                cout << "\n";
            }
        }
        else if ( 0x34 == peek_uc ) // [SFsysflag flag]
        {
            filetempl.read( &c, 1);

            LONGINT flag;
            Kernel_ReadNum( filetempl, &flag );

            if ( is_Symbols )
            {
                cout << "Structure SFsysflag flag = " << flag;
                cout << "\n";
            }
        }
    }
    else if ( 0x2E == peek_uc || 0x2F == peek_uc || 0x30 == peek_uc || 0x31 == peek_uc || 0x33 == peek_uc || 0x32 == peek_uc ) 
    {
        //TODO
        //UserStr2 	= (SFtypOpenArr | SFtypDynArr)  Structure name0
        //  	                    | SFtypArray    Structure name0 size
        //  	                    | SFtypPointer  Structure name0
        //  	                    | SFtypProcTyp  Structure name0 ParList
        //  	                    | SFtypRecord   Structure name0 prio flags RecStr

        filetempl.read( &c, 1);
        uc = c;
           
        if ( is_Symbols && uc == 0x2E )
        {
            cout << "Structure UserStr2  = SFtypOpenArr";
            cout << "\n";
        }
        else if ( is_Symbols && uc == 0x2F )
        {
            cout << "Structure UserStr2  = SFtypDynArr";
            cout << "\n";
        }
        else if ( is_Symbols && uc == 0x30 )
        {
            cout << "Structure UserStr2  = SFtypArray";
            cout << "\n";
        }
        else if ( is_Symbols && uc == 0x31 )
        {
            cout << "Structure UserStr2  = SFtypPointer";
            cout << "\n";
        }
        else if ( is_Symbols && uc == 0x33 )
        {
            cout << "Structure UserStr2  = SFtypProcTyp";
            cout << "\n";
        }
        else if ( is_Symbols && uc == 0x32 )
        {
            cout << "Structure UserStr2  = SFtypRecord";
            cout << "\n";
        }

        Structure( filetempl, is_Symbols );

        std::string name0;
        Kernel_ReadString( filetempl, name0 );

        if ( is_Symbols  )
        {
            cout << "Structure name0  = " << name0;
            cout << "\n";
        }

        if ( uc == 0x30 ) // SFtypArray
        {
            LONGINT size;
            Kernel_ReadNum( filetempl, &size );

            if ( is_Symbols  )
            {
                cout << "Structure SFtypArray size  = " << size;
                cout << "\n";
            }
        }

        if ( uc == 0x33 ) // SFtypProcTyp
        {
            ParList( filetempl, is_Symbols );
        }

    }
    else
    {
        cerr << "SymFile file: Structure error\n";
        return; 
    }
}

void ParList( std::ifstream& filetempl, bool is_Symbols )
{
//ParList 	= 	{[SFvar] Structure name0} SFEnd
	
    char c;
    unsigned char uc;

    c = filetempl.peek( );
    unsigned char peek_uc = c;

    while ( SFend_3FX != peek_uc ) //SFend
    {
        if ( SFvar_38X == peek_uc ) // SFvar
        {
	        filetempl.read( &c, 1);

            if ( is_Symbols )
            {
                cout << "ParList SFvar";
                cout << "\n";
            }
        }

        int current = filetempl.tellg(); //TODO

        Structure( filetempl, is_Symbols );

        std::string name0;
        Kernel_ReadString_0( filetempl, name0 );

        if ( is_Symbols  )
        {
            cout << "Structure name0  = " << name0;
            cout << "\n";
        }

        c = filetempl.peek( );
        peek_uc = c;
    }

	filetempl.read( &c, 1);
    uc = c;

    if ( SFend_3FX != uc ) // SFend
    {
        cerr << "SymFile file: SFend != 0x3F\n";
        return; 
    }
}

void SFvar( std::ifstream& filetempl, bool is_Symbols )
{
//  	  	[SFvar {[SFobjflag flag 1] [SFreadonly] Structure name0}]

    char c;
    unsigned char uc;

    c = filetempl.peek( );
    uc = c;
    if ( 0x37 == uc ) // SFobjflag
    {
	    filetempl.read( &c, 1);
        char flag = c;
    }
    
    if ( 0x36 == uc ) // SFreadonly
    {
	    filetempl.read( &c, 1);
    }

    Structure( filetempl, is_Symbols );

    std::string name0;
    Kernel_ReadString_0( filetempl, name0 );
}

void SFlproc( std::ifstream& filetempl )
{
    cerr << "SymFile file: SFlproc not defind \n";
}

void SFxproc( std::ifstream& filetempl, bool is_Symbols )
{
// 	[ SFxproc {[SFobjflag flag 1] Structure name0 ParList} ]

    int current = filetempl.tellg();
    if ( is_Symbols )
    {
        cout << "SFxproc position = 0x" << std::hex << current << std::dec;
        cout << "\n";
    }

    char c;
    unsigned char uc;

    c = filetempl.peek( );
    uc = c;

    while ( SFoperator_3BX != uc && SFtproc_3CX != uc && SFalias_3DX != uc && SFtyp_3EX != uc && SFend_3FX != uc )
    {
        if ( 0x37 == uc ) // SFobjflag
        {
	        filetempl.read( &c, 1);
            char flag = c;
        }
    
        Structure( filetempl, is_Symbols );

        std::string name0;
        Kernel_ReadString_0( filetempl, name0 );

        if ( is_Symbols )
        {
            cout << "SFxproc name0 = " << name0;
            cout << "\n";
        }

        current = filetempl.tellg(); //TODO

        ParList( filetempl, is_Symbols );

        c = filetempl.peek( );
        uc = c;
    }
}

void SFoperator( std::ifstream& filetempl )
{
    cerr << "SymFile file: SFoperator not defind \n";
}

void SFalias( std::ifstream& filetempl )
{
    cerr << "SymFile file: SFalias not defind \n";
}

void SFtyp( std::ifstream& filetempl )
{
    cerr << "SymFile file: SFtyp not defind \n";
}

int main(int argc, char* argv[])
{
    if ( argc < 2 )
        return 1; 

    std::string file = argv[ 1 ];
	std::ifstream filetempl( file.c_str(), std::ios_base::in | std::ios_base::binary ); 
    if ( ! filetempl.is_open() )
    {
        cerr << "File is not opened";
        cerr << "\n";
        return 1; 
    }

//ObjectFile 	= 	OFTag OFVersion symfilesize SymbolFile
//  	  	        Header Entries Commands Pointers Imports VarConsLinks Links
//  	  	        Consts Exports Code Use Types References
//OFTag 	    = 	0BBX
//OFVersion 	= 	0AFX

    bool is_Header = true;
    bool is_Symbols = true;
    bool is_Entries = true;
    bool is_Commands = true;
    bool is_Pointers = true;
    bool is_Imports = true;
    bool is_VarConsLinks = true;
    bool is_Links = true;
    bool is_Consts = true;
    bool is_Exports = true;
    bool is_Code = true;
    bool is_Use = true;
    bool is_Types = true;
    bool is_References = true; //TODO

    if ( argc >= 3 )
    {
        std::string option = argv[ 2 ];

        if ( option == "is_All" )
        {
            is_Header = false;
            is_Symbols = false;
            is_Entries = false;
            is_Commands = false;
            is_Pointers = false;
            is_Imports = false;
            is_VarConsLinks = false;
            is_Links = false;
            is_Consts = false;
            is_Exports = false;
            is_Code = false;
            is_Use = false;
            is_Types = false;
            is_References = false;
        }
    }

    char c;
	filetempl.read( &c, 1);
    unsigned char uc = c;
    if ( 0xBB != uc )
    {
        cerr << "OFTag != 0BBX";
        cerr << "\n";
        return 1; 
    }

	filetempl.read( &c, 1);
    uc = c;
    if ( 0xAF != uc )
    {
        cerr << "OFVersion != 0AFX";
        cerr << "\n";
        return 1; 
    }

    int symfilesize;
    Kernel_ReadNum( filetempl, &symfilesize );
    if ( is_Header )
    {
        cout << "symfilesize = " << symfilesize;
        cout << "\n";
    }

    // overseek SymbolFile;
    filetempl.seekg( symfilesize, ios_base::cur );

///////////
//SymFile 	= 	{modname0}
//  	  	[SFConst {Structure name0 val}]
//  	  	[SFvar {[SFobjflag flag 1] [SFreadonly] Structure name0}]
//  	  	[SFlproc {Structure name0 ParList}]
//  	  	[SFxproc {[SFobjflag flag 1] Structure name0 ParList}]
//  	  	[SFoperator {Structure name0 ParList}]
//  	  	[SFalias {Structure name0}]
//  	  	[SFtyp {Structure}]
//  	  	SFEnd
//  	  	 
//ParList 	= 	{[SFvar] Structure name0} SFEnd
//Structure 	= 	Basic | UserStr | oldstr | modno (name0 | 0X oldimpstrn)
//Basic 	= 	SFtypBool .. SFtypNilTyp
//UserStr 	= 	[SFinvisible][SFsysflag flag] UserStr2
//UserStr2 	= 	(SFtypOpenArr | SFtypDynArr) Structure name0
//  	| 	SFtypArray Structure name0 size
//  	| 	SFtypPointer Structure name0
//  	| 	SFtypProcTyp Structure name0 ParList
//  	| 	SFtypRecord Structure name0 prio flags RecStr
//RecDef 	= 	{ FieldDef }[SFtproc {MethodDef}] SFend
//FieldDef 	= 	[SFreadonly] Structure name0
//MethodDef 	= 	Structure name0 ParList 

//Basic Types Encoding 	  	 
//SFtypBool 	= 	01X
//SFtypChar 	= 	02X
//SFtypSInt 	= 	03X
//SFtypInt 	= 	04X
//SFtypLInt 	= 	05X
//SFtypHInt 	= 	06X
//SFtypReal 	= 	07X
//SFtypLReal 	= 	08X
//SFtypSet 	= 	09X
//SFtypString 	= 	0AX
//SFtypNoTyp 	= 	0BX
//SFtypNilTyp 	= 	0CX
//SFtypByte 	= 	0DX
//SFtypSptr 	= 	0EX
//  	  	 
//Composed Types 	  	 
//SFtypOpenArr 	= 	2EX
//SFtypDynArr 	= 	2FX
//SFtypArray 	= 	30X
//SFtypPointer 	= 	31X
//SFtypRecord 	= 	32X
//SFtypProcTyp 	= 	33X
//  	  	 
//Flags 	  	 
//SFsysflag 	= 	34X
//SFinvisible 	= 	35X
//SFreadonly 	= 	36X
//SFobjflag 	= 	37X
//  	  	 
//Section Delimiters 	  	 
//SFconst 	= 	37X
//SFvar 	= 	38X
//SFlproc 	= 	39X
//SFxproc 	= 	3AX
//SFoperator 	= 	3BX
//SFtproc 	= 	3CX
//SFalias 	= 	3DX
//SFtyp 	= 	3EX
//SFend 	= 	3FX

 //   std::string modname0;
 //   Kernel_ReadString( filetempl, modname0 );
 //   if ( is_Symbols )
 //   {
 //       cout << "SymFile modname0 " << modname0;
 //       cout << "\n";
 //   }

	//filetempl.read( &c, 1);
 //   uc = c;
 //   while ( SFend_3FX != uc ) //SFend
 //   {
 //       switch ( uc )
 //       {
 //       case 0x37 :
 //           SFConst( filetempl );
 //           break;
 //       case SFvar_38X :
 //           SFvar( filetempl, is_Symbols );
 //           break;
 //       case SFlproc_39X :
 //           SFlproc( filetempl );
 //           break;
 //       case SFxproc_3AX :
 //           SFxproc( filetempl, is_Symbols );
 //           break;
 //       case SFoperator_3BX :
 //           SFoperator( filetempl );
 //           break;
 //       case SFalias_3DX :
 //           SFalias( filetempl );
 //           break;
 //       case SFtyp_3EX :
 //           SFtyp( filetempl );
 //           break;
 //       default :
 //           cerr << "SymFile file: tag error\n";
 //           return 1; 
 //           //break;
 //       }

	//    filetempl.read( &c, 1);
 //       uc = c;
 //   }

///////////////


//Header 	= 	refSize 4 nofEntries 2 nofCommands 2 nofPointers 2
//  	  	    nofTypes 2 nofImports 2 nofVarConsLinks 2 nofLinks 2
//  	  	    dataSize 4 constSize 2 codeSize 2 moduleName

    LONGINT refSize;
    Kernel_ReadLInt( filetempl, refSize );
    if ( is_Header )
    {
        cout << "refSize = " << refSize;
        cout << "\n";

        if ( refSize < 0 )
        {
            cerr << "refSize < 0";
            cerr << "\n";
            return 1; 
        }
    }

    INTEGER nofEntries;
    Kernel_ReadInt( filetempl, nofEntries );
    if ( is_Header )
    {
        cout << "nofEntries = " << nofEntries;
        cout << "\n";

        if ( nofEntries < 0 )
        {
            cerr << "nofEntries < 0";
            cerr << "\n";
            return 1; 
        }
    }

    INTEGER nofCommands;
    Kernel_ReadInt( filetempl, nofCommands );
    if ( is_Header )
    {
        cout << "nofCommands = " << nofCommands;
        cout << "\n";

        if ( nofCommands < 0 )
        {
            cerr << "nofCommands < 0";
            cerr << "\n";
            return 1; 
        }
    }

    INTEGER nofPointers;
    Kernel_ReadInt( filetempl, nofPointers );
    if ( is_Header )
    {
        cout << "nofPointers = " << nofPointers;
        cout << "\n";

        if ( nofPointers < 0 )
        {
            cerr << "nofPointers < 0";
            cerr << "\n";
            return 1; 
        }
    }

    INTEGER nofTypes;
    Kernel_ReadInt( filetempl, nofTypes );
    if ( is_Header )
    {
        cout << "nofTypes = " << nofTypes;
        cout << "\n";

        if ( nofTypes < 0 )
        {
            cerr << "nofTypes < 0";
            cerr << "\n";
            return 1; 
        }
    }

    INTEGER nofImports;
    Kernel_ReadInt( filetempl, nofImports );
    if ( is_Header )
    {
        cout << "nofImports = " << nofImports;
        cout << "\n";

        if ( nofImports < 0 )
        {
            cerr << "nofImports < 0";
            cerr << "\n";
            return 1; 
        }
    }

    INTEGER nofVarConsLinks;
    Kernel_ReadInt( filetempl, nofVarConsLinks );
    if ( is_Header )
    {
        cout << "nofVarConsLinks = " << nofVarConsLinks;
        cout << "\n";

        if ( nofVarConsLinks < 0 )
        {
            cerr << "nofVarConsLinks < 0";
            cerr << "\n";
            return 1; 
        }
    }

    INTEGER nofLinks;
    Kernel_ReadInt( filetempl, nofLinks );
    if ( is_Header )
    {
        cout << "nofLinks = " << nofLinks;
        cout << "\n";

        if ( nofLinks < 0 )
        {
            cerr << "nofLinks < 0";
            cerr << "\n";
            return 1; 
        }
    }

    LONGINT dataSize;
    Kernel_ReadLInt( filetempl, dataSize );
    if ( is_Header )
    {
        cout << "dataSize = " << dataSize;
        cout << "\n";

        if ( dataSize < 0 )
        {
            cerr << "dataSize < 0";
            cerr << "\n";
            return 1; 
        }
    }

    INTEGER constSize;
    Kernel_ReadInt( filetempl, constSize );
    if ( is_Header )
    {
        cout << "constSize = " << constSize;
        cout << "\n";

        if ( constSize < 0 )
        {
            cerr << "constSize < 0";
            cerr << "\n";
            return 1; 
        }
    }

    INTEGER codeSize;
    Kernel_ReadInt( filetempl, codeSize );
    if ( is_Header )
    {
        cout << "codeSize = " << codeSize;
        cout << "\n";

        if ( codeSize < 0 )
        {
            cerr << "codeSize < 0";
            cerr << "\n";
            return 1; 
        }
    }

    std::string moduleName;
    Kernel_ReadString( filetempl, moduleName );
    if ( is_Header )
    {
        cout << "moduleName = " << moduleName;
        cout << "\n";
    }

//Entries 	= 	82X {entryOffset 2} 
    ReadEntries( filetempl, nofEntries, is_Entries );

//Commands 	= 	83X {cmdName cmdOffset 2 }
    ReadCommands( filetempl, nofCommands, is_Commands );

//Pointers 	= 	84X {pointerOffset 4 }
    ReadPointers( filetempl, nofPointers, is_Pointers );

//Imports 	= 	85X {moduleName} 
    ReadImports( filetempl, nofImports, is_Imports );

//VarConstLinks 	= 	8DX { VarConstLinkEntry }
//VarConstLinkEntry 	= 	mod 1 entry 2 count 2 {offset 2}
    ReadConstLinks( filetempl, nofVarConsLinks, is_VarConsLinks );

//Links 	= 	86X {LinkEntry}
//LinkEntry 	= 	mod 1 entry 1 offset 2
    ReadLinks( filetempl, nofLinks, is_Links );

//Consts 	= 	87X {char 1}
    ReadConsts( filetempl, constSize, is_Consts );

//Exports 	= 	88X nofExports 2 {ExportEntry} 0X
//ExportEntry 	= 	FP fixup [1X ExportRecord]
//ExportRecord 	= 	oldref    | 	tdentry [1X ExportRecord] nofFPs 2 {FP [1X ExportRecord]} 0X
    ReadExports( filetempl, is_Exports );

//Code 	= 	89X {char 1}
    ReadCode( filetempl, codeSize, is_Code );

//Use 	        = 	08AX {UsedModules} 0X
//UsedModules 	= 	moduleName0 {UsedVar |UsedProc |UsedType} 0X
//UsedVar 	    = 	FP varName0 fixlist [1X UsedRecord]
//UsedProc 	    = 	FP procName0 offset
//UsedType 	    = 	FP typeName0 0X [1X UsedRecord]
//UsedRecord 	= 	tdentry [FP "@"] 0X
    ReadAllUse( filetempl, is_Use );

//Types 	= 	8BX {TypeEntry}
//TypeEntry 	= 	size 4 tdaddr 2 Base Count name Methods Pointers
//Base 	= 	module 2 entry 4
//Count 	= 	nofMethods 2 nofInheritedMethods 2 nofNewMethods 2 nofPointers 2
//Methods 	= 	{methodNumber 2 entryNumber 2}
//Pointers 	= 	{pointerOffset 4} 
    ReadAllTypes( filetempl, nofTypes, is_Types );

//Reference 	= 	8CX BodyRef {ProcRef}
//BodyRef 	= 	0F8X offset name {Variable}
//ProcRef 	= 	0F9X offset nofPars 1 RetType 1 procLev 1 slFlag 1 name {Variable}
//RetType 	= 	0X | VarType | ArrayType | Record
//ArrayType 	= 	12X | 14X | 15X. (* static, dynamic, open *)
//Record 	= 	16X
//Variable 	= 	VarMode ( VarType | ArrayVar | RecordVar ) offset name
//VarMode 	= 	1X | 3X. (* direct, indirect *)
//RecordVar 	= 	(16X|1DX) tdadr (* record, recordpointer *)
//  	=
//ArrayVar 	= 	81X..8EX dim
//VarType 	= 	1X ..0FX
//  	  	(*byte, boolean, char, shortint, integer, longint
//  	  	real, longreal, set, , , , ptr, proc, string *)
    ReadAllReferences( filetempl, is_References );

 //   filetempl.seekg(0,ios_base::end);
    if ( ! filetempl.eof() )
    {
        cerr << "eof is not found ";
        cerr << "\n";
        return 1; 
    }

    cout << "Congratulation. It's OK!";
    cout << "\n";

    return 0;
}

////////////////////////


//name 	            write 0X terminated string
//name0 	        write string with 0X compression
//num 1 	        write num as 1 byte value
//num 2 	        write num as 2 byte value
//num 4 	        write num as 4 byte value
//num 	            write num as compressed value

//ObjectFile 	= 	OFTag OFVersion symfilesize SymbolFile
//  	  	        Header Entries Commands Pointers Imports VarConsLinks Links
//  	  	        Consts Exports Code Use Types References
//OFTag 	    = 	0BBX
//OFVersion 	= 	0AFX

//Header 	= 	refSize 4 nofEntries 2 nofCommands 2 nofPointers 2
//  	  	nofTypes 2 nofImports 2 nofVarConsLinks 2 nofLinks 2
//  	  	dataSize 4 constSize 2 codeSize 2 moduleName

//Entries 	= 	82X {entryOffset 2} 
//Commands 	= 	83X {cmdName cmdOffset 2 }
//Pointers 	= 	84X {pointerOffset 4 }
//Imports 	= 	85X {moduleName} 

//VarConstLinks 	= 	8DX { VarConstLinkEntry }
//VarConstLinkEntry 	= 	mod 1 entry 2 count 2 {offset 2}

//Links 	= 	86X {LinkEntry}
//LinkEntry 	= 	mod 1 entry 1 offset 2

//Consts 	= 	87X {char 1}

//Exports 	= 	88X nofExports 2 {ExportEntry} 0X
//ExportEntry 	= 	FP fixup [1X ExportRecord]
//ExportRecord 	= 	oldref    | 	tdentry [1X ExportRecord] nofFPs 2 {FP [1X ExportRecord]} 0X

//Code 	= 	89X {char 1}

//Use 	        =   08AX {UsedModules} 0X
//UsedModules 	= 	moduleName0 {UsedVar |UsedProc |UsedType} 0X
//UsedVar 	    = 	FP varName0 fixlist [1X UsedRecord]             // FP > 0
//UsedProc 	    = 	FP procName0 offset                             // FP < 0
//UsedType 	    = 	FP typeName0 0X [1X UsedRecord]                 // FP == 0
//UsedRecord 	= 	tdentry [FP "@"] 0X

//Types 	    = 	8BX {TypeEntry}
//TypeEntry 	= 	size 4 tdaddr 2 Base Count name Methods Pointers
//Base 	        = 	module 2 entry 4
//Count 	    = 	nofMethods 2 nofInheritedMethods 2 nofNewMethods 2 nofPointers 2
//Methods 	    = 	{methodNumber 2 entryNumber 2}
//Pointers 	    = 	{pointerOffset 4} 

//Reference 	= 	8CX BodyRef {ProcRef}
//BodyRef 	    = 	0F8X offset name {Variable}
//ProcRef 	    = 	0F9X offset nofPars 1 RetType 1 procLev 1 slFlag 1 name {Variable}
//RetType 	    = 	0X | VarType | ArrayType | Record
//ArrayType 	= 	12X | 14X | 15X. (* static, dynamic, open *)
//Record 	    = 	16X
//Variable 	    = 	VarMode ( VarType | ArrayVar | RecordVar ) offset name
//VarMode 	    = 	1X | 3X. (* direct, indirect *)
//RecordVar 	= 	(16X|1DX) tdadr (* record, recordpointer *)
//  	        =
//ArrayVar 	    = 	81X..8EX dim
//VarType 	    = 	1X ..0FX
//  	  	(*byte, boolean, char, shortint, integer, longint
//  	  	real, longreal, set, , , , ptr, proc, string *)

//EUEnd = 0; 
//EURecord = 1; 
//EUobjScope = 0; 
//EUrecScope = 1;  
//EUerrScope = -1;
//EUProcFlag = 80000000H; 

