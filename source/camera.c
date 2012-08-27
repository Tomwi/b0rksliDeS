#include <feos.h>
#include "camera.h"
#include "sprite.h"
#include "video.h"
#include "player.h"

#define CLAMP(n,l,u) ((n) = ((n) > (u) ? (u) : ((n)<(l) ? (l) : (n))))

void updateCamera(OBJECT* center, BG_INF* inf)
{

	int bgX = ( center->x + ( center->width - SCREEN_WIDTH)/2)  ;
	int bgY = ( center->y + ( center->height - SCREEN_HEIGHT)/2);
	CLAMP(bgX, 0, inf->mapwidth*8-SCREEN_WIDTH);
	CLAMP(bgY, 0, inf->mapHeight*8-SCREEN_HEIGHT);
	updateScroll(inf, bgX-inf->x, bgY-inf->y);

	/* TODO: hide the b0rkwin, when centered about another object and not in range */
	int b0rkX = b0rkwin.x - bgX;
	int b0rkY = b0rkwin.y - bgY;
	setSprXY(0, b0rkX, b0rkY, TOP_SCREEN);
}
