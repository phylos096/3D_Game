#pragma once
#include "Main.h"

#define BOX_FRONT	"9DBF"
#define BOX_RIGHT	"DCFE"
#define BOX_UP		"8C9D"
#define BOX_LEFT	"BA98"
#define BOX_BACK	"AE8C"
#define BOX_DOWN	"EAFB"
#define D3DFVF_VERTEX  (D3DFVF_XYZ | D3DFVF_DIFFUSE)    //トランスフォームされていない頂点の位置座標+ディフューズ カラー成分

class BOX3D
{
private:
	float X[6][4], Y[6][4], Z[6][4];
	DWORD Color[6][4];
	D3DXVECTOR3	Calculation(const char* str,byte i);
	D3DXVECTOR3 tmpPosition;

public:
	BOX3D();
	~BOX3D();
	void CreateBOX(float x, float y, float z, float length);

	void SetUpMatrices(IDirect3DDevice9* pDevice3D,float x, float y, float z);
	
	void Draw(IDirect3DDevice9* pDevice3D);
};