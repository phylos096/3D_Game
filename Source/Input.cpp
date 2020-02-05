#include "Input.h"

CInput::CInput()
{
	m_pDInput = NULL;
	m_hWnd = NULL;
	m_useDevice = 0;
}

CInput::~CInput()
{
	Release();
}

//デバイスの作成
bool CInput::Create(HWND hWnd, int useDevice)
{
	if (m_pDInput) {
		Release();
	}
	m_hWnd = hWnd;

	//DirectInputオブジェクトの生成
	HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL);
	if (FAILED(hr)) {
		return FALSE;
	}

	m_useDevice = useDevice;
	if (useDevice & UseInputDevice_KEYBOARD) { m_keyboard.Create(m_pDInput, hWnd); }
	if (useDevice & UseInputDevice_MOUSE) { m_mouse.Create(m_pDInput, hWnd); }

	return TRUE;
}

//デバイスの解放
void CInput::Release()
{
	//各デバイス解放
	m_keyboard.Release();
	m_mouse.Release();

	//DirectInputオブジェクトの解放
	if (m_pDInput != NULL) {
		m_pDInput->Release();
		m_pDInput = NULL;
	}

	m_hWnd = NULL;
	m_useDevice = 0;
}


/*#include "Input.h"
#include "dinput.h"
#include<Windows.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

LPDIRECTINPUT8 g_lpDI;
LPDIRECTINPUTDEVICE8 g_lpDIDevice;

//解放
#define Release(X){if((X)!=nullptr)(X)->Release();(X)=nullptr;}

//コンストラクタ
Input::Input(Window* win):win(win),result(S_OK),input(nullptr),key(nullptr)
{
	memset(&keys, 0, sizeof(keys));
	memset(&olds, 0, sizeof(olds));

	CreateInput();
	CreateKey();
	SetKeyFormat();
	SetKeyCooperative();
}

//デストラクタ
Input::~Input()
{
	Release(key);
	Release(input);
	delete win;
}

//インプットの生成
HRESULT Input::CreateInput(void)
{
	result = DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)(&input), NULL);
	return result;
}

//キーデバイスの生成
HRESULT Input::CreateKey(void)
{
	result = input->CreateDevice(GUID_SysKeyboard, &key, NULL);
	return result;
}

//キーフォーマットのセット
HRESULT Input::SetKeyFormat(void)
{
	result = key->SetDataFormat(&c_dfDIKeyboard);

	return result;
}

//キーの協調レベルのセット
HRESULT Input::SetKeyCooperative(void)
{
	result = key->SetCooperativeLevel(win->GetHandle(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	//入力デバイスへのアクセス権を取得
	key->Acquire();

	return result;
}

//キー入力
bool Input::CheckKey(UINT index)
{
	//チェックフラグ
	bool flag = FALSE;

	//キー情報を取得
	key->GetDeviceState(sizeof(keys), &key);
	if (keys[index] & 0x80) {
		flag = TRUE;
	}
	olds[index] = keys[index];

	return flag;
}

//トリガー入力
bool Input::TriggerKey(UINT index)
{
	bool flag = FALSE;

	//キー情報を取得
	key->GetDeviceState(sizeof(keys), &key);
	if ((keys[index] & 0x80) && !(olds[index] & 0x80)) {
		flag = TRUE;
	}
	olds[index] = keys[index];

	return flag;
}
*/