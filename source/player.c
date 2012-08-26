#include <sprite.h>
#include "file.h"
#include "player.h"
#include "collision.h"

#ifdef DEBUG
#include <stdio.h>
#endif

#define B0RKWIN_WIDTH	(32)
#define B0RKWIN_HEIGHT	(32) 

OBJECT b0rkwin = {
	B0RKWIN_WIDTH,B0RKWIN_HEIGHT,0,0
};

#define B0RKWIN_PAL "b0rkwin.pal.bin"
#define B0RKWIN_GFX "b0rkwin.img.bin"
/*
 * TODO: PHYSICS as the current gravity is just crap
 */
#define GRAVITY (2)

void initPlayer(void)
{
	int size;
	void* pal = bufferFile(B0RKWIN_PAL, &size);
	if(pal)
		loadPalette(0, (void*)pal, false, TOP_SCREEN);
	free(pal);
	void* gfx = bufferFile(B0RKWIN_GFX, &size);
	hword_t * b0rkwinFrame = NULL;
	if(gfx)
		b0rkwinFrame = loadFrame(gfx, SpriteColorFormat_256Color, SpriteSize_32x32, 0, TOP_SCREEN);
	free(gfx);
	initSprite(0, 0, oamGfxPtrToOffset(states(TOP_SCREEN), b0rkwinFrame), SpriteSize_32x32, SpriteColorFormat_256Color, TOP_SCREEN);
	setSprXY(0, b0rkwin.x, b0rkwin.y, TOP_SCREEN);
	setSpriteVisiblity(false, 0, TOP_SCREEN);
}

void updatePlayer(u16* map)
{
	int val = checkMapCollision(&b0rkwin, 0, GRAVITY, map);
	if(!val) {
#ifdef DEBUG
		printf("No collision\n");
#endif
		b0rkwin.y+= GRAVITY;
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
	}

	setSprXY(0, b0rkwin.x, b0rkwin.y, TOP_SCREEN);
}

void deinitPlayer(void){
	
}
