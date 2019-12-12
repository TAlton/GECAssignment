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

	float GetGravity() const { return this->m_fGravity; } //maybe need this to be whole
	float Lerp(float a, float b, float t) { return (a + t * (b - a)); }

private:

	const float m_fGravity{ 0.981f };

	Physics() = default;

	static std::shared_ptr<Physics> s_pPhysics;

};

#define PHYSICS Physics::GetInstance()