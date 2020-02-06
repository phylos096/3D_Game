#include "KeyInput.h"

#pragma region コンストラクタ
///<summary>KeyInputのコンストラクタ</summary>
KeyInput::KeyInput() {

	pDInput = NULL;
	pKeyDevice = NULL;

	ZeroMemory(KeyState, sizeof(KeyState));
}
#pragma endregion


#pragma region Create関数
bool KeyInput::Create(HINSTANCE hInstance, HWND hWnd) {

	//DirectInput8オブジェクト作成
	hr = DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(LPVOID*)&pDInput,
		NULL);

	if (FAILED(hr))return false;


	//デバイスの作成
	pDInput->CreateDevice(GUID_SysKeyboard,
		&pKeyDevice,
		NULL);

	if (FAILED(hr))return false;

	//デバイスの設定
	hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(hr))return false;

	pKeyDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	if (FAILED(hr))return false;

	//バッファサイズの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = 100;
	hr = pKeyDevice->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);

	if (FAILED(hr))return false;

	return true;
}
#pragma endregion

#pragma region Update関数
///<summary>KeyInputのUpdate</summary>
void KeyInput::Update() {

	DIDEVICEOBJECTDATA od;
	DWORD dwInOut = 1;

	pKeyDevice->Acquire();

	hr = pKeyDevice->GetDeviceData(sizeof(od), &od, &dwInOut, 0);

	if (FAILED(hr) || dwInOut == 0)return;
	else {
		if (od.dwData & 0x80)KeyState[od.dwOfs] = TRUE;
		else KeyState[od.dwOfs] = FALSE;
	}

}
#pragma endregion

#pragma region Release関数
///<summary>KeyInputのRelease</summary>
void KeyInput::Release() {
	if (pKeyDevice) {
		pKeyDevice->Unacquire();
	}

	pKeyDevice->Release();
	pKeyDevice = NULL;

	pDInput->Release();
	pDInput = NULL;

	ZeroMemory(KeyState, sizeof(KeyState));
}
#pragma endregion