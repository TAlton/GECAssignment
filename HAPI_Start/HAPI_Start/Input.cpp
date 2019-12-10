#include "Input.h"

const char Input::GetKBInput() const {

	const static HAPI_TKeyboardData& kbData = HAPI.GetKeyboardData();

	if (kbData.scanCode['D']) return 'D';

	return '\0';
	
}
