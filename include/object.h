#ifndef OBJECT_H
#define OBJECT_H

#include <feos.h>

typedef int (*COLFUNCPTR)(int mask, int inX, int inY);

typedef struct {
	u16 width, height;
	u16 x, y;
	s16 dx, dy;
	COLFUNCPTR collCallback;
}OBJECT;

#endif
