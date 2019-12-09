#include "Scene.h"



Scene::~Scene()
{
}

void Scene::LoadScene(const int index) {

	if (!FILEMANAGER->FileExists(FILEMANAGER->GetSceneFilepath(index))) return;

	CHapiXML xml = FILEMANAGER->GetSceneFilepath(index);

	std::vector<CHapiXMLNode*> nodes = xml.GetAllNodesWithName("Scene");

	for (auto& node : nodes) {

		CHapiXMLAttribute attr;

		if (!node->GetAttributeWithName("Alias", attr)) return;

		auto vecAttr = node->GetAttributes();

		std::shared_ptr<WorldEntity> we = std::make_shared<Worldentity>() //add ctor params

	}


}
