#pragma once

#include"Main.h"

class Direct3D
{
public:
	IDirect3D9* pD3D9;				//Direct3D�f�o�C�X�����I�u�W�F�N�g
	//LPDIRECT3DDEVICE9 g_pDevice;	//Direct3D�̃f�o�C�X
	IDirect3DDevice9* pDevice3D;	//Direct3D�̃f�o�C�X
	float GameAspect;

	//�R���X�g���N�^
	Direct3D();
	//�f�X�g���N�^
	~Direct3D();
	//�f�o�C�X����
	bool Create(HWND hWnd, int WindowWidth, int WindowHeight);

	void SetView();
};
