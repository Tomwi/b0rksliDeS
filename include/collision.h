#ifndef COLLISION_H
#define COLLISION_H

#include "collision.h"
#include "object.h"

#define COLTILE_SZ (16)

#define U_COLLISION (BIT(0))
#define D_COLLISION (BIT(1))
#define L_COLLISION (BIT(2))
#define R_COLLISION (BIT(3))

inline int getTile(int x, int y, int width);
int checkMapCollision(OBJECT* obj, int dx, int dy, u16* map);

#endif
