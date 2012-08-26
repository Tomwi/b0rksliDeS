#include <feos.h>
#include <stdio.h>
#include <stdlib.h>

#include "background.h"
#include "input.h"
#include "map.h"
#include "sprite.h"
#include "player.h"

#include "level0.h"


BG_INF* level;

int main()
{
	FeOS_DirectMode();
	FeOS_SetAutoUpdate(AUTOUPD_KEYS, false);
	
	videoSetMode(MODE_5_2D);
	vramSetPrimaryBanks (VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG_0x06200000, VRAM_D_LCD);
	
	oamEnable(states(TOP_SCREEN));
	oamInit(states(TOP_SCREEN), SpriteMapping_1D_128, false);
	
	level = initBg((s16*)level0Tiles, level0TilesLen, (s16*)level0Pal, 32, 0, (s16*)level0Map);
	initPlayer();
	
	u16* map = loadMap("level0.bks");
	
	while(1) {
		FeOS_WaitForVBlank();
		readInput();
		updateScroll(level);
		updatePlayer(map);
	}
	return 0;
}
