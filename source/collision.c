#include <feos.h>
#include <stdlib.h>
#include <stdio.h>

#include "collision.h"

#define COLTILE_SZ (16)
#define D_COLLISION (BIT(0))
#define R_COLLISION (BIT(1))
#define L_COLLISION (BIT(2))
#define U_COLLISION (BIT(3))


#define COLTILE_SZ (16)

inline int getTile(int x, int y, int width){
	return y*width + x;
}

/*
Checks for a collision
x and y need to be in pixels!:D
*/
int checkCollision(int x, int y, int dx, int dy, u16* map){
	
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
		 val = map[2+getTile(cx>>3, cy>>3, map[0])]; 
		 if(val)
			 return val;
	}
	return val;
}

