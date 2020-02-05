#pragma once

#include"Main.h"


// �e�L�X�g�`��N���X
class DirectXFont
{
private:
	ID3DXFont* pFont;	// Direct3D�t�H���g
	RECT				Rect;	// �`��̈�
	std::vector<TCHAR>	Buf;	// ������o�b�t�@
public:

	// �R���X�g���N�^
	DirectXFont();
	// �f�X�g���N�^
	virtual ~DirectXFont();
	
	// DirectX�t�H���g�쐬
	//HRESULT Create(LPDIRECT3DDEVICE9 g_pDevice, int FontHeight);
	bool Create(IDirect3DDevice9* pDevice3D, int FontHeight);

	// ������̕`��
	void Draw(DWORD Color, int x, int y, const TCHAR* Str, ...);
};

