#include "World.h"

void HAPI_Main() {

	WORLD->Init();
	WORLD->Loop();

}

/*

implement shooting and interacting for controller

jumping error reoccured where holding jump sticks to a surface

fix lerp

change collisions to rectangles simply use entity->GetRect - translate rect to screen space - Rect->Overlap

add patrol paths - defined in constructor and in xml, if shooting stop patrol

add explosions if bullet collided set to inactive spawn explosion at bullet location


*/