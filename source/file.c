#include "file.h"

far_t hArc;

FEOSINIT static void _initFar()
{
	hArc = FAR_OpenSelf();
}

FEOSFINI static void _deinitFar()
{
	if (hArc) FAR_Close(hArc);
}

void * bufferFile(const char * file, int * sz)
{
	if (!hArc) return NULL;

	farfile_t hFile = FAR_GetFile(hArc, file);
	if (!hFile) return NULL;
	size_t size;
	if(sz)
		*sz = FAR_FileGetSize(hFile);
	void* mem = malloc(size = FAR_FileGetSize(hFile));
	if (!mem)
	{
		FAR_FileClose(hFile);
		return NULL;
	}
	FAR_FileRead(hFile, mem, size);
	FAR_FileClose(hFile);
	DC_FlushRange(mem, size);
	return mem;
}
