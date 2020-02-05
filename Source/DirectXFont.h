#pragma once

#include"Main.h"


// テキスト描画クラス
class DirectXFont
{
private:
	ID3DXFont* pFont;	// Direct3Dフォント
	RECT				Rect;	// 描画領域
	std::vector<TCHAR>	Buf;	// 文字列バッファ
public:

	// コンストラクタ
	DirectXFont();
	// デストラクタ
	virtual ~DirectXFont();
	
	// DirectXフォント作成
	//HRESULT Create(LPDIRECT3DDEVICE9 g_pDevice, int FontHeight);
	bool Create(IDirect3DDevice9* pDevice3D, int FontHeight);

	// 文字列の描画
	void Draw(DWORD Color, int x, int y, const TCHAR* Str, ...);
};

