#pragma once

#include <HAPI_lib.h>

#include "Entity.h"
#include "FileManager.h"
#include "WorldEntity.h"
#include "Enemy.h"

using namespace HAPISPACE;

#define TOTALSCENES 3

class Scene {

	enum eScene : int { SCENE1 = 0, SCENE2, SCENE3,  BOSSSCENE };

public:

	Scene(const int index) { 

		if (BOSSSCENE == index) {

			m_shSceneID = index;

		}
		else {

			m_shSceneID = index % TOTALSCENES;

		}
	}
	~Scene();

	const int GetPrevScene() const { return this->m_shPrevScene; }
	const int GetNextSceneLeft() const { return this->m_shNextSceneLeft; }
	const int GetNextSceneRight() const { return this->m_shNextSceneRight; }
	const int GetID() const { return this->m_shSceneID; }
	void SetPathways(int id, int parent, int lChild, int rChild) { //applies the binary tree paths to the scene

		m_shID = id;
		m_shPrevScene = parent;
		m_shNextSceneLeft = lChild;
		m_shNextSceneRight = rChild;

	}

	std::vector<Entity*> GetEntities() const { return this->m_vecpEntities; }
	std::vector<Entity*> GetBackgrounds() const { return this->m_vecpBackground; }
	std::vector<Enemy*> GetEnemies() const { return this->m_vecpEnemy; }

	void AddEntity(Entity* e);
	void AddBackground(Entity* e);
	void AddEnemy(Enemy* e);

private:

	short m_shID{ -1 },
		m_shPrevScene{ -1 },
		m_shNextSceneLeft{ -1 },
		m_shNextSceneRight{ -1 },
		m_shSceneID{ -1 };

	std::vector<Entity*> m_vecpEntities;
	std::vector<Entity*> m_vecpBackground;
	std::vector<Enemy*> m_vecpEnemy;

};

