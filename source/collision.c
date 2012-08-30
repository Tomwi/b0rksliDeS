#include <feos.h>
#include <stdlib.h>
#include <stdio.h>

#include "collision.h"

inline int getTile(int x, int y, int width)
{
	return y*width + x;
}

int checkMapCollision(OBJECT* obj, LEVEL* lvl)
{
	int x = obj->x;
	int y = obj->y;
	int toHor = 0;
	int toVer = 0;
	if(obj->dx < 0)
		toHor = (x + obj->dx) / COLTILE_SZ - ( x/COLTILE_SZ);
	else
		toHor = ((( x + 0xF) % COLTILE_SZ ) + obj->dx ) / COLTILE_SZ;
	if(obj->dy < 0)
		toVer = (y + obj->dy) / COLTILE_SZ - ( y/COLTILE_SZ);
	else
		toVer= ((( y + 0xF) % COLTILE_SZ ) + obj->dy ) / COLTILE_SZ;
	int toCheck = ( abs(toHor) >= abs(toVer) ? abs(toHor) : abs(toVer));

	if(toCheck==0)
		return 0;

	int i, val = 0;
	for(i=1; i<=toCheck; i++) {
		/* Calculate where the left top of the obj  would be located
		when a collision occurs */
		int cy = ((y/COLTILE_SZ)*COLTILE_SZ + ((toVer*i)/toCheck)*COLTILE_SZ);
		int cx = ((x/COLTILE_SZ)*COLTILE_SZ + ((toHor*i)/toCheck)*COLTILE_SZ);

		int tile = getTile(cx/COLTILE_SZ, cy/COLTILE_SZ, lvl->hdr.width);

		if(obj->dx) {
			int add = 0;
			if(obj->dx > 0) {
				add = obj->width/COLTILE_SZ;
				/* We're aligned and the right is one tile less far away from the left */
				if(x % COLTILE_SZ == 0)
					add--;
			}
			int j;
			for(j=0; j<obj->height/COLTILE_SZ; j++) {
				if(lvl->colMap[tile+add+lvl->hdr.width*j] & (L_COLLISION | R_COLLISION )) {
					val |= (obj->dx > 0 ? R_COLLISION : L_COLLISION );
					if(val) {
						int inX = cx-x;
						if(obj->dx < 0)
							inX += COLTILE_SZ;
						else {
							if(x % COLTILE_SZ == 0)
								inX -= COLTILE_SZ;
						}
						if(obj->collCallback((val&12), inX, cy-y))
							return val;
					}
				}
			}
		}
		if(obj->dy) {
			int add = 0;
			if(obj->dy > 0) {
				add = lvl->hdr.width* (obj->height/COLTILE_SZ);
				if(y % COLTILE_SZ == 0)
					add-=lvl->hdr.width;
			}
			int i;
			for(i=0; i<obj->width/COLTILE_SZ; i++) {
				if(lvl->colMap[tile+add+i] & (U_COLLISION | D_COLLISION )) {
					val |= (obj->dy > 0 ? D_COLLISION : U_COLLISION );
					if(val) {
						int inY = cy-y;

						if(obj->dy < 0)
							inY += COLTILE_SZ;
						else {
							/* This is an annoying situation, because there's one tile less
							when going down aligned. Going up always needs some adjusting of inY.
							*/
							if(y % COLTILE_SZ == 0)
								inY -= COLTILE_SZ;
						}
						if(obj->collCallback((val&3), cx-x, inY))
							return val;
					}
				}
			}
		}
	}
	return val;
}
