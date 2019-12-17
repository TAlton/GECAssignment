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

	try {

		umapTextures.find(m_pPlayer->GetAlias()) != umapTextures.end(); //checks if the texture exists

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
		GetInput();
		UpdateEntities();
		DrawRenderables();

	}

}

World::World() {



}

World::~World() {

	for (auto& x : umapTextures) delete x.second;
	for (auto& x : vecpScenes) delete x;
	for (auto& x : vecpBullets) delete x;

	vecpBullets.clear();
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

		Texture* t = new Texture(node->GetAttributes()[0].AsString(), node->GetAttributes()[2].AsInt());

		t->LoadTexture();

		umapTextures.insert({ node->GetAttributes()[1].AsString(), t });

	}

	for (int i{ 0 }; i < 100; i++) {

		Bullet* b = new Bullet(0, 0, 0, "bullet", ENEMY);
		vecpBullets.push_back(b);

	}
	for(auto& x : vecpBullets) x->SetTexture(*(umapTextures.at(
								x->GetAlias()
								)));
	
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

			if (NOCOLLIDE == vecAttr[4].AsInt()) {

				s->AddBackground(wo);

			}
			else {

				s->AddEntity(wo);

			}

		}

	}

}

void World::DrawRenderables() const {

	for (auto& x : vecpScenes[m_shCurrentScene]->GetBackground()) GRAPHICS->Draw(*x);
	for (auto& x : vecpScenes[m_shCurrentScene]->GetEntities()) GRAPHICS->Draw(*x); //draw background then entities
	for (auto& x : vecpBullets) {
		
		if (x->IsActive()) {

			GRAPHICS->Draw(*x);

		}
		else { break; }

	}

	GRAPHICS->Draw(*m_pPlayer);

}

