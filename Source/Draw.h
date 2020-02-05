#pragma once
#define FVF_CUSTOM (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#include"Main.h"

struct CUSTOMVERTEX {
	float x, y, z;		//頂点座標
	float rhw;			//除算数
	DWORD dwcexolor;		//焦点の色
	float u, v;			//テクスチャ座標
};

class Draw {
private:
	Draw();
	~Draw();
public:
	
	void main(void);
	HRESULT CreateVertexBuffer(UINT,DWORD,DWORD,D3DPOOL,IDirect3DVertexBuffer9**,HANDLE*);
	HRESULT Lock(UINT,UINT,void**,DWORD);

	void IsDraw();
};