#include <feos.h>
#include <stdlib.h>
#include <stdio.h>

#include "collision.h"
#include "b0rk.h"

extern int jumping;

inline int getTile(int x, int y, int width)
{
	CLAMP(x, 0, width-1);
	return y*width + x;
}

int checkMapCollision(OBJECT* obj, LEVEL* lvl)
{
	int toHor = 0, toVer = 0, i, j, k, val;
	int addX = 0, addY = 0;
	bool checkY = true, checkX = true;
	if(!obj->dx)
		checkX = false;
	if(!obj->dy)
		checkY = false;
	/* Nothing to do */
	if(!checkX && !checkY)
		return 0;

	if(obj->dx < 0)
		toHor = (obj->x + obj->dx)/COLTILE_SZ - obj->x/COLTILE_SZ;
	else {
		toHor = ((( obj->x + (COLTILE_SZ-1)) % COLTILE_SZ ) + obj->dx ) / COLTILE_SZ;
		addX = COLTILE_SZ*2 - 1;
	}

	if(obj->dy < 0)
		toVer = (obj->y + obj->dy)/COLTILE_SZ - obj->y/COLTILE_SZ;
	else {
		toVer= ((( obj->y + (COLTILE_SZ-1)) % COLTILE_SZ ) + obj->dy ) / COLTILE_SZ;
		addY = COLTILE_SZ*2 - 1;
	}

	j = (abs(toHor)>=abs(toVer)? abs(toHor):abs(toVer));
	for(i=0; i<=j; i++) {
		int tX = obj->x + ((i*toHor)/j)*COLTILE_SZ;
		int tY = obj->y + ((i*toVer)/j)*COLTILE_SZ;

		int hT = getTile((tX + addX)/COLTILE_SZ , tY/COLTILE_SZ, lvl->hdr.width);
		int vT = getTile(tX/COLTILE_SZ, ((tY + addY)/COLTILE_SZ), lvl->hdr.width);

		for(k=0; k<(2+(obj->y % COLTILE_SZ ? 1: 0)); k++) {
			if(checkX) {
				if((val=lvl->colMap[hT + k*lvl->hdr.width])) {
					if(val & R_COLLISION && obj->dx > 0) {
						obj->x += ((tX + addX)/COLTILE_SZ)*COLTILE_SZ - (obj->x+32);
						obj->dx = 0;
						vT = getTile((obj->x)/COLTILE_SZ, ((tY + addY)/COLTILE_SZ), lvl->hdr.width);
					}
					if(val & L_COLLISION && obj->dx < 0) {
						obj->x += ((tX)/COLTILE_SZ)*COLTILE_SZ - (obj->x) + COLTILE_SZ;
						obj->dx = 0;
						vT = getTile((obj->x)/COLTILE_SZ, ((tY + addY)/COLTILE_SZ), lvl->hdr.width);
					}
					checkX = false;
				}
			}
		}
		for(k=0; k<(2+(obj->x % COLTILE_SZ ? 1: 0)); k++) {
			if(checkY) {
				if((val=lvl->colMap[vT + k])) {
					if(val & D_COLLISION) {
						if(jumping)
							jumping = 0;
						obj->y += ((tY + addY)/COLTILE_SZ)*COLTILE_SZ - (obj->y+32);
						obj->dy = 0;
					}
					if(val & U_COLLISION) {
						obj->y += ((tY)/COLTILE_SZ)*COLTILE_SZ - (obj->y) + COLTILE_SZ;
						obj->dy = 0;
					}
					checkY = false;
				}
			}
		}
	}
	return 0;
}
