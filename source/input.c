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
