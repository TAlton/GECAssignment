#include "World.h"

std::shared_ptr<World> World::s_pWorld = nullptr;
bool World::m_bLoadScene = false; //prevent loading of data twice
bool World::m_bLoadTexture = false;
bool World::m_bLoadUI = false;

void World::Init() {

	GRAPHICS->CreateWindow();
	BINARYTREE->CreateTree(m_cshNumLevels);
	LoadTextures();
	SOUND->LoadSound();
	LoadScenes();
	LoadUI();

	m_pPlayer = std::make_shared<Player>(Vec2(0,0));
	m_pInput = std::make_shared<Input>();

	m_ulCurrentTime = HAPI.GetTime();

	try {

		if(!(m_umapTextures.find(m_pPlayer->GetAlias()) != m_umapTextures.end())) return; //checks if the texture exists
		m_pPlayer->SetTexture(*(m_umapTextures.at(m_pPlayer->GetAlias())));

	}
	catch (std::out_of_range& e) {

		throw e;
		return;

	}
	catch (...) {

		return;

	}

}

void World::Loop() {

	while (HAPI.Update()) {

		CalcFrameTime();
		GRAPHICS->ClearScreen();
		GetInput();
		UpdateEntities();
		UpdateScore();
		DrawRenderables();

	}

}

World::World() {



}

World::~World() { //this could all be avoided with smart pointers, not a priority fix

	for (auto& x : m_umapTextures) delete x.second;
	for (auto& x : m_vecpScenes) delete x;
	for (auto& x : m_vecpBullets) delete x;
	for (auto& x : m_vecpUI) delete x;
	for (auto& x : m_vecpBackgrounds) delete x;
	for (auto& x : m_vecpEnemy) delete x;

	m_vecpEnemy.clear();
	m_vecpBackgrounds.clear();
	m_vecpUI.clear();
	m_vecpBullets.clear();
	m_vecpScenes.clear();
	m_umapTextures.clear();

}

void World::LoadTextures() { //checks if a file exists extracts xml nodes and loads them as textures, placed bullet load in here to prevent memory alloc in loop

	if (m_bLoadTexture) return;
	m_bLoadTexture = true;

	if (!FILEMANAGER->FileExists(FILEMANAGER->GetTextureFilepath())) return;
	std::string str = FILEMANAGER->GetTextureFilepath();
	CHapiXML xml = FILEMANAGER->GetTextureFilepath();

	std::vector<CHapiXMLNode*> nodes = xml.GetAllNodesWithName("Texture");

	for (auto& node : nodes) {

		CHapiXMLAttribute attr;

		if (!node->GetAttributeWithName("filepath", attr)) return;
		if (!node->GetAttributeWithName("alias", attr)) return;

		if (node->GetAttributeWithName("isBackground", attr, false)) { //loads into a seperate umap if it has the isbackground attribute

			Texture* t = new Texture(node->GetAttributes()[0].AsString(), node->GetAttributes()[2].AsInt(), node->GetAttributes()[3].AsBool());
			t->LoadTexture();

			m_vecpBackgrounds.push_back(t);
			continue;

		}

		Texture* t = new Texture(node->GetAttributes()[0].AsString(), node->GetAttributes()[2].AsInt());

		t->LoadTexture();

		m_umapTextures.insert({ node->GetAttributes()[1].AsString(), t });

	}

	for (int i{ 0 }; i < 100; i++) {

		Bullet* b = new Bullet(0, 0, 0, "bullet", ENEMY);
		m_vecpBullets.push_back(b);

	}

	try {

		m_umapTextures.find(m_vecpBullets[0]->GetAlias()) != m_umapTextures.end(); //checks if the texture exists

	}
	catch (std::out_of_range & e) {

		throw e;
		return;

	}
	catch (...) {

		return;

	}

	for (auto& x : m_vecpBullets) {

		x->SetTexture(*(m_umapTextures.at(
			x->GetAlias()
		)));

	}
	
}

