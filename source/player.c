#include <sprite.h>
#include "player.h"
#include "collision.h"

#include "b0rkwin.h"

int x, y;

/* 
 * TODO: PHYSICS as the current gravity is just crap
 */
#define GRAVITY (2)

void initPlayer(void){
	loadPalette(0, (void*)b0rkwinPal, false, TOP_SCREEN);
	hword_t * b0rkwin = loadFrame((hword_t*)b0rkwinTiles, SpriteColorFormat_256Color, SpriteSize_32x32, 0, TOP_SCREEN);
	initSprite(0, 0, oamGfxPtrToOffset(states(TOP_SCREEN), b0rkwin), SpriteSize_32x32, SpriteColorFormat_256Color, TOP_SCREEN);
	setSprXY(0, x, y, TOP_SCREEN);
	setSpriteVisiblity(false, 0, TOP_SCREEN);
}

void updatePlayer(u16* map){
	if(!checkCollision(x, y, 0, GRAVITY, map))
		y+= GRAVITY;
	setSprXY(0, x, y, TOP_SCREEN);
}
