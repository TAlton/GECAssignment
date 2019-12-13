#include "World.h"

std::shared_ptr<World> World::s_pWorld = nullptr;

void World::Init() {

	GRAPHICS->CreateWindow();
	BINARYTREE->CreateTree(m_cshNumLevels);
	LoadTextures();
	LoadScenes();

	m_pPlayer = std::make_shared<Player>(Vec2(0,0));
	m_pInput = std::make_shared<Input>();

	m_ulCurrentTime = HAPI.GetTime();

	vecpBullets.resize(100);

	try {

		umapTextures.find(m_pPlayer->GetAlias()) != umapTextures.end();

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

		CalcFrameTime();
		GRAPHICS->ClearScreen();

		UpdateEntities();

		DrawRenderables();

		UpdateLevel();

	}

}

World::World() {



}

World::~World() {

	for (auto& x : umapTextures) delete x.second;
	for (auto& x : vecpScenes) delete x;

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

			auto vecAttr = node->GetAttributes();

			if (!node->GetAttributeWithName("Health", attr)) return;
			if (!node->GetAttributeWithName("Position_X", attr)) return;
			if (!node->GetAttributeWithName("Position_Y", attr)) return;
			if (!node->GetAttributeWithName("TextureAlias", attr)) return;
			if (!node->GetAttributeWithName("Side", attr)) return;


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

void World::GetInput() {

	switch (m_pInput->GetKBInput()) {

	case 'W':
	case HK_SPACE:

		switch (m_pPlayer->GetJump()) {

		case true:
			break;
		case false:
			m_pPlayer->SetJump(true);
			break;
		default:
			break;

		}

		break;
	case 'A':
		m_pPlayer->SetState(MOVELEFT);
		break;

	case 'D':
		m_pPlayer->SetState(MOVERIGHT);
		break;

	default:
		m_pPlayer->SetState(IDLE);
		break;

	}

}

void World::UpdateEntities() {

	if (m_ulCurrentTime % 16 == 0) return;

	m_pPlayer->UpdateY(m_ulFrameTime);
	CheckCollision();

	GetInput();

	m_pPlayer->UpdateX(m_ulFrameTime);
	CheckCollision();
	//necessary to check collision twice as the player will either stick to the floor or be able to go through walls

}

bool World::CheckCollision() {

	const short x1 = m_pPlayer->GetPosition().x;
	const short y1 = m_pPlayer->GetPosition().y;
	const short x2 = m_pPlayer->GetPosition().x + m_pPlayer->GetWidth();
	const short y2 = m_pPlayer->GetPosition().y + m_pPlayer->GetHeight();

	for (auto& x : vecpScenes[m_shCurrentScene]->GetEntities()) {

		const short e_x1 = x->GetPosition().x;
		const short e_y1 = x->GetPosition().y;
		const short e_x2 = x->GetPosition().x + x->GetWidth();
		const short e_y2 = x->GetPosition().y + x->GetHeight();

		if (x1 < e_x2 && x2 > e_x1 &&
			y1 < e_y2 && y2 > e_y1) { //checks if rectangle one intersects rectangle 2

			m_pPlayer->Collided(true);
			return true;
		}

	}

	m_pPlayer->Collided(false);
	return false;

}

void World::CalcFrameTime() {

	const unsigned long ulNewTime = HAPI.GetTime(); //calculates current time and time to run frame
	m_ulFrameTime = ulNewTime - m_ulCurrentTime;
	m_ulCurrentTime = ulNewTime;

}

void World::UpdateLevel() {

	//if collide with left door go left etc etc

	for (auto& x : vecpBullets) x->SetActive(false);

}
