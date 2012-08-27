#ifndef B_LEVEL_H
#define B_LEVEL_H

#include <feos.h>
#include <stdlib.h>
#include <stdio.h>

/* TODO:
 * add support for "level modules"
 */
 
typedef struct {
	u16 width;
	u16 height;
}LEVEL_HDR;

typedef struct{
	LEVEL_HDR hdr;
	u16* colMap;
	u16* tileMap;
}LEVEL;


LEVEL* loadLevel(const char* name);
void freeLevel(LEVEL* lvl);

#endif
