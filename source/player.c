#include <sprite.h>
#include "file.h"
#include "player.h"
#include "collision.h"
#include "input.h"

#ifdef DEBUG
#include <stdio.h>
#endif

OBJECT b0rkwin = {
	B0RKWIN_WIDTH,B0RKWIN_HEIGHT
};

#define B0RK_SPEED (3)
#define B0RKWIN_PAL "b0rkwin.pal.bin"
#define B0RKWIN_GFX "b0rkwin.img.bin"
/*
 * TODO: PHYSICS as the current gravity is just crap
 */
#define GRAVITY (1)

int b0rkwinCol(int mask, int inX, int inY)
{
	if(b0rkwin.dy) {
		if(mask & ( U_COLLISION | D_COLLISION )) {
			b0rkwin.y += inY;
			b0rkwin.dy = 0;
		}
	}
	if(b0rkwin.dx) {
		if(mask & ( R_COLLISION | L_COLLISION)) {
			b0rkwin.x += inX;
			b0rkwin.dx = 0;
		}
	}
	// we should be properly aligned by now, stop collision checking
	if(!b0rkwin.dx && !b0rkwin.dy)
		return 1;
	return 0;
}

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
	b0rkwin.collCallback = b0rkwinCol;
}

void updatePlayer(LEVEL* lvl)
{

	int val = checkMapCollision(&b0rkwin, lvl);
	b0rkwin.y += b0rkwin.dy;
	b0rkwin.x += b0rkwin.dx;

	if(!(val&D_COLLISION)) {
		b0rkwin.dy+=GRAVITY;
	}

	if(!(val&R_COLLISION)) {
		if(keysHold & KEY_RIGHT) {
			if(b0rkwin.dx < B0RK_SPEED)
				b0rkwin.dx ++;
		}
	}

	if(!(val&L_COLLISION)) {
		if(keysHold & KEY_LEFT) {
			if(b0rkwin.dx > -B0RK_SPEED)
				b0rkwin.dx --;
		}
	}

}

void deinitPlayer(void)
{

}
