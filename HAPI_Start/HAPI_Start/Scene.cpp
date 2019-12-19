#include "Scene.h"



Scene::~Scene(){

	for (auto& x : m_vecpEntities) delete x;
	for (auto& x : m_vecpBackground) delete x;
	for (auto& x : m_vecpEnemy) delete x;

	m_vecpEnemy.clear();

}

void Scene::AddEntity(Entity* e) {

	m_vecpEntities.push_back(e);

}

void Scene::AddBackground(Entity* e) {

	m_vecpBackground.push_back(e);

}

void Scene::AddEnemy(Enemy* e) {

	m_vecpEnemy.push_back(e);

}
