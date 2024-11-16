all:
	gcc -I src/include -L src/lib -o main main.c mathslibrary/matrix.c mathslibrary/vec.c -lmingw32 -lSDL2main -lSDL2