ml /c /Zd /coff output.asm
link /SUBSYSTEM:CONSOLE /OUT:output.exe output.obj
del output.asm
del output.obj
del errors.txt
del output.tok
output
