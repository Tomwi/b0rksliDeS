#include <feos.h>
#include <stdio.h>
#include <maxmod9.h>
#include <far.h>
#include "audio.h"
#include "soundbank.h"

/* 
 * TODO:
 * - move far stuff to a seperate file
 * - use another module than the example
 */

far_t hFar;

FEOSINIT void loadFar()
{
	hFar = FAR_OpenSelf();
}

FEOSFINI void closeFar()
{
	if (hFar) FAR_Close(hFar);
}

int initAudio(void){
	if(!mmIsARM7Loaded())
		return 0;
	// Init Maxmod with default settings (loading from FAR)
	mmInitDefaultFAR(hFar, "/soundbank.bin");
	
	// Load the module
	mmLoad(MOD_FLATOUTLIES);

	// Start playing module
	mmStart(MOD_FLATOUTLIES, MM_PLAY_LOOP);
	return 1;
}

void deinitAudio(void){
	mmStop();
	mmUnload(MOD_FLATOUTLIES);
	mmUnloadSoundbank();
}
