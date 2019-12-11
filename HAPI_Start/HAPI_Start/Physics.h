#pragma once

#include <memory>

class Physics {

public:

	static std::shared_ptr<Physics>& GetInstance() {

		if (!s_pPhysics) {

			s_pPhysics.reset(new Physics());

		}

		return s_pPhysics;

	}

	float GetGravity() const { return this->m_fGravity; }

private:

	const float m_fGravity{ 0.981f };

	Physics();

	static std::shared_ptr<Physics> s_pPhysics;

};

#define PHYSICS Physics::GetInstance()