#include <feos.h>
#include "input.h"

int keysHold, keysPres, keysReleased;
styluspos_t stylus;

void readInput(void){
	scanKeys();
	FeOS_GetStylusPos(&stylus);
	keysHold = keysHeld();
	keysPres = keysDown();
	keysReleased = keysUp();
}

void parseInput(int* dx, int* dy){
	*dx = 0;
	*dy = 0;
	if(keysHold & KEY_RIGHT){ 
		*dx = bork_speed;}
	else if(keysHold & KEY_LEFT){
		*dx = -1*bork_speed;}
			
	
	if(keysHold & KEY_UP)
		*dy = -1*bork_speed;
	else if(keysHold & KEY_DOWN)
		*dy = bork_speed;
}
