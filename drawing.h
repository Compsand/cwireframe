#define diff(a, b) ((a)>(b)?(a-b):(b-a))
#define sign(a) (a > 0) - (a < 0)

#define VSYMBOL "@"
#define HSYMBOL "@"

typedef struct {
	float x;
	float y;
} V2;

typedef struct {
	float x;
	float y;
	float z;
} V3;

typedef struct {
	V3 *a;
	V3 *b;
} V3set;

/* draws a line between 2 points */
void line(V2 start, V2 end){
	/* move cursor to start of line */
	move(start.y, start.x);

	/* calculate difference between vectors */
	V2 diff = { diff(start.x,end.x), diff(start.y,end.y) };
	V2 sign = { sign(end.x-start.x), sign(end.y-start.y) };

	if(diff.y < diff.x){
		/* if x difference bigger, loop through every dot on the x axis */
		for(int i = 0; i <= diff.x; i++){
			/* calculate y position of dot */
			float progress = (float)i / diff.x;
			int b = roundf(start.y + progress * diff.y * sign.y);
			/* calculate x position of dot */
			int m = roundf(start.x + i * sign.x);
			/* draw dot */
			move(b,m);
			printw(HSYMBOL);
		}
	} else {
		/* the same but on the other axis
		(there's probably a way to have this as only 1 for loop
		but i want to finish this function asap) */
		for(int i = 0; i <= diff.y; i++){
			float progress = (float)i / diff.y;
			int b = roundf(start.x + progress * diff.x * sign.x);
			int m = roundf(start.y + i * sign.y);
			move(m,b);
			printw(VSYMBOL);
		}
	}
}

/* draws a line between 2 3d points */
/* size is the size of the 2d area to project onto */
void line3d(V3 start, V3 end, int size){
	/* avoid division by zero */
	if(start.z < 0.0 || end.z < 0.0) return;
	
	/* project */
	V2 start2d = {start.x / start.z, -start.y / start.z};
	V2 end2d = {end.x / end.z, -end.y / end.z};
	
	/* translate to terminal coordintates */
	start2d.x *= (float)size;
	start2d.y *= (float)size;
	end2d.x *= (float)size;
	end2d.y *= (float)size;

	start2d.x += size / 2;
	start2d.y += size / 2;
	end2d.x += size / 2;
	end2d.y += size / 2;

	/* draw!! */
	line(start2d, end2d);
}

