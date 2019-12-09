#include "World.h"

std::shared_ptr<World> World::s_pWorld = nullptr;

void World::Init() const {

	GRAPHICS->CreateWindow();

}

void World::Loop() {

	while (HAPI.Update()) {



	}

}

World::World() {



}


World::~World()
{
}
