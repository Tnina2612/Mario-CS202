@echo off
setlocal enabledelayedexpansion
set "filename=S"
set "side=16"
set "space=17"
set "count=1"

for /l %%i in (0, 1, 1) do (
    set /a y=%%i*%space%

    for /l %%j in (0, 1, 4) do (
        set /a x=%%j*%space%

        magick %filename%.png -crop %side%x%side%+!x!+!y! %filename%!count!.png
        echo magick %filename%.png -crop %side%x%side%+!x!+!y! %filename%!count!.png
        set /a count += 1

	echo Done !x!, !y!
        pause
    )
)