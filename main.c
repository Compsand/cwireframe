#include <stdio.h>
#include <math.h>
#include <ncurses.h>
#include "drawing.h"

/* function for rotating an array of vertices (broken currently) */
void rotatey(V3 *ve, int veamnt, float rads, V3 center){
	for(int i = 0; i < veamnt; i++){
		ve[i].x = center.x + (ve[i].x-center.x)*cos(rads)-(ve[i].z-center.z)*sin(rads);
		ve[i].z = center.z + (ve[i].x-center.x)*sin(rads)+(ve[i].z-center.z)*cos(rads);
	}
}

int main(int argc, char *argv[])
{
	/* vertices for the model */
	V3 ve[8] = {
		{0.1, 0.1, 0.1},
		{-0.1, 0.1, 0.1},
		{-0.1, -0.1, 0.1},
		{0.1, -0.1, 0.1},
		{0.1, 0.1, -0.1},
		{-0.1, 0.1, -0.1},
		{-0.1, -0.1, -0.1},
		{0.1, -0.1, -0.1}
	};

	/* lines between vertices */
	V3set ln[12] = {
		{&ve[0],&ve[1]},
		{&ve[1],&ve[2]},
		{&ve[2],&ve[3]},
		{&ve[3],&ve[0]},
		{&ve[4],&ve[5]},
		{&ve[5],&ve[6]},
		{&ve[6],&ve[7]},
		{&ve[7],&ve[4]},
		{&ve[0],&ve[4]},
		{&ve[1],&ve[5]},
		{&ve[2],&ve[6]},
		{&ve[3],&ve[7]}
	};

	/* ncurses initialization */
	initscr();
	curs_set(0);
	
	int termw, termh;
	getmaxyx(stdscr, termh, termw);

	cbreak();

	/* main loop */
	while(true){

		/* get input */
		char ans = getch();
		
		/* controls */
		switch (ans) {
			case 'q':
				goto end;
				break;
			case 'w':
				for(int i = 0; i < 8; i++){
					ve[i].z += 0.1;
				}
				break;
			case 's':
				for(int i = 0; i < 8; i++){
					ve[i].z -= 0.1;
				}
				break;
			case 'j':
				for(int i = 0; i < 8; i++){
					ve[i].y -= 0.1;
				}
				break;
			case 'k':
				for(int i = 0; i < 8; i++){
					ve[i].y += 0.1;
				}
				break;
			case 'h':
				for(int i = 0; i < 8; i++){
					ve[i].x -= 0.1;
				}
				break;
			case 'l':
				for(int i = 0; i < 8; i++){
					ve[i].x += 0.1;
				}
				break;
			case 'r':
				rotatey(ve, 8, M_PI * 0.25, ve[0]);
				break;
		}

		/* draw */
		clear();
		/* go throught all the lines and draw them */
		for(int i = 0; i < 12; i++) {
			line3d(*ln[i].a, *ln[i].b, termw<termh ? termw : termh);
		}
		refresh();
	}
end:
	endwin();
	return 0;
}
