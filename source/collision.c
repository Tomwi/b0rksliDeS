#include <feos.h>
#include <stdlib.h>
#include <stdio.h>

#include "collision.h"
extern int jumping;

#define CLAMP(n,l,u) ((n) = ((n) > (u) ? (u) : ((n)<(l) ? (l) : (n))))

inline int getTile(int x, int y, int width)
{
	CLAMP(x, 0, width-1);
	return y*width + x;
}

int checkMapCollision(OBJECT* obj, LEVEL* lvl)
{
	/* If you don't clamp it will b9rk at the edges */
	CLAMP(obj->x, 0, (lvl->hdr.width*COLTILE_SZ-32));
	CLAMP(obj->dx, 0-obj->x, ((lvl->hdr.width)*COLTILE_SZ-32-obj->x));
	
	CLAMP(obj->y,  0, (lvl->hdr.height*COLTILE_SZ-32));
	CLAMP(obj->dy, 0-obj->y, ((lvl->hdr.height)*COLTILE_SZ-32-obj->y));
	
	
	int x = obj->x;
	int y = obj->y;
	
	int toHor = 0;
	int toVer = 0;
	
	if(obj->dx < 0)
		toHor = (x + obj->dx) / COLTILE_SZ - ( x/COLTILE_SZ);
	else{
		
		toHor = ((( x + (COLTILE_SZ-1)) % COLTILE_SZ ) + obj->dx ) / COLTILE_SZ;
		
	}
	if(obj->dy < 0)
		toVer = (y + obj->dy) / COLTILE_SZ - ( y/COLTILE_SZ);
	else
		toVer= ((( y + (COLTILE_SZ-1)) % COLTILE_SZ ) + obj->dy ) / COLTILE_SZ;
	int toCheck = ( abs(toHor) >= abs(toVer) ? abs(toHor) : abs(toVer));
	if(toCheck==0)
		return 0;

	int i, val = 0;
	check:
	for(i=1; i<=toCheck; i++) {
		
		/* Calculate where the left top of the obj  would be located
		when a collision occurs */
		int x = obj->x;
		int y = obj->y;
		int cy = ((y/COLTILE_SZ)*COLTILE_SZ + ((toVer*i)/toCheck)*COLTILE_SZ);
		int cx = ((x/COLTILE_SZ)*COLTILE_SZ + ((toHor*i)/toCheck)*COLTILE_SZ);
		
		int tile = getTile(cx/COLTILE_SZ, cy/COLTILE_SZ, lvl->hdr.width);

		if(obj->dx) {
			int add = 0;
			/* Checking @ the right */
			if(obj->dx > 0) {
				add = obj->width/COLTILE_SZ;
				/* We're aligned and the right is one tile less far away from the left */
				if(x % COLTILE_SZ == 0)
					add--;
			}
			int j, k = 2 +  ((obj->y % COLTILE_SZ)? 1 : 0);
			for(j=0; j<k; j++) {
				if(lvl->colMap[tile+add+lvl->hdr.width*j] & (L_COLLISION | R_COLLISION)) {
					/* Prevent the collision system detecting horizontal collision whereas
					 * these tiles can't be reached due to a vertical collision */
					if(lvl->colMap[tile+add+lvl->hdr.width*j]& (D_COLLISION | U_COLLISION)){
						break;
					}
					val |= (obj->dx > 0 ? R_COLLISION : L_COLLISION );
					if(val) {
						int inX = cx-x;
						if(obj->dx < 0)
							inX += COLTILE_SZ;
						else {
							if(x % COLTILE_SZ == 0)
								inX -= COLTILE_SZ;
						}
						if(obj->collCallback((val&(L_COLLISION | R_COLLISION)), inX, cy-y))
							return val;
						else{
							toHor = 0;
							cy = ((obj->y/COLTILE_SZ)*COLTILE_SZ + ((toVer*i)/toCheck)*COLTILE_SZ);
							cx = ((obj->x/COLTILE_SZ)*COLTILE_SZ);
							tile = getTile(cx/COLTILE_SZ, cy/COLTILE_SZ, lvl->hdr.width);
						}
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
			int k, j = 2 +  ((obj->x % COLTILE_SZ)? 1 : 0);
			for(k=0; k<j; k++) {
				if(lvl->colMap[tile+add+k] & (U_COLLISION | D_COLLISION )) {
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
						if(obj->collCallback((val&(U_COLLISION | D_COLLISION)), cx-x, inY)){
							return val;
						}
					}
				}
			}
		}
	}	
	return val;
}