@echo off
setlocal enabledelayedexpansion

set "side=16"
set "gap=17"
set "count=1"

for /l %%i in (0, 1, 1) do (
    for /l %%j in (0, 1, 4) do (
        set /a x=%%j*%gap%
        set /a y=%%i*%gap%
        magick S.png -crop %side%x%side%+!x!+!y! S!count!.png
        set /a count+=1
    )
)