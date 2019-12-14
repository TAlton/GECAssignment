#pragma once

#include <HAPI_lib.h>

enum eMouseData : int { LMB = 0, RMB, MMB, SIDEB1, SIDEB2 };

using namespace HAPISPACE;

class Input
{

public:

	const char GetKBInput() const;
	const int GetMouseInput() const;

private:

};