void World::GetInput() {

	switch (m_pInput->GetKBInput()) { //keyboard input

	case 'W':
	case HK_SPACE:

		switch (m_pPlayer->GetJump()) { //nested switch for jumping

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

	switch (m_pInput->GetMouseInput()) {

	case LMB:
		if(m_pPlayer->Shoot(m_ulFrameTime))SpawnBullet(m_pPlayer->GetDirection());
		break;
	case RMB:
		break;
	case MMB:
		break;
	default:
		break;

	}

}

void World::UpdateEntities() {

	if (m_ulCurrentTime % 16 == 0) return; //16 is update every 1/60 of a second placeholder to be programmed in

	m_pPlayer->UpdateY(m_ulFrameTime);
	CheckCollision();

	for (auto& x : vecpBullets) {

		if (x->IsActive()) {

			x->Update(m_ulFrameTime);

		}
		else { break; }

	}

	m_pPlayer->UpdateX(m_ulFrameTime);
	CheckCollision();
	//necessary to check collision twice as the player will either stick to the floor or be able to go through walls

	m_ulScore -= m_ulCurrentTime / 1000;
	HAPI.RenderText(600, 0, HAPI_TColour::CYAN, std::to_string(m_ulScore), 24);

	if (m_pPlayer->GetHealth() <= 0 || m_ulScore <= 0) RestartGame();

}

bool World::CheckCollision() { //this is really ugly and needs cleaning up

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
	//general collision checking for world objects
	for (auto& x : vecpScenes[m_shCurrentScene]->GetBackground()) {

		const short e_x1 = x->GetPosition().x;
		const short e_y1 = x->GetPosition().y;
		const short e_x2 = x->GetPosition().x + x->GetWidth();
		const short e_y2 = x->GetPosition().y + x->GetHeight();

		if (x1 < e_x2 && x2 > e_x1 &&
			y1 < e_y2 && y2 > e_y1) {

			if ('E' == m_pInput->GetKBInput() && "doorLeft" == x->GetAlias() && vecpScenes[m_shCurrentScene]->GetNextSceneLeft() != -1) 
				m_shCurrentScene = vecpScenes[m_shCurrentScene]->GetNextSceneLeft();
			if ('E' == m_pInput->GetKBInput() && "doorRight" == x->GetAlias() && vecpScenes[m_shCurrentScene]->GetNextSceneRight() != -1)
				m_shCurrentScene = vecpScenes[m_shCurrentScene]->GetNextSceneRight();
			if ('E' == m_pInput->GetKBInput() && "doorPrev" == x->GetAlias() && vecpScenes[m_shCurrentScene]->GetPrevScene() != -1)
				m_shCurrentScene = vecpScenes[m_shCurrentScene]->GetPrevScene();

		}

	}  
	//collision checking for doors
	for (int i{ 0 }; i < vecpBullets.size(); i++) {

		if (false == vecpBullets[i]->IsActive()) break; //if bullet isnt active do nothing

		const short x_1 = vecpBullets[i]->GetPosition().x;
		const short y_1 = vecpBullets[i]->GetPosition().y;
		const short x_2 = vecpBullets[i]->GetPosition().x + vecpBullets[i]->GetWidth();
		const short y_2 = vecpBullets[i]->GetPosition().y + vecpBullets[i]->GetHeight();

		for (auto& y : vecpScenes[m_shCurrentScene]->GetEntities()) {

			const short e_x1 = y->GetPosition().x;
			const short e_y1 = y->GetPosition().y;
			const short e_x2 = y->GetPosition().x + y->GetWidth();
			const short e_y2 = y->GetPosition().y + y->GetHeight();

			if (x_1 < e_x2 && x_2 > e_x1 &&
				y_1 < e_y2 && y_2 > e_y1) {

				vecpBullets[i]->SetActive(false);
				auto index = vecpBullets.begin() + i;
				std::rotate(index, index + 1, vecpBullets.end()); //rotate to the end of the vector for caching and breaking

			}

		 }

	}
	//collision checking for bullet against world objects
	for (int i{ 0 }; i < vecpBullets.size(); i++) {

		if (false == vecpBullets[i]->IsActive() || PLAYER == vecpBullets[i]->GetSide()) break; //if bullet isnt active do nothing

		const short x_1 = vecpBullets[i]->GetPosition().x;
		const short y_1 = vecpBullets[i]->GetPosition().y;
		const short x_2 = vecpBullets[i]->GetPosition().x + vecpBullets[i]->GetWidth();
		const short y_2 = vecpBullets[i]->GetPosition().y + vecpBullets[i]->GetHeight();

		if (x_1 < x2 && x_2 > x1 &&
			y_1 < y2 && y_2 > y1) {

			vecpBullets[i]->SetActive(false);
			auto index = vecpBullets.begin() + i;
			std::rotate(index, index + 1, vecpBullets.end()); //rotate to the end of the vector for caching and breaking
			m_pPlayer->Damage(vecpBullets[i]->GetDamage());

		}

	}
	//collision checking for bullet against player

	m_pPlayer->Collided(false);
	return false;

}

void World::CalcFrameTime() {

	const unsigned long ulNewTime = HAPI.GetTime(); //calculates current time and time to run frame
	m_ulFrameTime = ulNewTime - m_ulCurrentTime;
	m_ulCurrentTime = ulNewTime;

}

void World::UpdateLevel() {

}

void World::SpawnBullet(bool dir) { //should take in a reference to the spawner

	bool bFoundBullet{ false };

	do  {

		for (int i{ 0 }; i < vecpBullets.size(); i++) {
			
			if (false == vecpBullets[i]->IsActive()) {

				bFoundBullet = true;
				vecpBullets[i]->SetDirection(dir);
				vecpBullets[i]->SetActive(true);
				vecpBullets[i]->SetSide(PLAYER);
				bFoundBullet = !bFoundBullet;
				vecpBullets[i]->SetPosition(m_pPlayer->GetPosition());
				return;

			}
			
		}

		bFoundBullet = true;
		int i = vecpBullets.size() - 1;
		vecpBullets[i]->SetActive(true);
		vecpBullets[i]->SetSide(PLAYER);
		bFoundBullet = !bFoundBullet;
		vecpBullets[i]->SetPosition(m_pPlayer->GetPosition());
		return;

	} while (!bFoundBullet);

}

void World::RestartGame() {

	/*
	
	reset all positions and scores
	reload binary tree 

	*/

}

//
//{
//	auto it = v.begin() + itemIndex;
//	std::rotate(it, it + 1, v.end());
//}
