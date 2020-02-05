#include"Main.h"

//�L�[�{�[�h
class CInputKeyboard
{
	friend class CInput;

	IDirectInputDevice8* m_pDIDevKB;			//�f�o�C�X
	bool					m_Keystate[256];	//�X�V���ɉ����Ă���ON(�������ςȂ����E��)
	bool					m_KeyAction[256];	//���������ゾ��ON(�������ςȂ���OFF�ɂȂ�)
												//�z��C���f�b�N�X��DIK_SPACE�Ȃ�

	CInputKeyboard();//private�ɂ��Ă�B�N���X�������CInput���炾���B
	bool Create(IDirectInput8* pDInput, HWND hWnd);
	void Release();
	void Update();

public:
	bool ChkKeyDown(int key) { return m_Keystate[key]; }
	bool ChkKeyAction(int key) { return m_KeyAction[key]; }
};

//�}�E�X
class CInputMouse
{
	friend class CInput;

	IDirectInputDevice8* m_pDIMouse;		//�f�o�C�X
	bool CreateMouse();
	void UpdateInput_Mouse();
	void ReleaseMouse();

	HWND					m_hWnd;
	int						m_wndWid;
	int						m_wndHgt;
	bool					m_windowMode;

	long					m_posX;	//�}�E�X���W
	long					m_posY;

	bool					m_LDown;	//Update���_�̃{�^�����
	bool					m_RDown;
	bool					m_MDown;

	bool					m_LAction;	//�{�^�����������ゾ��ON�ɂȂ�(�N���b�N���E���Ƃ���)
	bool					m_RAction;
	bool					m_MAction;


	CInputMouse();
	bool Create(IDirectInput8* pDInput, HWND hWnd);
	void Release();
	void Update();

public:

	long PosX() { return m_posX; }
	long PosY() { return m_posY; }

	bool IsLAction() { return m_LAction; }
	bool IsRAction() { return m_RAction; }
	bool IsMAction() { return m_MAction; }

	//�E�B���h�E���[�h�̎w��
	//�J�[�\���ʒu��API�����邩�ADirectInput�����邩�̈Ⴂ
	void SetWindowMode(bool isWindowmode) { m_windowMode = isWindowmode; }//TRUE:�E�B���h�E���[�h FALSE:�t���X�N���[��

	void SetCursorPos(int x, int y)
	{
		m_posX = x;
		m_posY = y;
	}

};

//�L�[�{�[�h�A�}�E�X�A�Q�[���p�b�h���͂��Ǘ�����N���X
class CInput
{
	HWND					m_hWnd;

	//DirectInput�I�u�W�F�N�g
	IDirectInput8* m_pDInput;

	//CInput�Ŏg���f�o�C�X�i�������Ώۂɂ���j
	int						m_useDevice;
#define UseInputDevice_KEYBOARD	0x01
#define UseInputDevice_MOUSE	0x02
#define UseInputDevice_ALL		(UseInputDevice_KEYBOARD | UseInputDevice_MOUSE)

	//�e�f�o�C�X
	CInputKeyboard		m_keyboard;
	CInputMouse			m_mouse;

public:

	CInput();
	~CInput();

	bool Create(HWND hWnd, int useDevice = UseInputDevice_ALL);
	void Release();

public:
	//���͏�Ԃ��X�V����
	/*void InputUpdate() {
		m_keyboard.Update();
		m_mouse.Update();
	}*/

	//�e�f�o�C�X���Q�Ƃ���(����������͏�Ԃ��擾����)
	CInputKeyboard* Keyboard() { return &m_keyboard; }
	CInputMouse* Mouse() { return &m_mouse; }
};


/*#define INITGUID
#include<dinput.h>


#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define KEY_MAX 256

class Window;

class Input {
private:
	//Input����
	HRESULT CreateInput(void);
	//�L�[�f�o�C�X�̐���
	HRESULT CreateKey(void);
	//�L�[�t�H�[�}�b�g�̃Z�b�g
	HRESULT SetKeyFormat(void);
	//�L�[�̋������x���̃Z�b�g
	HRESULT SetKeyCooperative(void);

	//�E�B���h�E
	Window* win;

	//�Q�ƌ���
	HRESULT result;

	//�C���v�b�g
	LPDIRECTINPUT8 input;

	//�C���v�b�g�f�o�C�X
	LPDIRECTINPUTDEVICE8 key;

	//�L�[���
	BYTE keys[KEY_MAX];

	//�O�̃L�[���
	BYTE olds[KEY_MAX];

public:
	//�R���X�g���N�^
	Input(Window* win);
	//�f�X�g���N�^
	~Input();
	//�L�[����
	bool CheckKey(UINT index);
	//�g���K�[�̓���
	bool TriggerKey(UINT index);
};*/