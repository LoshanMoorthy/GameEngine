set files=src\glad.c src\main.c 
set libs=D:\GameEngine\lib\SDL2main.lib D:\GameEngine\lib\SDL2.lib D:\GameEngine\lib\freetype.lib

CL /Zi /I D:\GameEngine\include %files% /link %libs% /OUT:game.exe 
