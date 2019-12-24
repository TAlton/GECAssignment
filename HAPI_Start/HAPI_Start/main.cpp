#include "World.h"

void HAPI_Main() {

	WORLD->Init();
	WORLD->Loop();

}

/*

Check controller works

fix lerp

change collisions to rectangles simply use entity->GetRect - translate rect to screen space - Rect->Overlap

add patrol paths - defined in constructor and in xml, if shooting stop patrol

add explosions if bullet collided set to inactive spawn explosion at bullet location


*/