#pragma once

#include "Vec2.h"

#include <HAPI_lib.h>

enum eMouseData : int { LMB = 0, RMB, MMB, SIDEB1, SIDEB2 };

using namespace HAPISPACE;

class Input
{

public:

	Input() { vecbControllers.resize(HAPI.GetMaxControllers(), false); }

	char GetKBInput() const;
	int GetMouseInput() const;
	Vec2 GetMousePos() const;
	Vec2 GetControllerAnalogInput(int i);
	int GetControllerDigitalInput(int i);

private:

	std::vector<bool> vecbControllers;

	void CheckControllersConnected();
	int GetLeftAnalogX(int i);
	int GetLeftAnalogY(int i);

};

