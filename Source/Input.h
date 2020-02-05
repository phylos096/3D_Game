#include"Main.h"

//キーボード
class CInputKeyboard
{
	friend class CInput;

	IDirectInputDevice8* m_pDIDevKB;			//デバイス
	bool					m_Keystate[256];	//更新時に押してたらON(押しっぱなしを拾う)
	bool					m_KeyAction[256];	//押した直後だけON(押しっぱなしはOFFになる)
												//配列インデックスはDIK_SPACEなど

	CInputKeyboard();//privateにしてる。クラスを作れるはCInputからだけ。
	bool Create(IDirectInput8* pDInput, HWND hWnd);
	void Release();
	void Update();

public:
	bool ChkKeyDown(int key) { return m_Keystate[key]; }
	bool ChkKeyAction(int key) { return m_KeyAction[key]; }
};

//マウス
class CInputMouse
{
	friend class CInput;

	IDirectInputDevice8* m_pDIMouse;		//デバイス
	bool CreateMouse();
	void UpdateInput_Mouse();
	void ReleaseMouse();

	HWND					m_hWnd;
	int						m_wndWid;
	int						m_wndHgt;
	bool					m_windowMode;

	long					m_posX;	//マウス座標
	long					m_posY;

	bool					m_LDown;	//Update時点のボタン状態
	bool					m_RDown;
	bool					m_MDown;

	bool					m_LAction;	//ボタン押した直後だけONになる(クリックを拾うときに)
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

	//ウィンドウモードの指定
	//カーソル位置をAPIから取るか、DirectInputから取るかの違い
	void SetWindowMode(bool isWindowmode) { m_windowMode = isWindowmode; }//TRUE:ウィンドウモード FALSE:フルスクリーン

	void SetCursorPos(int x, int y)
	{
		m_posX = x;
		m_posY = y;
	}

};

//キーボード、マウス、ゲームパッド入力を管理するクラス
class CInput
{
	HWND					m_hWnd;

	//DirectInputオブジェクト
	IDirectInput8* m_pDInput;

	//CInputで使うデバイス（初期化対象にする）
	int						m_useDevice;
#define UseInputDevice_KEYBOARD	0x01
#define UseInputDevice_MOUSE	0x02
#define UseInputDevice_ALL		(UseInputDevice_KEYBOARD | UseInputDevice_MOUSE)

	//各デバイス
	CInputKeyboard		m_keyboard;
	CInputMouse			m_mouse;

public:

	CInput();
	~CInput();

	bool Create(HWND hWnd, int useDevice = UseInputDevice_ALL);
	void Release();

public:
	//入力状態を更新する
	/*void InputUpdate() {
		m_keyboard.Update();
		m_mouse.Update();
	}*/

	//各デバイスを参照する(ここから入力状態を取得する)
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
	//Input生成
	HRESULT CreateInput(void);
	//キーデバイスの生成
	HRESULT CreateKey(void);
	//キーフォーマットのセット
	HRESULT SetKeyFormat(void);
	//キーの協調レベルのセット
	HRESULT SetKeyCooperative(void);

	//ウィンドウ
	Window* win;

	//参照結果
	HRESULT result;

	//インプット
	LPDIRECTINPUT8 input;

	//インプットデバイス
	LPDIRECTINPUTDEVICE8 key;

	//キー情報
	BYTE keys[KEY_MAX];

	//前のキー情報
	BYTE olds[KEY_MAX];

public:
	//コンストラクタ
	Input(Window* win);
	//デストラクタ
	~Input();
	//キー入力
	bool CheckKey(UINT index);
	//トリガーの入力
	bool TriggerKey(UINT index);
};*/