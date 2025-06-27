@echo off
setlocal enabledelayedexpansion

set "side=16"
set "gap=17"
set "count=1"

for /l %%i in (0, 1, 3) do (
    for /l %%j in (0, 1, 7) do (
        set /a x=%%j*%gap%
        set /a y=%%i*%gap%
        if %%i==2 (
            if %%j NEQ 6 (
                magick G.png -crop %side%x%side%+!x!+!y! G!count!.png
                set /a count += 1
            )
        ) else if %%i==3 (
            if %%j NEQ 7 (
                magick G.png -crop %side%x%side%+!x!+!y! G!count!.png
                set /a count += 1
            )
        ) else (
            magick G.png -crop %side%x%side%+!x!+!y! G!count!.png
            set /a count += 1
        )
    )
)