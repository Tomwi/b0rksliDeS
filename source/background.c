#include <feos.h>
#include <stdio.h>
#include <stdlib.h>

#include "background.h"
#include "input.h"

#define TILE_SIZE (8)

int bgx, bgy;
int freeVIDX, freeBYT;

void fillScreen(BG_INF* inf, int tx, int ty)
{
	int i;
	for(i=0; i<33; i++)
		t_copyColumn(inf, tx+i, ty);
}

BG_INF* initBg(s16* tiles, int tileSz, s16* pal, int width, int layer, s16* map)
{
	BG_INF* tmp;
	if((tmp = malloc(sizeof(BG_INF)))) {
		tmp->bgId = bgInit(layer, BgType_Text8bpp, BgSize_T_512x256, 0,1);
		dmaCopy(tiles, bgGetGfxPtr(tmp->bgId), tileSz);
		dmaCopy(pal, BG_PALETTE, 256*2);
		tmp->vram_map 	= bgGetMapPtr(tmp->bgId);
		tmp->map 		= map;
		tmp->mapwidth	= width;
		fillScreen(tmp, 0, 0);
		return tmp;
	}
	return NULL;
}

void scroll(int xo, int yo, int dx, int dy, BG_INF* inf)
{
	int i;
	int toCopyX = (xo+dx)/TILE_SIZE - (xo/TILE_SIZE);
	/* Copy left */
	if(toCopyX < 0) {
		for(i=-1; i>=toCopyX; i--)
			t_copyColumn(inf, (xo/TILE_SIZE)+i, (yo+dy)/TILE_SIZE);
	} 
	/* Copy right */
	else if(toCopyX > 0) {
		for(i=1; i<=toCopyX; i++)
			t_copyColumn(inf, (xo/TILE_SIZE)+i+32, (yo+dy)/TILE_SIZE);
	}
	int toCopyY = (yo+dy)/TILE_SIZE - (yo/TILE_SIZE);
	int copyLen = 33-(toCopyX >= 0 ? toCopyX : -toCopyX);
	if(copyLen) {
		if(toCopyY < 0) {
			for(i=-1; i>=toCopyY; i--)
				t_copyRow(inf, (xo)/TILE_SIZE, yo/TILE_SIZE+i, copyLen);
		} else if(toCopyY > 0) {
			for(i=1; i<=toCopyY; i++)
				t_copyRow(inf, (xo+dx)/TILE_SIZE, yo/TILE_SIZE+24+i, copyLen);
		}
	}

}

void updateScroll(BG_INF* inf)
{
	int dx = 0, dy = 0;
	if(keysHold & KEY_RIGHT)
		dx = 1;
	else if(keysHold & KEY_LEFT)
		dx = -1;
	if(keysHold & KEY_UP)
		dy = -1;
	else if(keysHold & KEY_DOWN)
		dy = 1;
	scroll(bgx, bgy, dx, dy, inf);
	bgx+= dx;
	bgy+= dy;
	bgSetScroll (inf->bgId, bgx, bgy);
	bgUpdate();
}
