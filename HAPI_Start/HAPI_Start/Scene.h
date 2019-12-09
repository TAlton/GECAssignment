#pragma once

#include "Entity.h"
#include "FileManager.h"

class Scene {

	enum eScene : int { BOSSSCENE = 0, SCENE1, SCENE2, SCENE3 };

public:

	Scene(const short index) : m_shID(index) {}
	~Scene();

private:

	short m_shID{ 0 };


	std::vector<Entity*> m_vecpenEntities;

	void LoadScene(const int index);

};

