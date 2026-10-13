#include <stdio.h>
#include <math.h>
#include <ncurses.h>

#define ACTIVE "@"

#define diff(a, b) ((a)>(b)?(a-b):(b-a))
#define sign(a) (a > 0) - (a < 0)

typedef struct {
	float x;
	float y;
} V2;

typedef struct {
	float x;
	float y;
	float z;
} V3;

void line(V2 start, V2 end){
	// move cursor to start of line
	move(start.y, start.x);

	// calculate difference between vectors
	V2 diff = { diff(start.x,end.x), diff(start.y,end.y) };
	V2 sign = { sign(end.x-start.x), sign(end.y-start.y) };

	if(diff.y < diff.x){
		// if x difference bigger, loop through every dot on the x axis
		for(int i = 0; i <= diff.x; i++){
			// calculate y position of dot
			float progress = (float)i / diff.x;
			int b = roundf(start.y) + progress * diff.y * sign.y;
			// calculate x position of dot
			int m = roundf(start.x) + i * sign.x;
			// draw dot
			move(b,m);
			printw(ACTIVE);
		}
	}
}

int main(int argc, char *argv[])
{
	initscr();
	curs_set(0);
	
	int termw, termh;
	int paused = 1;
	getmaxyx(stdscr, termh, termw);

	V2 p1 = {1,1};
	V2 p2 = {1,1};

	cbreak();

	while(true){

		/* get input */
		char ans = getch();
		
		switch (ans) {
			case 'q':
				goto end;
				break;
			case 'p':
				if(paused){
					paused = 0;
					halfdelay(1);
				} else {
					paused = 1;
					cbreak();
				}
				break;
			case 'l':
				p2.x += 1;
				break;
			case 'h':
				p2.x -= 1;
				break;
			case 'j':
				p2.y += 1;
				break;
			case 'k':
				p2.y -= 1;
				break;
			case 'L':
				p1.x += 1;
				break;
			case 'H':
				p1.x -= 1;
				break;
			case 'J':
				p1.y += 1;
				break;
			case 'K':
				p1.y -= 1;
				break;
		}

		/* draw line */
		clear();
		line(p1,p2);
		refresh();
	}
end:
	endwin();
	return 0;
}
