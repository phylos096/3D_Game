#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include"Main.h"

///<summary>KeyInputクラス
///<para>キーボードの入力ができる</para>
///</summary>
class KeyInput {

private:

	void Release();

	HRESULT hr;

	//キーの情報
	bool KeyState[256];
public:
	KeyInput();
	~KeyInput() { Release(); };

	//DirectInputオブジェクトポインタ
	LPDIRECTINPUT8 pDInput;
	
	//DirectInputデバイス、オブジェクトポインタ
	LPDIRECTINPUTDEVICE8 pKeyDevice;


	bool Create(HINSTANCE hInstance,HWND hWnd);

	void Update();

	///<summary>
	///これを通して、キーの状態を受け取る
	///<para>使い方:if(CheckKey(キーコード)){ 処理; }</para>
	///</summary>
	bool CheckKey(int key) { return KeyState[key]; };

};