#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::LoadScene(const int index) {

	FILEMANAGER->GetSceneFilepath(index);

}
