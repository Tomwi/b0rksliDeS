#include <feos.h>
#include <stdio.h>
#include <stdlib.h>

#include "audio.h"
#include "background.h"
#include "input.h"
#include "map.h"
#include "file.h"
#include "sprite.h"
#include "player.h"

BG_INF* level;

/* TODO: add a clean way to load levels */
#define LEVEL0_PAL "level0.pal.bin"
#define LEVEL0_GFX "level0.img.bin"
#define LEVEL0_MAP "level0.map.bin"

int main()
{
	FeOS_DirectMode();
	FeOS_SetAutoUpdate(AUTOUPD_KEYS, false);
	
	videoSetMode(MODE_5_2D);
	vramSetPrimaryBanks (VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG_0x06200000, VRAM_D_LCD);
	
	oamEnable(states(TOP_SCREEN));
	oamInit(states(TOP_SCREEN), SpriteMapping_1D_128, false);
	int tileSize = 0;
	int mapSize = 0;
	void* tiles 	=  bufferFile(LEVEL0_GFX , &tileSize);
	void* pal 		=  bufferFile(LEVEL0_PAL , &mapSize);
	void* tileMap 	=  bufferFile(LEVEL0_MAP , &mapSize);
	if(tiles && pal && tileMap)
	level = initBg(tiles, tileSize, pal, 32, 0, tileMap);
	free(tiles);
	free(pal);
	
	initPlayer();
	
	u16* map = loadMap("level0.bks");
	initAudio();
	while(1) {
		FeOS_WaitForVBlank();
		readInput();
		if(keysPres & KEY_START)
			break;
		updateScroll(level);
		updatePlayer(map);
	}
	deinitAudio();
	free(map);
	free(tileMap);
	
	return 0;
}
