set render=src\engine\render\render.c src\engine\render\render_init.c src\engine\render\render_util.c
set io=src\engine\io\io.c
set files=src\glad.c src\main.c src\engine\global.c %render% %io%
set libs=D:\game_engine\lib\SDL2main.lib D:\game_engine\lib\SDL2.lib D:\game_engine\lib\freetype.lib

CL /Zi /I D:\game_engine\include %files% /link %libs% /OUT:game.exe 
