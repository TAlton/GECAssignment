#include "Scene.h"



Scene::~Scene(){

	for (auto& x : m_vecpenEntities) delete x;
	for (auto& x : m_vecpenBackground) delete x;

}

void Scene::AddEntity(Entity* e) {

	m_vecpenEntities.push_back(e);

}

void Scene::AddBackground(Entity* e) {

	m_vecpenBackground.push_back(e);

}
