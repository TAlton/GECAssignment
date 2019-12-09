#include "World.h"

std::shared_ptr<World> World::s_pWorld = nullptr;

void World::Init() const {

	GRAPHICS->CreateWindow();
	BINARYTREE->CreateTree(m_cshNumLevels);

}

void World::Loop() {

	while (HAPI.Update()) {



	}

}

World::World() {



}

void World::LoadTextures() {

	if (!FILEMANAGER->FileExists(FILEMANAGER->GetTextureFilepath())) return;
	
	CHapiXML xml = FILEMANAGER->GetTextureFilepath();

	std::vector<CHapiXMLNode*> nodes = xml.GetAllNodesWithName("Texture");

	for (auto& node : nodes) {

		CHapiXMLAttribute attr;

		if (!node->GetAttributeWithName("filepath", attr)) return;
		if (!node->GetAttributeWithName("alias", attr)) return;

		std::shared_ptr<Texture> t = std::make_shared<Texture>(node->GetAttributes()[0].AsString());

		umapTextures.insert({ node->GetAttributes()[1].AsString(), t });

	}

}


World::~World()
{
}
