a.out : main.c drawing.h
	tcc -o a.out -lm -lncurses main.c
