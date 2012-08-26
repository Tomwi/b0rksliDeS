#include <feos.h>
#include <stdlib.h>
#include <stdio.h>

#include "collision.h"

inline int getTile(int x, int y, int width){
	return y*width + x;
}

/*
Checks for a collision
x and y need to be in pixels!:D
TODO: check the directional bits of the collision tiles
*/
int checkMapCollision(OBJECT* obj, int dx, int dy, u16* map){
	
	int x = obj->x;
	int y = obj->y;
	int toHor = (( x % COLTILE_SZ ) + dx ) / COLTILE_SZ;
	int toVer = (( y % COLTILE_SZ ) + dy ) / COLTILE_SZ;
	int toCheck = ( abs(toHor) >= abs(toVer) ? abs(toHor) : abs(toVer));
	/* We stay on the same tile, so stop (and avoid a division by zero too) */
	if(toCheck==0)
				return 0;
	int i, val = 0;
	for(i=0; i<toCheck; i++){
		 int cy = y + ((toVer*i)/toCheck)*COLTILE_SZ;
		 int cx = x + ((toHor*i)/toCheck)*COLTILE_SZ;
		 int tile = getTile(cx/COLTILE_SZ, cy/COLTILE_SZ, map[0]);
		 if(dx){
			 int add = -1;/* Check for left and right collision */
			 if(dx > 0)
				 add = obj->width/COLTILE_SZ + 1;
			 int i;
			 for(i=0; i<obj->height/COLTILE_SZ; i++){
				 // right or left collision occured: TODO -> callback for object
				 if(map[2+tile+add+map[0]*i] & (L_COLLISION | R_COLLISION )){
					 val |= (dx > 0 ? R_COLLISION : L_COLLISION );
					 break;
				 }
			 }
		 }
		 if(dy){
			 int add = 0;/* Check for Down and up collision */
			 if(dy > 0){
				 add = map[0] * (obj->height/COLTILE_SZ);
			 }
			 int i;
			 for(i=0; i<obj->width/COLTILE_SZ; i++){
				 // right or left collision occured: TODO -> callback for object
				 if(map[2+tile+add+i] & (U_COLLISION | D_COLLISION )){
					 val |= (dy > 0 ? D_COLLISION : U_COLLISION );
					 break;
				 }
			 }
		 }
		 if(val)
			 return val;
	}
	return val;
}

