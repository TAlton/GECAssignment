#include "Input.h"

char Input::GetKBInput() const {

	const static HAPI_TKeyboardData& kbData = HAPI.GetKeyboardData();

	if (kbData.scanCode[HK_SPACE]) return HK_SPACE;
	if (kbData.scanCode['W']) return 'W';
	if (kbData.scanCode['D']) return 'D';
	if (kbData.scanCode['A']) return 'A';
	if (kbData.scanCode['E']) return 'E';

	return '\0';
	
}

int Input::GetMouseInput() const {

	const HAPI_TMouseData& mData = HAPI.GetMouseData();

	if (mData.leftButtonDown) return LMB;
	if (mData.rightButtonDown) return RMB;
	if (mData.middleButtonDown) return MMB;

	return -1;

}

Vec2 Input::GetMousePos() const {

	const HAPI_TMouseData& mData = HAPI.GetMouseData();

	return Vec2(mData.x, mData.y);

}

Vec2 Input::GetControllerAnalogInput(int i) {

	CheckControllersConnected();

	if (true == vecbControllers[i]) {

		return Vec2( GetLeftAnalogX(i), GetLeftAnalogY(i) );

	}

	return Vec2{ 0,0 };
	
}

int Input::GetControllerDigitalInput(int i) {

	CheckControllersConnected();

	const HAPI_TControllerData& ctrlrData = HAPI.GetControllerData(i);

	if (ctrlrData.digitalButtons[HK_DIGITAL_A]) return HK_DIGITAL_A;

	return NULL;

}

void Input::CheckControllersConnected() {

	for (int i{ 0 }; i < HAPI.GetMaxControllers(); i++) {

		if (HAPI.GetControllerData(i).isAttached) vecbControllers[i] = true;

	}

}

int Input::GetLeftAnalogX(int i) { //returns a 1 or -1 as direction right/left 

	const HAPI_TControllerData& ctrlrData = HAPI.GetControllerData(i);

	if (ctrlrData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE) {

		return 1;

	}
	if (ctrlrData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE) {

		return -1;

	}

	return 0;

}

int Input::GetLeftAnalogY(int i) {//returns 1 or -1, Up or Down 

	const HAPI_TControllerData& ctrlrData = HAPI.GetControllerData(i);

	if (ctrlrData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE) {

		return 1;

	}
	if (ctrlrData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE) {

		return -1;

	}

	return 0;

}
