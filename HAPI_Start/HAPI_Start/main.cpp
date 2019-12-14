#include "World.h"

void HAPI_Main() {

	WORLD->Init();
	WORLD->Loop();

}

/*

shooting ---- if input == left click shoort based on direction (check moveleft and right)
-----------update entities will cause bullet to move
enemy
collision with bullets 
---------if bullet collide stop moving play animation? set active to false when last anim frame is hit
---------------------------rotate inactive keep ptr of first inactive

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