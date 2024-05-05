game.exe:main.o bg.o
	gcc main.o bg.o -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lm -o game -g
main.o:main.c
	gcc -c main.c -g
bg.o:bg.c
	gcc -c bg.c -g
