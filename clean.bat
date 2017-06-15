forfiles /S /M *.o /c "cmd /c del /f @path"
forfiles /S /M a.out /c "cmd /c del /f @path"
forfiles /S /M *.swp /c "cmd /c del /f @path"


