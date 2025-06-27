@echo off
setlocal enabledelayedexpansion

set "side=16"
set "gap=17"
set "count=1"

for /l %%i in (0, 1, 3) do (
    for /l %%j in (0, 1, 8) do (
        set /a x=%gap%*%%j
        set /a y=%gap%*%%i
	echo crop !x!,!y!
        pause
        if %%i==1 (
            if %%j NEQ 4 (
                magick P.png -crop %side%x%side%+!x!+!y! P!count!.png
		echo magick P.png -crop %side%x%side%+!x!+!y! P!count!.png
		set /a count += 1
            )
        ) else if %%i==2 (
            if %%j NEQ 3 (
                if %%j NEQ 4 (
                    magick P.png -crop %side%x%side%+!x!+!y! P!count!.png
                    echo magick P.png -crop %side%x%side%+!x!+!y! P!count!.png
                    set /a count += 1
                )
            )
        ) else (
            magick P.png -crop %side%x%side%+!x!+!y! P!count!.png
            echo magick P.png -crop %side%x%side%+!x!+!y! P!count!.png
            set /a count += 1
        )
    )
)