#include <sprite.h>
#include "player.h"
#include "collision.h"

#include "b0rkwin.h"

//#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif

OBJECT b0rkwin = {
	32,32,0,0
};

/*
 * TODO: PHYSICS as the current gravity is just crap
 */
#define GRAVITY (2)


void initPlayer(void)
{
	loadPalette(0, (void*)b0rkwinPal, false, TOP_SCREEN);
	hword_t * b0rkwinFrame = loadFrame((hword_t*)b0rkwinTiles, SpriteColorFormat_256Color, SpriteSize_32x32, 0, TOP_SCREEN);
	initSprite(0, 0, oamGfxPtrToOffset(states(TOP_SCREEN), b0rkwinFrame), SpriteSize_32x32, SpriteColorFormat_256Color, TOP_SCREEN);
	setSprXY(0, b0rkwin.x, b0rkwin.y, TOP_SCREEN);
	setSpriteVisiblity(false, 0, TOP_SCREEN);
}

void updatePlayer(u16* map,int dx, int dy)
{
	
	
	int val = checkMapCollision(&b0rkwin, 0, GRAVITY, map);
	if(!val) {
#ifdef DEBUGif
		printf("No collision\n");
#endif
		b0rkwin.y+= GRAVITY;
		b0rkwin.x+=dx;
	}
	/* align the b0rkwin */
	else {
		/* Not aligned */
		if(b0rkwin.y % 16 != 15) {
			b0rkwin.y += (15-(b0rkwin.y%16));
		}
#ifdef DEBUG
		printf("Coordinaten: %d,%d\n", b0rkwin.x, b0rkwin.y);
		if(val & D_COLLISION)
			printf("Down collision\n");
		if(val & U_COLLISION)
			printf("Up collision\n");
		if(val & R_COLLISION)
			printf("Right collision\n");
		if(val & L_COLLISION)
			printf("Left collision\n");
#endif
		if(dx<0){
			if( !(val & L_COLLISION))
				b0rkwin.x+=dx;
		} else if(dx>0){
			if( !(val & R_COLLISION))
				b0rkwin.x+=dx;
		}
		if(dy<0){
			if( !(val & D_COLLISION))
				b0rkwin.y+=dy;
		} else if(dy>0){
			if( !(val & U_COLLISION))
				b0rkwin.y+=dy;
		}
		
		
	}
	

	setSprXY(0, b0rkwin.x, b0rkwin.y, TOP_SCREEN);
}
