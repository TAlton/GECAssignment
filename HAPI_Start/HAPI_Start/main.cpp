#include "World.h"

void HAPI_Main() {

	WORLD->Init();
	WORLD->Loop();

}

/*

fix double jumping by adding is colliding and w = true to set jumping to true
fix sticking into wall unsure of issue
change level flags
shooting
enemy
collision with bullets 
rotate inactive keep ptr of first inactive

*/