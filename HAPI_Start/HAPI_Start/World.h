#pragma once

#include <unordered_map>

#include "Graphics.h"
#include "Texture.h"
#include "Player.h"
#include "Scene.h"
#include "BinaryTree.h"
#include "Physics.h"
#include "Input.h"
#include "Bullet.h"

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

	void Init();
	void Loop();

private:

	World();

	static std::shared_ptr<World> s_pWorld;

	std::shared_ptr<Player> m_pPlayer = nullptr;
	std::shared_ptr<Input> m_pInput = nullptr;

	std::unordered_map<std::string, Texture*> umapTextures;

	std::vector<Scene*> vecpScenes;
	std::vector<Bullet*> vecpBullets;

	const unsigned short m_cshNumLevels{ 10 };
	short m_shCurrentScene{ 0 };

	unsigned long m_ulCurrentTime{ 0 };
	unsigned long m_ulFrameTime;

	void LoadTextures();
	void LoadScenes();
	void DrawRenderables() const;
	void GetInput();
	void UpdateEntities();
	bool CheckCollision();
	void CalcFrameTime();
	void UpdateLevel();

};

#define WORLD World::GetInstance()