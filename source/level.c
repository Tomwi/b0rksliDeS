#include <string.h>
#include "level.h"


LEVEL* loadLevel(const char* name)
{
	/* Allocate a level structure and read the header */
	LEVEL* tmp = NULL;
	FILE* fp = NULL;
	if((tmp=malloc(sizeof(LEVEL)))==NULL)
		goto error;
		
	memset(tmp, 0, sizeof(LEVEL));
	
	if((fp = fopen(name, "rb"))==NULL)
		return NULL;
		
	fread(tmp, 1, sizeof(LEVEL_HDR), fp);
	int numMapEntries = tmp->hdr.width*tmp->hdr.height;
	#ifdef DEBUG
	
		printf("width & height; %d & %d\n", tmp->hdr.width, tmp->hdr.height);
		printf("reading %d bytes\n", 0);
	
	#endif
	/* Allocate the collision- and tilemap
	 * The collision map uses 16x16 tiles, whereas the tilemap
	 * uses 8x8. Map width and height are measured in 16x16 tiles.
	 * This is why we allocate 4x the size of a collision map for the 
	 * tilemap (length*2*width*2 = sizeof(colmap)*4)
	*/
	tmp->colMap = malloc(numMapEntries*sizeof(u16)*5);
	if(tmp->colMap==NULL)
		goto error;
	tmp->tileMap = &tmp->colMap[numMapEntries];
	fread(tmp->colMap, 1, numMapEntries*sizeof(u16)*5, fp);
	fclose(fp);
	return tmp;
error:
	freeLevel(tmp);
	fclose(fp);
	return NULL;
}

/*
 * DOESN't unload the lvl struct, as this may be static
 */
void freeLevel(LEVEL* lvl){
	// will free both colmap and tilemap as they're allocated in one go
	free(lvl->colMap);
}
