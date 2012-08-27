#ifndef BACKGROUND_H
#define BACKGROUND_H

typedef struct BG_INF {
	void * map;			
	void * vram_map;	
	int mapwidth, mapHeight;
	int bgId;
	int x, y;
} BG_INF;

/* ASM */

void t_copyRow(BG_INF*, int, int, int);
void t_copyColumn(BG_INF*, int, int);

/* C */
void fillScreen(BG_INF*, int, int);
BG_INF* initBg(s16* tiles, int tileSz, s16* pal, int width, int height, int layer, u16* map);
void updateScroll(BG_INF*, int dx, int dy);

#endif
