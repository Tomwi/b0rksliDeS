#ifndef PLAYER_H
#define PLAYER_H

#include "level.h"
#include "object.h"

#define B0RKWIN_WIDTH	(32)
#define B0RKWIN_HEIGHT	(32)

extern OBJECT b0rkwin;

void initPlayer(void);
void updatePlayer(LEVEL*);
void deinitPlayer(void);

#endif
