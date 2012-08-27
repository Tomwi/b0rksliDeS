#ifndef CAMERA_H
#define CAMERA_H

#include "background.h"
#include "object.h"
#include "level.h"
/* 
 * Will center the level around an object which may be the b0rkwin
 * but just as well an invisbile object
 */
void updateCamera(OBJECT* center, BG_INF* inf);

#endif
