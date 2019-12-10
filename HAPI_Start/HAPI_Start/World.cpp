#include "World.h"

std::shared_ptr<World> World::s_pWorld = nullptr;

void World::Init() {

	GRAPHICS->CreateWindow();
	BINARYTREE->CreateTree(m_cshNumLevels);
	LoadTextures();
	LoadScenes();

	m_pPlayer = new Player(Vec2(0,0));
	m_pInput = new Input();

	try {

		if (umapTextures.find(m_pPlayer->GetAlias()) != umapTextures.end());

	}
	catch (std::out_of_range& e) {

		throw e;
		return;

	}
	catch (...) {

		return;

	}

	m_pPlayer->SetTexture(*(umapTextures.at(m_pPlayer->GetAlias())));

}

void World::Loop() {

	while (HAPI.Update()) {

		GRAPHICS->ClearScreen();

		DrawRenderables();

	}

}

World::World() {



}

World::~World() {

	for (auto& x : umapTextures) delete x.second;
	for (auto& x : vecpScenes) delete x;

	delete m_pPlayer;
	delete m_pInput;

	vecpScenes.clear();
	umapTextures.clear();

}

void World::LoadTextures() {

	if (!FILEMANAGER->FileExists(FILEMANAGER->GetTextureFilepath())) return;
	std::string str = FILEMANAGER->GetTextureFilepath();
	CHapiXML xml = FILEMANAGER->GetTextureFilepath();

	std::vector<CHapiXMLNode*> nodes = xml.GetAllNodesWithName("Texture");

	for (auto& node : nodes) {

		CHapiXMLAttribute attr;

		if (!node->GetAttributeWithName("filepath", attr)) return;
		if (!node->GetAttributeWithName("alias", attr)) return;

		Texture* t = new Texture(node->GetAttributes()[0].AsString());

		t->LoadTexture();

		umapTextures.insert({ node->GetAttributes()[1].AsString(), t });

	}

}

void World::LoadScenes() {

	for (int i{ 0 }; i < BINARYTREE->GetTreeSize(); i++) {

		Scene* s = new Scene(i);
		Node* n = BINARYTREE->Search(i);

		auto lCheckNull = [&](Node* nn) { //check for valid nodes then return id

			if (nn == nullptr) return -1;

			return nn->m_nID;

		};

		if (nullptr != n) { //check for valid node

			s->SetPathways(n->m_nID,
				lCheckNull(n->m_nodeParent),
				lCheckNull(n->m_nodeLeft),
				lCheckNull(n->m_nodeRight));

		}

		vecpScenes.push_back(s);

		if (!FILEMANAGER->FileExists(FILEMANAGER->GetSceneFilepath(s->GetID()))) return;

		CHapiXML xml = (FILEMANAGER->GetSceneFilepath(s->GetID()));

		std::vector<CHapiXMLNode*> nodes = xml.GetAllNodesWithName("Object");

		for (auto& node : nodes) {

			CHapiXMLAttribute attr;

			//if (!node->GetAttributeWithName("alias", attr)) return;

			auto vecAttr = node->GetAttributes();

			WorldEntity* wo = new WorldEntity(vecAttr[0].AsInt(), vecAttr[1].AsInt(), vecAttr[2].AsInt(), vecAttr[3].AsString(), vecAttr[4].AsInt());

			wo->SetTexture(*(umapTextures.at(
				wo->GetAlias()
			)));

			s->AddEntity(wo);

		}

	}

}

void World::DrawRenderables() const {

	for (auto& x : vecpScenes[m_shCurrentScene]->GetEntities()) GRAPHICS->Draw(*x);

	GRAPHICS->Draw(*m_pPlayer);

}
