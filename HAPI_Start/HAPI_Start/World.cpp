#include "World.h"

std::shared_ptr<World> World::s_pWorld = nullptr;

void World::Init() {

	GRAPHICS->CreateWindow();
	BINARYTREE->CreateTree(m_cshNumLevels);
	LoadTextures();
	//LoadScenes();

	m_pPlayer = new Player(Vec2(0,0));
	m_pPlayer->SetTexture(*(umapTextures.at(m_pPlayer->GetAlias())));

}

void World::Loop() {

	while (HAPI.Update()) {



	}

}

World::World() {



}

World::~World() {

	for (auto& x : umapTextures) delete x.second;

	delete m_pPlayer;

	vecpScenes.clear();
	umapTextures.clear();

}

void World::LoadTextures() {

	if (!FILEMANAGER->FileExists(FILEMANAGER->GetTextureFilepath())) return;

	CHapiXML xml = FILEMANAGER->GetTextureFilepath();

	std::vector<CHapiXMLNode*> nodes = xml.GetAllNodesWithName("Textures");

	for (auto& node : nodes) {

		CHapiXMLAttribute attr;

		if (!node->GetAttributeWithName("filepath", attr)) return;
		if (!node->GetAttributeWithName("alias", attr)) return;

		Texture* t = new Texture(node->GetAttributes()[0].AsString());
		

		umapTextures.insert({ node->GetAttributes()[1].AsString(), t });

	}

}