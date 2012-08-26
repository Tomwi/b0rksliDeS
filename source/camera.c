
#include <feos.h>

#include "background.h"

#include "input.h"
#include "player.h"



void updateScroll(BG_INF* inf, int dx, int dy) {
		
	if((inf->bgx + SCREEN_WIDTH) > inf->mapwidth || inf->bgx < 0){
		dx = 0;} //Dont scroll the map because its big
	
	scroll(inf->bgx, inf->bgy, dx, dy, inf);
	inf->bgx+= dx;
	inf->bgy+= dy;
	bgSetScroll (inf->bgId, inf->bgx, inf->bgy);
	bgUpdate();
}
