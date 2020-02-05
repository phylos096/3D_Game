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

//�f�o�C�X�̍쐬
bool CInput::Create(HWND hWnd, int useDevice)
{
	if (m_pDInput) {
		Release();
	}
	m_hWnd = hWnd;

	//DirectInput�I�u�W�F�N�g�̐���
	HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL);
	if (FAILED(hr)) {
		return FALSE;
	}

	m_useDevice = useDevice;
	if (useDevice & UseInputDevice_KEYBOARD) { m_keyboard.Create(m_pDInput, hWnd); }
	if (useDevice & UseInputDevice_MOUSE) { m_mouse.Create(m_pDInput, hWnd); }

	return TRUE;
}

//�f�o�C�X�̉��
void CInput::Release()
{
	//�e�f�o�C�X���
	m_keyboard.Release();
	m_mouse.Release();

	//DirectInput�I�u�W�F�N�g�̉��
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

//���
#define Release(X){if((X)!=nullptr)(X)->Release();(X)=nullptr;}

//�R���X�g���N�^
Input::Input(Window* win):win(win),result(S_OK),input(nullptr),key(nullptr)
{
	memset(&keys, 0, sizeof(keys));
	memset(&olds, 0, sizeof(olds));

	CreateInput();
	CreateKey();
	SetKeyFormat();
	SetKeyCooperative();
}

//�f�X�g���N�^
Input::~Input()
{
	Release(key);
	Release(input);
	delete win;
}

//�C���v�b�g�̐���
HRESULT Input::CreateInput(void)
{
	result = DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)(&input), NULL);
	return result;
}

//�L�[�f�o�C�X�̐���
HRESULT Input::CreateKey(void)
{
	result = input->CreateDevice(GUID_SysKeyboard, &key, NULL);
	return result;
}

//�L�[�t�H�[�}�b�g�̃Z�b�g
HRESULT Input::SetKeyFormat(void)
{
	result = key->SetDataFormat(&c_dfDIKeyboard);

	return result;
}

//�L�[�̋������x���̃Z�b�g
HRESULT Input::SetKeyCooperative(void)
{
	result = key->SetCooperativeLevel(win->GetHandle(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	//���̓f�o�C�X�ւ̃A�N�Z�X�����擾
	key->Acquire();

	return result;
}

//�L�[����
bool Input::CheckKey(UINT index)
{
	//�`�F�b�N�t���O
	bool flag = FALSE;

	//�L�[�����擾
	key->GetDeviceState(sizeof(keys), &key);
	if (keys[index] & 0x80) {
		flag = TRUE;
	}
	olds[index] = keys[index];

	return flag;
}

//�g���K�[����
bool Input::TriggerKey(UINT index)
{
	bool flag = FALSE;

	//�L�[�����擾
	key->GetDeviceState(sizeof(keys), &key);
	if ((keys[index] & 0x80) && !(olds[index] & 0x80)) {
		flag = TRUE;
	}
	olds[index] = keys[index];

	return flag;
}
*/