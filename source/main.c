#include <feos.h>
#include <stdio.h>
#include <stdlib.h>

#include "audio.h"
#include "background.h"
#include "camera.h"
#include "input.h"
#include "level.h"
#include "file.h"
#include "sprite.h"
#include "player.h"

BG_INF* level;

#define LEVEL0_PAL "level0.pal.bin"
#define LEVEL0_GFX "level0.img.bin"


int main()
{
	FeOS_DirectMode();
	FeOS_SetAutoUpdate(AUTOUPD_KEYS, false);
	
	videoSetMode(MODE_5_2D);
	vramSetPrimaryBanks (VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG_0x06200000, VRAM_D_LCD);
	
	oamEnable(states(TOP_SCREEN));
	oamInit(states(TOP_SCREEN), SpriteMapping_1D_128, false);
	
	LEVEL* lvl = loadLevel("level0.bks");
	
	int tileSize = 0;
	int palSize = 0;
	void* tiles 	=  bufferFile(LEVEL0_GFX , &tileSize);
	void* pal 		=  bufferFile(LEVEL0_PAL , &palSize);

	if(tiles && pal)
	level = initBg(tiles, tileSize, pal, lvl->hdr.width*2, lvl->hdr.height*2, 0, lvl->tileMap);

	free(tiles);
	free(pal);
	
	initPlayer();
	initAudio();
	
	while(1) {
		FeOS_WaitForVBlank();
		updateCamera(&b0rkwin, level);
		readInput();
		if(keysPres & KEY_START)
			break;
		updatePlayer(lvl);
	}
	deinitAudio();
	freeLevel(lvl);
	FeOS_ConsoleMode();
	return 0;
}
