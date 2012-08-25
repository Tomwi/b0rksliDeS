
//{{BLOCK(level0)

//======================================================================
//
//	level0, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 25 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 1600 + 2048 = 4160
//
//	Time-stamp: 2012-08-24, 11:50:15
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LEVEL0_H
#define GRIT_LEVEL0_H

#define level0TilesLen 1600
extern const unsigned int level0Tiles[400];

#define level0MapLen 2048
extern const unsigned short level0Map[1024];

#define level0PalLen 512
extern const unsigned short level0Pal[256];

#endif // GRIT_LEVEL0_H

//}}BLOCK(level0)