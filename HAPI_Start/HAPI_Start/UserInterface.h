#pragma once
#include "Entity.h"
class UserInterface :
	public Entity
{
public:

	UserInterface(short h, Vec2 P, const char* id, int side) : Entity(h, P, id, side) {}
	UserInterface(int h = 0, int x = 0, int y = 0, std::string id = "default", int side = 3) : Entity(h, x, y, id, side) { SetPosition(x, y); }
	UserInterface(const Entity& e) : Entity(e) {}
	~UserInterface();

	void Update(float dt) override;

private:

};

