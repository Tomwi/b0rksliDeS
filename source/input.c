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
		*dx = 1;}
	else if(keysHold & KEY_LEFT){
		*dx = -1;}
			
	
	if(keysHold & KEY_UP)
		*dy = -1;
	else if(keysHold & KEY_DOWN)
		*dy = 1;
		
	
	
}
