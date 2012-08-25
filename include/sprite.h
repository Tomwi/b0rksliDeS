#ifndef T_SPRITE_H
#define T_SPRITE_H

#include <feos.h>

#include "video.h"

#define states(n) ((n)>0? FeOS_GetMainOAM():FeOS_GetSubOAM())

/* Straight from libnds */
#define SPRITE_SIZE_SHAPE(size) (((size) >> 12) & 0x3)
#define SPRITE_SIZE_SIZE(size)  (((size) >> 14) & 0x3)
#define SPRITE_SIZE_PIXELS(size) (((size) & 0xFFF) << 5)

#define SPRITE_SIZE_BYTES(size,pal) (SPRITE_SIZE_PIXELS((size))>>(1-pal))

extern hword_t * const const spritePalettes[2];

typedef struct {
    u8 * tileaddr;
    hword_t counter;
    hword_t size;
    u8 curFrame, animating;
    u8 start, stop, time;
} SPRITE_INFO;

hword_t * loadFrame(hword_t * gfx, int color, int size, int index, bool screen);
bool loadPalette(u8 no, void * data, bool small, bool screen);
bool loadExtPalette(u8 no, void * data, bool screen);
void initSprite(u8 no, u8 pal, hword_t name, int size, int format,  bool screen);
void setSprXY(int no, hword_t x, hword_t y, bool screen);
void setFrame(hword_t * ptr, bool hidden, int no, int screen);
void setSpriteVisiblity(bool hidden, int no, int screen);
void cloneSprite(int no, int toClone, int screen);
inline void setHflip(int no, bool flip, bool screen);

#endif



