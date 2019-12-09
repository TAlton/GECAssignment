#pragma once

#include <unordered_map>

#include "Graphics.h"
#include "Texture.h"
#include "Scene.h"
#include "BinaryTree.h"

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

	std::unordered_map<std::string, std::shared_ptr<Texture>> umapTextures;

	std::vector<std::shared_ptr<Scene>> vecpScenes;

	const unsigned short m_cshNumLevels{ 10 };

	void LoadTextures();

};

#define WORLD World::GetInstance()