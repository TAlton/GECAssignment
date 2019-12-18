#include "World.h"

void HAPI_Main() {

	WORLD->Init();
	WORLD->Loop();

}

/*

enemy

win lose conditions ---- kill boss or die

health bar
----- change health bar width based on hp


ADDITIONS

move file handling into filemanager completely ---- move all xml files into one?
falling background
adding boss enemy 
pickups

fix Lerp 
main menu for difficulty


*/