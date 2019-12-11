#include "World.h"

void HAPI_Main() {

	WORLD->Init();
	WORLD->Loop();

}

/*

setup delta time
change level flags
shooting
enemy
collision with bullets 
rotate inactive keep ptr of first inactive

*/