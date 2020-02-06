#pragma once

#include"Main.h"

class Direct3D
{
public:
	IDirect3D9* pD3D9;				//Direct3Dデバイス生成オブジェクト
	//LPDIRECT3DDEVICE9 g_pDevice;	//Direct3Dのデバイス
	IDirect3DDevice9* pDevice3D;	//Direct3Dのデバイス
	float GameAspect;

	//コンストラクタ
	Direct3D();
	//デストラクタ
	~Direct3D();
	//デバイス生成
	bool Create(HWND hWnd, int WindowWidth, int WindowHeight);

	void SetView();
};
