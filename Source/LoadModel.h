#pragma once
#include"Main.h"

class LoadModel {
public:
	LPD3DXMESH			pMesh;			//���b�V��
	D3DMATERIAL9*		pMaterials;		//�}�e���A���̔z��
	LPDIRECT3DTEXTURE9* pTextures;		//�e�N�X�`���̔z��
	DWORD				numMaterials;	//�}�e���A���̐�
	BOOL				used;			//�f�[�^�������Ă��邩�̃t���O
	LoadModel();
	~LoadModel();
	void Init();
	void Play(IDirect3DDevice9* pDevice);
	void End();
	void Result();
	HRESULT Load(LPCTSTR modelName, IDirect3DDevice9* pDevice3D, D3DXVECTOR3* position);
	HRESULT Load(LPCTSTR modelName, LPCTSTR textureName, IDirect3DDevice9* pDevice3D, D3DXVECTOR3* position);
};