Set file=file.txt
Set source_dir=../src/

Set dest_dir=./

@Echo Off


For /F "usebackq tokens=*" %%i In (./%file%) Do (

	rem Echo compiler.exe %source_dir%%%i

  	for /f "tokens=1" %%a IN ("%%i") DO ( 
	
	 	if not exist %dest_dir%%%~na.Obj (
			rem echo %%a 
   		    	compiler.exe %source_dir%%%i
		)	

	 	if not exist %dest_dir%%%~na.Obj (
			echo not %%a 
		)	

	)
)

complile_rename_files.bat