void World::LoadScenes() {

	if (m_bLoadScene) return;
	m_bLoadScene = true;

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

		m_vecpScenes.push_back(s);

		if (!FILEMANAGER->FileExists(FILEMANAGER->GetSceneFilepath(s->GetID()))) return;

		CHapiXML xml = (FILEMANAGER->GetSceneFilepath(s->GetID()));

		std::vector<CHapiXMLNode*> nodes = xml.GetAllNodesWithName("Object");

		for (auto& node : nodes) { // loads objects

			CHapiXMLAttribute attr;

			auto vecAttr = node->GetAttributes();

			if (!node->GetAttributeWithName("Health", attr)) return;
			if (!node->GetAttributeWithName("Position_X", attr)) return;
			if (!node->GetAttributeWithName("Position_Y", attr)) return;
			if (!node->GetAttributeWithName("TextureAlias", attr)) return;
			if (!node->GetAttributeWithName("Side", attr)) return;

			WorldEntity* wo = new WorldEntity(vecAttr[0].AsInt(), vecAttr[1].AsInt(), vecAttr[2].AsInt(), vecAttr[3].AsString(), vecAttr[4].AsInt());

			wo->SetTexture(*(m_umapTextures.at(
				wo->GetAlias()
			)));

			if (NOCOLLIDE == vecAttr[4].AsInt()) { //if the object is not able to collide with anything load into seperate vector

				s->AddBackground(wo);

			}
			else {

				s->AddEntity(wo);

			}

		}

		nodes = xml.GetAllNodesWithName("Enemy");

		for (auto& node : nodes) { //loads enemies

			CHapiXMLAttribute attr;

			auto vecAttr = node->GetAttributes();

			if (!node->GetAttributeWithName("Health", attr)) return;
			if (!node->GetAttributeWithName("Position_X", attr)) return;
			if (!node->GetAttributeWithName("Position_Y", attr)) return;
			if (!node->GetAttributeWithName("TextureAlias", attr)) return;
			if (!node->GetAttributeWithName("Side", attr)) return;

			Enemy* e = new Enemy(vecAttr[0].AsInt(), vecAttr[1].AsInt(), vecAttr[2].AsInt(), vecAttr[3].AsString(), vecAttr[4].AsInt());

			e->SetTexture(*(m_umapTextures.at(
				e->GetAlias()
			)));

			m_vecpEnemy.push_back(e);

		}

	}

}

void World::LoadUI() { //potential to move this whole function into filemanager and pass in filepath, node name ?

	if (m_bLoadUI) return;
	m_bLoadUI = true;

	if (!FILEMANAGER->FileExists(FILEMANAGER->GetUIFilepath())) return;
	std::string str = FILEMANAGER->GetUIFilepath();
	CHapiXML xml = FILEMANAGER->GetUIFilepath();

	std::vector<CHapiXMLNode*> nodes = xml.GetAllNodesWithName("Object");

	for (auto& node : nodes) {

		CHapiXMLAttribute attr;

		UserInterface* ui = new UserInterface(0, node->GetAttributes()[0].AsInt(), node->GetAttributes()[1].AsInt(), node->GetAttributes()[2].AsString());

		ui->SetTexture(*(m_umapTextures.at(
			ui->GetAlias()
		)));

		m_vecpUI.push_back(ui);

	}

	

}

