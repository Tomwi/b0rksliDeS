#include <sprite.h>
#include "player.h"
#include "collision.h"

#include "b0rkwin.h"
#include "input.h"



/* 
 * TODO: PHYSICS as the current gravity is just crap
 */
#define GRAVITY (2)

void movePlayer(int x, int y);

void initPlayer(void){
	loadPalette(SPR_NO_BORKWIN, (void*)b0rkwinPal, false, TOP_SCREEN);
	hword_t * b0rkwin = loadFrame((hword_t*)b0rkwinTiles, SpriteColorFormat_256Color, SpriteSize_32x32, 0, TOP_SCREEN);
	initSprite(SPR_NO_BORKWIN, 0, oamGfxPtrToOffset(states(TOP_SCREEN), b0rkwin), SpriteSize_32x32, SpriteColorFormat_256Color, TOP_SCREEN);
	setSprXY(SPR_NO_BORKWIN, playerx, playery, TOP_SCREEN);
	setSpriteVisiblity(false, SPR_NO_BORKWIN, TOP_SCREEN);
}

void updatePlayer(u16* map, int dx, int dy){
	if(!checkCollision(playerx, playery, 0, GRAVITY, map))
		playery+= GRAVITY;
		
	playerx+=dx;
	playery+=dy;
	
	
		
	setSprXY(SPR_NO_BORKWIN, playerx, playery, TOP_SCREEN);
}




