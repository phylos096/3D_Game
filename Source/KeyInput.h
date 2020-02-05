#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include"Main.h"

///<summary>KeyInput�N���X
///<para>�L�[�{�[�h�̓��͂��ł���</para>
///</summary>
class KeyInput {

private:

	void Release();

	HRESULT hr;

	//�L�[�̏��
	bool KeyState[256];
public:
	KeyInput();
	~KeyInput() { Release(); };

	//DirectInput�I�u�W�F�N�g�|�C���^
	LPDIRECTINPUT8 pDInput;
	
	//DirectInput�f�o�C�X�A�I�u�W�F�N�g�|�C���^
	LPDIRECTINPUTDEVICE8 pKeyDevice;


	bool Create(HINSTANCE hInstance,HWND hWnd);

	void Update();

	///<summary>
	///�����ʂ��āA�L�[�̏�Ԃ��󂯎��
	///<para>�g����:if(CheckKey(�L�[�R�[�h)){ ����; }</para>
	///</summary>
	bool CheckKey(int key) { return KeyState[key]; };

};