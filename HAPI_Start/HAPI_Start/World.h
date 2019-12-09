#pragma once

#include "Graphics.h"

class World
{
public:

	~World();

	static std::shared_ptr<World>& GetInstance() {

		if (!s_pWorld) {

			s_pWorld.reset(new World());

		}

		return s_pWorld;

	}

	void Init() const;
	void Loop();

private:

	World();

	static std::shared_ptr<World> s_pWorld;

};

#define WORLD World::GetInstance()