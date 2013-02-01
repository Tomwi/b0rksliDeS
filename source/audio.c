#include <feos.h>
#include <stdio.h>
#include <maxmod9.h>
#include <far.h>

#include "audio.h"
#include "file.h"

#include "soundbank.h"

int initAudio(void){
	if(!mmIsARM7Loaded())
		return 0;
	// Init Maxmod with default settings (loading from FAR)
	mmInitDefaultFAR(hArc, "/soundbank.bin");
	
	// Load the module
	mmLoad(MOD_FLATOUTLIES);

	// Start playing module
	//mmStart(MOD_FLATOUTLIES, MM_PLAY_LOOP);
	return 1;
}

void deinitAudio(void){
	mmStop();
	mmUnload(MOD_FLATOUTLIES);
	mmUnloadSoundbank();
}