void World::DrawRenderables() const {

	//for (auto& x : m_vecpBackgrounds) GRAPHICS->DrawBackground(*x);
	for (auto& x : m_vecpScenes[m_shCurrentScene]->GetBackground()) GRAPHICS->Draw(*x); //scene background is uninteractable objects
	for (auto& x : m_vecpScenes[m_shCurrentScene]->GetEntities()) GRAPHICS->Draw(*x); //draw background then entities
	for (auto& x : m_vecpBullets) {
		
		if (x->IsActive()) {

			GRAPHICS->Draw(*x);

		}
		else { break; }

	}

	for (auto& x : m_vecpEnemy) GRAPHICS->Draw(*x);

	GRAPHICS->Draw(*m_pPlayer);

	for (auto& x : m_vecpUI) GRAPHICS->Draw(*x); //draw ui last has z priority

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

	switch (m_pInput->GetMouseInput()) { //mouse input

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

	do { //nested in a do while to prevent overrwriting or using goto

		if (HK_DIGITAL_A == m_pInput->GetControllerDigitalInput(0) || true == m_pPlayer->GetJump()) { //controller input for buttons and analog buttons
			m_pPlayer->SetJump(true);
		}
		if (-1 == m_pInput->GetControllerAnalogInput(0).x) {

			m_pPlayer->SetState(MOVELEFT);
			break;

		}
		if (1 == m_pInput->GetControllerAnalogInput(0).x) { 

			m_pPlayer->SetState(MOVERIGHT);
			break;
		}

		break;

	} while(true);

}

void World::UpdateEntities() {

	if (m_pPlayer->GetHealth() <= 0 || m_lScore <= 0) RestartGame(); //end game if player dies or score <= 0
	if (m_ulCurrentTime % 8 == 0) return; //16 is update every 1/60 of a second placeholder to be programmed in

	for (auto& x : m_vecpBullets) {

		if (x->IsActive()) {

			x->Update(m_ulFrameTime);

		}
		else { break; }

	}

	m_pPlayer->UpdateX(m_ulFrameTime);
	CheckCollision();
	m_pPlayer->UpdateY(m_ulFrameTime);
	CheckCollision();
	//necessary to check collision twice as the player will either stick to the floor or be able to go through walls
	//X then Y prevent clinging to walls, as Y applies falling velocity

}

bool World::CheckCollision() { //this is really ugly and needs cleaning up, or is it bucket collision will speed up as we wont check unnecessary objects

	const short x1 = m_pPlayer->GetPosition().x;
	const short y1 = m_pPlayer->GetPosition().y;
	const short x2 = m_pPlayer->GetPosition().x + m_pPlayer->GetWidth();
	const short y2 = m_pPlayer->GetPosition().y + m_pPlayer->GetHeight();

	for (auto& x : m_vecpScenes[m_shCurrentScene]->GetEntities()) {

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
	for (auto& x : m_vecpScenes[m_shCurrentScene]->GetBackground()) {

		const short e_x1 = x->GetPosition().x;
		const short e_y1 = x->GetPosition().y;
		const short e_x2 = x->GetPosition().x + x->GetWidth();
		const short e_y2 = x->GetPosition().y + x->GetHeight();

		if (x1 < e_x2 && x2 > e_x1 &&
			y1 < e_y2 && y2 > e_y1) {

			if ('E' == m_pInput->GetKBInput() && "doorLeft" == x->GetAlias() && m_vecpScenes[m_shCurrentScene]->GetNextSceneLeft() != -1) //use interact button whilst colliding with door
				m_shCurrentScene = m_vecpScenes[m_shCurrentScene]->GetNextSceneLeft();
			if ('E' == m_pInput->GetKBInput() && "doorRight" == x->GetAlias() && m_vecpScenes[m_shCurrentScene]->GetNextSceneRight() != -1)
				m_shCurrentScene = m_vecpScenes[m_shCurrentScene]->GetNextSceneRight();
			if ('E' == m_pInput->GetKBInput() && "doorPrev" == x->GetAlias() && m_vecpScenes[m_shCurrentScene]->GetPrevScene() != -1)
				m_shCurrentScene = m_vecpScenes[m_shCurrentScene]->GetPrevScene();

		}

	}  
	//collision checking for doors
	for (int i{ 0 }; i < m_vecpBullets.size(); i++) {

		if (false == m_vecpBullets[i]->IsActive()) break; //if bullet isnt active do nothing

		const short x_1 = m_vecpBullets[i]->GetPosition().x;
		const short y_1 = m_vecpBullets[i]->GetPosition().y;
		const short x_2 = m_vecpBullets[i]->GetPosition().x + m_vecpBullets[i]->GetWidth();
		const short y_2 = m_vecpBullets[i]->GetPosition().y + m_vecpBullets[i]->GetHeight();

		for (auto& y : m_vecpScenes[m_shCurrentScene]->GetEntities()) {

			const short e_x1 = y->GetPosition().x;
			const short e_y1 = y->GetPosition().y;
			const short e_x2 = y->GetPosition().x + y->GetWidth();
			const short e_y2 = y->GetPosition().y + y->GetHeight();

			if (x_1 < e_x2 && x_2 > e_x1 &&
				y_1 < e_y2 && y_2 > e_y1) {

				m_vecpBullets[i]->SetActive(false);
				auto index = m_vecpBullets.begin() + i;
				std::rotate(index, index + 1, m_vecpBullets.end()); //rotate to the end of the vector for caching and breaking

			}

		 }

	}
	//collision checking for bullet against world objects
	for (int i{ 0 }; i < m_vecpBullets.size(); i++) {

		if (false == m_vecpBullets[i]->IsActive() || PLAYER == m_vecpBullets[i]->GetSide()) break; //if bullet isnt active do nothing

		const short x_1 = m_vecpBullets[i]->GetPosition().x;
		const short y_1 = m_vecpBullets[i]->GetPosition().y;
		const short x_2 = m_vecpBullets[i]->GetPosition().x + m_vecpBullets[i]->GetWidth();
		const short y_2 = m_vecpBullets[i]->GetPosition().y + m_vecpBullets[i]->GetHeight();

		if (x_1 < x2 && x_2 > x1 &&
			y_1 < y2 && y_2 > y1) {

			m_vecpBullets[i]->SetActive(false);
			auto index = m_vecpBullets.begin() + i;
			std::rotate(index, index + 1, m_vecpBullets.end()); //rotate to the end of the vector for caching and breaking
			m_pPlayer->Damage(m_vecpBullets[i]->GetDamage());

		}

	}
	//collision checking for bullet against player

	//will need to add enemy colliding with player bullets

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

void World::SpawnBullet(bool dir) { //will need to take in side of the shooter

	if (!HAPI.PlaySound(SOUND->GetSound(SHOOT))) {

		throw std::runtime_error{ "unable to find file enum SHOOT" };

	}

	bool bFoundBullet{ false };

	do  {

		for (int i{ 0 }; i < m_vecpBullets.size(); i++) { //sets bullet to active, 
			
			if (false == m_vecpBullets[i]->IsActive()) {

				bFoundBullet = true;
				m_vecpBullets[i]->SetDirection(dir);
				m_vecpBullets[i]->SetActive(true);
				m_vecpBullets[i]->SetSide(PLAYER); //pass in side of shooter here
				bFoundBullet = !bFoundBullet;
				m_vecpBullets[i]->SetPosition(m_pPlayer->GetPosition().x + (m_pPlayer->GetWidth() >> 1), m_pPlayer->GetPosition().y); 
				//if all bullets are active use the last bullet in the vector due to rotation it has the longest lifetime
				//spawns bullet inside of player not at top left
				return;

			}
			
		}

		bFoundBullet = true;
		size_t i = m_vecpBullets.size() - 1;
		m_vecpBullets[i]->SetActive(true);
		m_vecpBullets[i]->SetSide(PLAYER);
		bFoundBullet = !bFoundBullet;
		m_vecpBullets[i]->SetPosition(m_pPlayer->GetPosition());
		return;

	} while (!bFoundBullet);

}

void World::RestartGame() {

	/*
	
	reset all positions and scores
	reload binary tree 

	*/

}

void World::UpdateScore() { //outside of update entities to prevent flickering

	m_lScore -= m_ulFrameTime;
	HAPI.RenderText(600, 0, HAPI_TColour::CYAN, std::to_string(m_lScore), 24);

}

//
//{
//	auto it = v.begin() + itemIndex;
//	std::rotate(it, it + 1, v.end());
//}
