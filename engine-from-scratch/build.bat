set files=src\glad.c src\main.c 
set libs=D:\game_engine\lib\SDL2main.lib D:\game_engine\lib\SDL2.lib D:\game_engine\lib\freetype.lib

CL /Zi /I D:\game_engine\include %files% /link %libs% /OUT:game.exe 
