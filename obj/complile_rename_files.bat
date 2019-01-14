if exist DisplaysDisplay.Obj (
	if not exist Displays.Display.Obj (
		copy DisplaysDisplay.Obj Displays.Display.Obj
	)	
)	

rem if exist EmptyDisplay.Obj (
rem 	if not exist Display.Obj (
rem		copy EmptyDisplay.Obj Display.Obj
rem 		copy EmptyDisplay.Obj Empty.Display.Obj
rem 	)	
rem )	
if exist Display.Obj (
 	if not exist Empty.Display.Obj (
 		copy Display.Obj Empty.Display.Obj
 	)	
)	

if exist CD.Obj (
 	if not exist Empty.CD.Obj (
 		copy CD.Obj Empty.CD.Obj
 	)	
)	

if exist GD54xxDisplay.Obj (
	if not exist GD54xx.Display.Obj (
		ren GD54xxDisplay.Obj GD54xx.Display.Obj
	)	
)	

if exist S3C805Display.Obj (
	if not exist S3C805.Display.Obj (
		ren S3C805Display.Obj S3C805.Display.Obj
	)	
)	

if exist S3C924Display.Obj (
	if not exist S3C924.Display.Obj (
		ren S3C924Display.Obj S3C924.Display.Obj
	)	
)	

if exist S3TrioDisplay.Obj (
	if not exist S3Trio.Display.Obj (
		ren S3TrioDisplay.Obj S3Trio.Display.Obj
	)	
)	

if exist S3TrioCDisplay.Obj (
	if not exist S3TrioC.Display.Obj (
		ren S3TrioCDisplay.Obj S3TrioC.Display.Obj
	)	
)	

if exist SVGADisplay.Obj (
	if not exist SVGA.Display.Obj (
		ren SVGADisplay.Obj SVGA.Display.Obj
	)	
)	

if exist SVGAHDisplay.Obj (
	if not exist SVGAH.Display.Obj (
		ren SVGAHDisplay.Obj SVGAH.Display.Obj
	)	
)	

if exist SVGALDisplay.Obj (
	if not exist SVGAL.Display.Obj (
		ren SVGALDisplay.Obj SVGAL.Display.Obj
	)	
)	

if exist TraceDisplay.Obj (
	if not exist Trace.Display.Obj (
		ren TraceDisplay.Obj Trace.Display.Obj
	)	
)	

if exist VGADisplay.Obj (
	if not exist VGA.Display.Obj (
		ren VGADisplay.Obj VGA.Display.Obj
	)	
)	

if exist W32Display.Obj (
	if not exist W32.Display.Obj (
		ren W32Display.Obj W32.Display.Obj
	)	
)	
