#include "WorldEntity.h"



WorldEntity::WorldEntity(const std::string alias, Vec2 pos, int side, short health) {

	try {

		this->m_strAlias = alias;
		this->m_v2Pos = pos;
		this->m_nSide = side;
		this->m_shHealth = health;

	}
	catch (std::overflow_error& e) {
		throw e;
	}
	catch (std::underflow_error& e) {
		throw e;
	}
	catch (std::invalid_argument& e) {
		throw e;
	}
	catch (...) {

	}

}

WorldEntity::~WorldEntity()
{
}

void WorldEntity::Update()
{
}
