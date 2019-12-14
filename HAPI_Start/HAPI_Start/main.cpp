#include "World.h"

void HAPI_Main() {

	WORLD->Init();
	WORLD->Loop();

}

/*

enemy

win lose conditions ---- kill boss or die
score = time in seconds + missing health * 100


ADDITIONS

falling background
adding boss enemy 
pickups
decent textures
----------decent anims
fix Lerp 
main menu for difficulty


*/