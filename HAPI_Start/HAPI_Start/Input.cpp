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

Vec2 Input::GetControllerAnalogInput(int i) {

	CheckControllersConnected();

	if (true == vecbControllers[i]) {

		Vec2 v{ 0,0 };
		v.x = GetLeftAnalogX(i);
		v.y = GetLeftAnalogY(i);

		return v;

	}

	return Vec2{ 0,0 };
	
}

int Input::GetControllerDigitalInput(int i) {

	CheckControllersConnected();

	const HAPI_TControllerData& ctrlrData = HAPI.GetControllerData(i);

	if (ctrlrData.digitalButtons[HK_DIGITAL_A]) return HK_DIGITAL_A;

}

void Input::CheckControllersConnected() {

	for (int i{ 0 }; i < HAPI.GetMaxControllers(); i++) {

		if (HAPI.GetControllerData(i).isAttached) vecbControllers[i] = true;

	}

}

int Input::GetLeftAnalogX(int i) {

	const HAPI_TControllerData& ctrlrData = HAPI.GetControllerData(i);
	int x{ 0 };

	if (ctrlrData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE) {

		x = 1;
		return x;

	}
	if (ctrlrData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE) {

		x = -1;
		return x;

	}

	return 0;

}

int Input::GetLeftAnalogY(int i) {

	const HAPI_TControllerData& ctrlrData = HAPI.GetControllerData(i);

	int y{ 0 };

	if (ctrlrData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE) {

		y = 1;
		return y;

	}
	if (ctrlrData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE) {

		y = -1;
		return y;

	}

	return 0;


}
