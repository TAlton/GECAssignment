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
#include "UserInterface.h"
#include "Sound.h"

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
	void RestartGame();

private:

	World();

	static std::shared_ptr<World> s_pWorld;

	std::shared_ptr<Player> m_pPlayer = nullptr;
	std::shared_ptr<Input> m_pInput = nullptr;

	std::unordered_map<std::string, Texture*> m_umapTextures;

	std::vector<Texture*> m_vecpBackgrounds;
	std::vector<Scene*> m_vecpScenes;
	std::vector<Bullet*> m_vecpBullets;
	std::vector<UserInterface*> m_vecpUI;

	Enemy* m_pBossEnemy = nullptr;

	const unsigned short m_cshNumLevels{ 10 };
	short m_shCurrentScene{ 0 };

	unsigned long m_ulCurrentTime{ 0 },
		m_ulFrameTime{ 0 };

	long m_lScore{ 999999 };

	bool m_bGameOver{ false },
		m_bLoadTexture{ false },
		m_bLoadScene{ false },
		m_bLoadUI{ false };

	void LoadTextures();
	void LoadScenes();
	void LoadUI();
	void DrawRenderables() const;
	void GetInput();
	void UpdateEntities();
	bool CheckCollision();
	void CalcFrameTime();
	void UpdateLevel();
	void SpawnBullet(bool dir, Entity& e); //add in param for shooter
	//void SpawnBullet(Vec2 v);
	void UpdateScore();
	void ClearContainers();

};

#define WORLD World::GetInstance()