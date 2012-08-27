#ifndef COLLISION_H
#define COLLISION_H


#include "level.h"
#include "object.h"
/* Callbacks for collision will handle the collision mask and return non-zero if
 * the collision checker should stop
 */
#define COLTILE_SZ (16)

#define U_COLLISION (BIT(0))
#define D_COLLISION (BIT(1))
#define R_COLLISION (BIT(2))
#define L_COLLISION (BIT(3))


inline int getTile(int x, int y, int width);
int checkMapCollision(OBJECT* obj, LEVEL* lvl);


#endif
