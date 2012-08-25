#include <string.h>
#include "sprite.h"

hword_t * const const spritePalettes[2] = {
	SPRITE_PALETTE_SUB,
	SPRITE_PALETTE,
};

hword_t * loadFrame(hword_t * gfx, int color, int size, int index, bool screen)
{
	int bytes = SPRITE_SIZE_BYTES(size, color);
	hword_t *temp = oamAllocateGfx(states(screen), size, color);
	if(temp) {
		dmaCopy(&gfx[(bytes*index)>>1], temp, bytes);
	}
	return temp;
}

SPRITE_INFO sprInf[2][128];

bool loadPalette(u8 no, void * data, bool small, bool screen)
{

	if (data) {
		// 16 color palette
		if (small) {
			dmaCopy(data, spritePalettes[screen]+(no*16), 32);
		}
		// 256 color palette
		else {
			dmaCopy(data, spritePalettes[screen], 512);
		}
	}
	return false;
}

bool loadExtPalette(u8 no, void * data, bool screen)
{
	if (data) {
		if (screen) {
			vramSetBankF(VRAM_F_LCD);
			dmaCopy(data, VRAM_F_EXT_SPR_PALETTE[no * 256], 512);
			vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
			return true;
		} else {
			vramSetBankI(VRAM_I_LCD);
			dmaCopy(data, VRAM_I_EXT_SPR_PALETTE[no * 256], 512);
			vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
			return true;
		}
	}
	return false;
}

void initSprite(u8 no, u8 pal, hword_t name, int size, int format,  bool screen)
{

	SpriteEntry* oamMem = (SpriteEntry*)FeOS_GetOAMMemory(states(screen));
	sprInf[screen][no].size = SPRITE_SIZE_PIXELS(size);
	oamMem[no].shape = SPRITE_SIZE_SHAPE(size);
	oamMem[no].size = SPRITE_SIZE_SIZE(size);
	oamMem[no].palette = pal;
	oamMem[no].isHidden = false;
	oamMem[no].gfxIndex  = name;
	oamMem[no].colorMode = format;
}

void setSprXY(int no, hword_t x, hword_t y, bool screen)
{
	SpriteEntry* oamMem = (SpriteEntry*)FeOS_GetOAMMemory(states(screen));
	oamMem[no].x = x;
	oamMem[no].y = y;
}

void setFrame(hword_t * ptr, bool hidden, int no, int screen)
{
	SpriteEntry* oamMem = (SpriteEntry*)FeOS_GetOAMMemory(states(screen));
	oamMem[no].gfxIndex = oamGfxPtrToOffset(states(screen), ptr);
	oamMem[no].isHidden = hidden;
}

void setSpriteVisiblity(bool hidden, int no, int screen)
{
	SpriteEntry* oamMem = (SpriteEntry*)FeOS_GetOAMMemory(states(screen));
	oamMem[no].isHidden = hidden;
}

void cloneSprite(int no, int toClone, int screen)
{
	SpriteEntry* oamMem = (SpriteEntry*)FeOS_GetOAMMemory(states(screen));
	memcpy(&oamMem[no], &oamMem[toClone], sizeof(SpriteEntry));
}

void setHflip(int no, bool flip, bool screen)
{
	SpriteEntry* oamMem = (SpriteEntry*)FeOS_GetOAMMemory(states(screen));
	oamMem[no].hFlip = flip;
}
