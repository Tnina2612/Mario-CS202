@echo off
setlocal enabledelayedexpansion

set "side=16"
set "gap=17"
set "count=1"

for /l %%i in (0, 1, 4) do (
    set "numCol=2"
    if %%i==0 set /a numCol+=1
    for /l %%j in (0, 1, !numCol!) do (
        set /a x=%%j*%gap%
        set /a y=%%i*%gap%
        magick C.png -crop %side%x%side%+!x!+!y! C!count!.png
	echo magick C.png -crop %side%x%side%+!x!+!y! C!count!.png
        set /a count+=1
    )
)