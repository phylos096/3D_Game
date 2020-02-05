#define _CRT_SECURE_NO_WARNINGS
#define  _CRT_NON_CONFORMING_SWPRINTFS
#include "DirectXFont.h"

// コンストラクタ
DirectXFont::DirectXFont()
{
	pFont = NULL;
};

// デストラクタ
DirectXFont::~DirectXFont()
{
	if (pFont != NULL)
		pFont->Release();
};


// DirectXフォント作成
bool DirectXFont::Create(IDirect3DDevice9* pDevice3D, int FontHeight)
{
	HFONT	hFont = NULL;	// フォントハンドル
	LOGFONT	LogFont = {};	// フォント構造体

	// デフォルトフォント取得
	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	// デフォルトフォント情報取得
	GetObject(hFont, sizeof(LOGFONT), &LogFont);
	
	// DirectXフォント作成
	/*if (FAILED(D3DXCreateFont(
		pDevice3D,
		FontHeight,					// 文字高さ
		LogFont.lfWidth,			// 文字幅
		LogFont.lfWeight,			// フォントの太さ
		0,							// ミップマップレベル
		LogFont.lfItalic,			// イタリックフラグ
		LogFont.lfCharSet,			// 文字セット
		LogFont.lfOutPrecision,		// 実際のフォントと目的のフォントの特性の一致方法
		LogFont.lfQuality,			// クォリティ
		LogFont.lfPitchAndFamily,	// ピッチとファミリインデックス
		LogFont.lfFaceName,			// フォント名
		&pFont)))
	{
		return false;
	}*/
	if (FAILED(D3DXCreateFont(
		pDevice3D,					//デバイス
		FontHeight,					//文字の高さ
		0,							//文字幅
		FW_NORMAL,					//フォントの太さ
		1,							//MIPMAPのレベル
		FALSE,						//イタリックか
		DEFAULT_CHARSET,			//文字セット
		OUT_DEFAULT_PRECIS,			//出力精度
		DEFAULT_QUALITY,			//出力品質
		DEFAULT_PITCH | FF_SWISS,	//フォントピッチとファミリ
		_T("ＭＳ Ｐゴシック"),		//フォント名
		&pFont))) {					//Direct3Dフォントへのポインタへのアドレス
		return  false;//S_FALSE;
	}

	return true;//S_OK;
};


// 文字列の描画
void DirectXFont::Draw(DWORD Color, int x, int y, const TCHAR* Str, ...)
{
	va_list args;
	va_start(args, Str);					// 可変引数の最初の要素を格納する
	int len = _vsctprintf(Str, args) + 1;	// 文字数カウント、ヌル文字分加える
	if (Buf.size() < (UINT)len)
		Buf.resize(len);						// 文字サイズ分動的にメモリ確保
	_vstprintf(&Buf[0], Str, args);			// 文字を整形する

	SetRect(&Rect, 0, 0, 0, 0);
	// 描画領域サイズ取得
	pFont->DrawText(NULL, &Buf[0], -1, &Rect, DT_LEFT | DT_CALCRECT, Color);
	// 本描画
	Rect.left += x;
	Rect.right += x;
	Rect.top += y;
	Rect.bottom += y;
	pFont->DrawText(NULL, &Buf[0], -1, &Rect, DT_LEFT, Color);
};