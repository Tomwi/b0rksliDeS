#include <feos.h>
#include <stdlib.h>
#include <stdio.h>

#include "collision.h"

inline int getTile(int x, int y, int width)
{
	return y*width + x;
}

/*
Checks for a collision
x and y need to be in pixels!:D
*/
int checkMapCollision(OBJECT* obj, LEVEL* lvl)
{

	int x = obj->x;
	int y = obj->y;
	int toHor = 0;
	int toVer = 0;
	if(obj->dx < 0)
		toHor = (( x % COLTILE_SZ ) + abs(obj->dx)) / COLTILE_SZ;
	else
		toHor = (( x % COLTILE_SZ ) + obj->width + obj->dx ) / COLTILE_SZ;
	if(obj->dy < 0)
		toVer= (( y % COLTILE_SZ ) + obj->dy ) / COLTILE_SZ;
	else
		toVer= (( y % COLTILE_SZ ) + obj->height + obj->dy ) / COLTILE_SZ;
	int toCheck = ( abs(toHor) >= abs(toVer) ? abs(toHor) : abs(toVer));
	/* We stay on the same tile, so stop (and avoid a division by zero too) */
	if(toCheck==0)
		return 0;

	int i, val = 0;
	for(i=0; i<toCheck; i++) {
		int cy = y + ((toVer*i)/toCheck)*COLTILE_SZ;
		int cx = x + ((toHor*i)/toCheck)*COLTILE_SZ;
		int tile = getTile(cx/COLTILE_SZ, cy/COLTILE_SZ, lvl->hdr.width);
		if(obj->dx) {
			int add = 0;
			if(obj->dx > 0)
				add = obj->width/COLTILE_SZ-1;
			int i;
			for(i=0; i<obj->height/COLTILE_SZ; i++) {
				if(lvl->colMap[tile+add+lvl->hdr.width*i] & (L_COLLISION | R_COLLISION )) {
					val |= (obj->dx > 0 ? R_COLLISION : L_COLLISION );
					if(val) {
						if(obj->collCallback((val&12), cx-x, cy-y))
							return val;
					}
				}
			}
		}
		if(obj->dy) {
			int add = -1;
			if(obj->dy > 0) {
				add = lvl->hdr.width* (obj->height/COLTILE_SZ);
			}
			int i;
			for(i=0; i<obj->width/COLTILE_SZ; i++) {
				if(lvl->colMap[tile+add+i] & (U_COLLISION | D_COLLISION )) {
					val |= (obj->dy > 0 ? D_COLLISION : U_COLLISION );
					if(val) {
						if(obj->collCallback((val&3), cx-x, cy-y))
							return val;
					}
				}
			}
		}
	}
	return val;
}
