#pragma once
#include"Main.h"

class LoadModel {
public:
	LPD3DXMESH			pMesh;			//メッシュ
	D3DMATERIAL9*		pMaterials;		//マテリアルの配列
	LPDIRECT3DTEXTURE9* pTextures;		//テクスチャの配列
	DWORD				numMaterials;	//マテリアルの数
	BOOL				used;			//データが入っているかのフラグ
	LoadModel();
	~LoadModel();
	void Init();
	void Play(IDirect3DDevice9* pDevice);
	void End();
	void Result();
	HRESULT Load(LPCTSTR modelName, IDirect3DDevice9* pDevice3D, D3DXVECTOR3* position);
	HRESULT Load(LPCTSTR modelName, LPCTSTR textureName, IDirect3DDevice9* pDevice3D, D3DXVECTOR3* position);
};