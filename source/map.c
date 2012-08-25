#include "map.h"

/* 
 * The map format used by b0rksliDeS is really simple:
 * it starts with the width and height (2 halfwords). The actual
 * map data is behind this 'header'
 */
u16* loadMap(const char* name)
{
	FILE* fp = fopen(name, "rb");
	if(!fp)
		return NULL;
	u16* data = malloc(sizeof(u16)*2);
	if(!data)
		goto error;
	fread(data, 1, sizeof(u16)*2, fp);
	int mapSz = sizeof(u16)*data[1]*data[0];
	void* temp = realloc(data, mapSz*2+sizeof(u16)*2);
	if(!temp)
		goto error;

	data = temp;
	fread(&data[2], 1, mapSz*2, fp);
	fclose(fp);
	return data;
error:
	free(data);
	fclose(fp);
	return NULL;
}
