@echo off
setlocal enabledelayedexpansion
set "splitWidth=16"
set "splitHeight=16"
set "count=1"
for /l %%i in (0, 1, 4) do (
    set /a y=%splitHeight%+1
    set /a y=y*%%i
    
    set /a "numCol=2"
    if %%i==0 set /a numCol += 1
    for /l %%j in (0, 1, !numCol!) do (
        set /a x=%splitWidth%+1
        set /a x=x*%%j
        magick C.png -crop %splitWidth%x%splitHeight%+!x!+!y! C!count!.png
        echo magick C.png -crop %splitWidth%x%splitHeight%+!x!+!y! C!count!.png
	set /a count += 1
    )
)

pause