Make it as simple as possible, but not simpler.
A. Einstein

# 1 . Introduction

For educational and informational purposes, my attention was attracted to the project [Oberon Niklaus Wirth](https://en.wikipedia.org/wiki/Oberon_(operating_system)). [Wirth's thesis on the simplicity and reliability of software](https://www.amazon.com/School-Niklaus-Wirth-Art-Simplicity/dp/1558607234) is very attractive to me and is an example to follow.

For a better understanding of programming and computer, I had the intention to get my own implementation of this project using Windows. I had the book Wirth, N., Gutknecht, J. ["Project Oberon: The Design of an Operating System and Compiler" (1992)](https://www.inf.ethz.ch/personal/wirth/ProjectOberon1992.pdf) and [source codes attached to it](https://github.com/Spirit-of-Oberon/ProjectOberonV4).

Project Oberon consists of the same name of the operating system and programming language.  (Wirth needed to create a new language for this project!)

# 2. Methods of implementation

How to repeat the process of launching the operating system on an empty machine (the process of how a system is started), working on Windows? How to compile the source code written in the Oberon language? How to build a boot disk and run it at least on a virtual machine?

The basis for the implementation of such a project is a compiler that runs on one operating system (in my case it is Windows) and is able to generate object files for another operating system (for Oberon). This process is called cross-compilation in the compilation theory.

Finding a compiler for this task turned out to be intriguing task. On the one hand, there are many compilers and translators for Oberon:
* Oberon Portable Compiler and Linker: https://github.com/AlexIljin/OPCL, https://github.com/Oleg-N-Cher/OPCL, http://sourceforge.net/projects/opcl/
* Optimizing Oberon-2 Compiler: https://github.com/AlexIljin/oo2c, http://ooc.sourceforge.net/index.html, https://github.com/Spirit-of-Oberon/oo2c, http://ooc.sourceforge.net/index.html, https://www.gsp.com/cgi-bin/man.cgi?section=1&topic=oo2c, https://sourceforge.net/projects/ooc/
* Ofront is an Oberon-2 to C translator: https://github.com/jtempl/ofront, https://github.com/Oleg-N-Cher/Ofront, http://www.software-templ.com/shareware.html, https://github.com/Oleg-N-Cher/OfrontPlus,  https://sourceforge.net/projects/ofrontplus/
* OBNC is a compiler for Niklaus Wirth’s programming language Oberon: http://miasap.se/obnc/
* pOt - Oberon to C translator: https://github.com/dtolpin/pOt, https://github.com/Spirit-of-Oberon/pOt
* Pow! is a software development environment for Microsoft Windows: https://github.com/Spirit-of-Oberon/POW, https://archive.codeplex.com/?p=pow, http://www.fim.uni-linz.ac.at/pow/pow.htm
* Oberon-0 Compiler: An educational compiler for a subset of the Oberon programming language: https://github.com/rcorcs/OberonC
* The obc Oberon compiler: http://fruttenboel.verhoeven272.nl/obc/index.html
* Oberon-07 is programming language: http://exaprog.com/eng/index.html
* Oxford Oberon-2 compiler: http://spivey.oriel.ox.ac.uk/corner/Oxford_Oberon-2_compiler
* Oberon2-Compiler: https://github.com/shitikanth/Oberon2-Compiler
* XDev is open and free set of compilers, additional tools, libraries and design patterns for cross-platform and embedded development in Oberon-2 language: https://github.com/Oleg-N-Cher/XDev
* Oberon-07/11 compiler for Win32: https://github.com/valexey/Oberon-07-11-compiler/
* XDS-C is a "via C" cross-compiler: https://www.excelsior-usa.com/doc/xds/xm.html, http://www.excelsior-usa.com/xds.html
* Oberon-0 Compiler: An educational compiler for a subset of the Oberon programming language: https://github.com/rcorcs/OberonC
* Oberon-07 translator: https://github.com/Vostok-space/vostok
* Durham University Oberon-2 Compiler: https://github.com/Metapyziks/duo2c?
* Oberon-07/11 compiler for x86-32 written by akron1: https://github.com/Spirit-of-Oberon/Oberon07akron1
* ETH Zonnon compiler: http://www.zonnon.ethz.ch/compiler/download.html

There are even whole reviews of compilers:
* N. E. Wirth Language Compilers: http://oberon07.com/compilers.xhtml
* Compilers and toolkit (rus): https://sites.google.com/site/oberonsystems/home/kompilatory-i
* Oberon Compilers and Language reference material: http://www.ethoberon.ethz.ch/compiler/
* Oberon-2 and Modula-2 Technical Publication: https://www.modulaware.com/mdlt62.htm

There is also an online OBERON compiler: http://oberspace.dyndns.org/oberonjs.html. 

On the other hand, I could not find the required cross-compiler for Windows, which would compile the object files for the Oberon boot disk on the x86 platform into Oberon’s own format?

I researched several approaches for this project. Among other things, there was an attempt to use GCC, more precisely MinGW, for cross-compiling. In the end, I decided to create your own cross-compiler.

# 3. Native Oberon, Vishap Oberon Compiler (VOC)

There is one of the many continuations of the Oberon project  - [Native Oberon](https://sourceforge.net/projects/nativeoberon). This project has a bootable system disk that is able to boot into the virtual machine [Bochs](https://en.wikipedia.org/wiki/Bochs). There is also a set of source files, including [the Oberon-2 compiler (OP2)](https://oberoncore.ru/_media/library/crelier_r.op2_a_portable_oberon_2_compiler.en.pdf) in the Oberon-2 language.

I am very lucky that I found the project [Vishap Oberon Compiler (VOC)](https://github.com/vishaps/voc/), which, in fact, is the Oberon-2 language translator into C language. It is necessary to add several built-in functions and interpret some errors as warnings in order for VOC to be able to translate the original Native Oberon project codes (see history of the VOC project).

The Oberon-2 compiler is translated into the C language with the help of the VOC. And I managed to compile all the source codes of the Native Oberon project into its own * .Obj format with the help of this C compiler.

# 4. Compiler

For some reason, the release version of the compiler sometimes does not work as expected. In view of this, the debug version of the product is used.

The compiler uses the realisation of the module File.Mod from the project voc. It's done for working with the window's file sistem.

The compiler requires the following files:
* Oberon.Text
* Oberon10.Scn.Fnt
* OPA.Data

To compile all the object files you have to repeatedly click compile_log.bat.

# 5. Testing

An obvious test for this work is the comparison of the object files obtained by this cross-compiler with those are found in [Native Oberon](https://sourceforge.net/projects/nativeoberon). You can compare the object files obtained from the Native Oberon project([no_obj](https://github.com/VoznyukI/OberonUtilities/tree/master/no_obj)) and compiled by this compiler([obj](https://github.com/VoznyukI/OberonUtilities/tree/master/obj)), for example, using [Araxis Merge](https://www.araxis.com/merge/index.en). For a complete binary match between these target files, some manipulations have to be done.

##### 5.1 
It is necessary to change the import order of modules (IMPORT) in some * .Mod files, for example, in the BMP.Mod, XPM.Mod files.

##### 5.2
Some files have been compiled with special [options](http://www.ethoberon.ethz.ch/native/compiler/options.html):
* FPA.Mod xp
* Net3Com509.Mod z
* Net3Com90x.Mod z
* NetBase.Mod z
* NetDNS.Mod z
* NetIP.Mod z
* NetNe2000.Mod z
* NetPorts.Mod z
* NetSystem.Mod z
* NetTCP.Mod z
* NetUDP.Mod z
* SLIP.Mod z

##### 5.3
The current implementation of the cross-compiler refuses to work with some * .Mod files, until the garbage placed at the begining of all files is removed. (As I understand the nature of this garbage are traces from the work of the Texts module).

It is necessary to delete the comments after the MODULE keyword in some cases, as well as the second comments, places on one line.  Therefore, many * .Mod files of this release differ from * .Mod files received from the [site](https://sourceforge.net/projects/nativeoberon). After compiling both versions of the .Mod file, the same binary files are obtained. 

##### 5.4
The current version of the compiler has a limit on the format of the file name. It must be with one point, followed by the Mod extension. It takes some manipulations with the renaming of files in view of this. It is enough just to drop the first prefix for most files, in the name of which there are two dots. For example, Native.Packages.Mod renames to Packages.Mod.

More complex changes have been made for other files. So, the file Displays.Display.Mod is renamed to the Display.Mod file, compiled and renamed to Displays.Display.Obj to check the operation of the compiler.

##### 5.5
There is no Display.Mod file in the source files. In order to get Display.Obj, you should rename Empty.Display.Mod to Display.Mod and compile. And then you should copy Display.Obj to Empty.Display.Obj. Empty.Display.Obj is exactly matched the Display.Obj file.

Similarly, there is no CD.Mod file in the source files. To do this, rename Empty.CD.Mod to CD.Mod and compile. The Empty.CD.Obj is exactly matched the CD.Obj file.

Similar manipulations are done with the following files:
* GD54xx.Display.Mod
* S3C805.Display.Mod
* S3C924.Display.Mod
* S3Trio.Display.Mod
* S3TrioC.Display.Mod
* SVGA.Display.Mod
* SVGAH.Display.Mod
* SVGAL.Display.Mod
* Trace.Display.Mod
* VGA.Display.Mod
* W32.Display.Mod

You can find the difference only in the file name that is specified in the * .Obj file for manipulated files. It can be checked with the help of binary comparison (for example, using [Araxis Merge](https://www.araxis.com/merge/index.en)).

##### 5.6
There are no corresponding * .Mod files for files IFWC31.Display.Obj and DisplayPermedia2.Obj from  [Native Oberon](https://sourceforge.net/projects/nativeoberon). And there is corresponding * .Obj file for the file DisplayBackdrop.Mod from  [Native Oberon](https://sourceforge.net/projects/nativeoberon) too.

##### 5.7 
There are files for which it is not possible to obtain exact correspondence with * .Obj files after compilation:
* ConfigV24.Mod - the current implementation of the cross-compiler does not support returning the value from the function as an array;
* HTMLDocs.Mod - error while compiling WriteCharRef function;
* LayoutPanels0.Mod - compilation error on the call to the Display3.Rect function (err 65 fewer actual than formal parameters);
* TestHalt.Mod  - the constant pi is read differently.

# 6. Utility view_obj

To work with * .Obj files, a console utility view_obj is developed that reads this [binary format](http://www.ethoberon.ethz.ch/native/compiler/obj081200/ObjectFile.html) and displays it in text form. It should be noted that there are some differences between [the document](http://www.ethoberon.ethz.ch/native/compiler/obj081200/ObjectFile.html) and the implementation of * .Obj in Native Oberon.
(Net3Com509_Obj.txt) TODO

# 7. The results and future plans

Thus, I have my own implementation of the Oberon cross-compiler at the moment. It is assumed to adapt the resulting compiler to generate object files for [Oberon system](https://github.com/Spirit-of-Oberon/ProjectOberonV4) in the future.

# 8. System Requirements

All work has been done on Windows XP and higher operating systems using MSVS 2010 SP1.

# 9. License

[Vishap Oberon Compiler (VOC)](https://github.com/vishaps/voc/) has been released under the GPLv3 License. 

Oberon Utilities are distributed under GPLv3 too.

# 10. Detected errors

The space before the MODULE keyword does not allow to compile the module.
