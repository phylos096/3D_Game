#include"LoadModel.h"

LoadModel::LoadModel() {
	pMaterials = NULL;
	pTextures = NULL;
	numMaterials = NULL;
	pMesh = NULL;
	used = false;
}

LoadModel::~LoadModel() {
	End();
}

HRESULT LoadModel::Load(LPCTSTR modelName, LPCTSTR textureName, IDirect3DDevice9* pDevice3D, D3DXVECTOR3* position) {

	LPD3DXBUFFER pD3DXBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX(modelName, D3DXMESH_SYSTEMMEM,
		pDevice3D, NULL, &pD3DXBuffer, NULL,
		&numMaterials, &pMesh)))
	{
		MessageBox(NULL, _T("Xファイルの読み込みに失敗しました"), modelName, MB_OK);
		return E_FAIL;
	}

	//マテリアルとテクスチャ記録用配列のメモリ確保
	D3DXMATERIAL* D3DXMaterials = (D3DXMATERIAL*)pD3DXBuffer->GetBufferPointer();

	pMaterials = new D3DMATERIAL9[numMaterials];
	pTextures = new LPDIRECT3DTEXTURE9[numMaterials];

	for (DWORD i = 0; i < numMaterials; i++) {
		pMaterials[i] = D3DXMaterials[i].MatD3D;
		pMaterials[i].Ambient = pMaterials[i].Diffuse;
		pTextures[i] = NULL;
		if (D3DXMaterials[i].pTextureFilename != NULL &&
			lstrlenA(D3DXMaterials[i].pTextureFilename) > 0) {
			if (FAILED(D3DXCreateTextureFromFileA(pDevice3D,
				D3DXMaterials[i].pTextureFilename,
				&pTextures[i]))) {
				MessageBox(NULL, _T("テクスチャの読み込みに失敗しました"), NULL, MB_OK);
			}
		}
	}

	pD3DXBuffer->Release();

	return S_OK;
}

void LoadModel::Play(IDirect3DDevice9* pDevice) {
	if (used == false)return;

	for (DWORD i = 0; i < numMaterials; i++) {
		pDevice->SetMaterial(&pMaterials[i]);
		pDevice->SetTexture(0, pTextures[i]);
		pMesh->DrawSubset(i);
	}
}

//修了処理
void LoadModel::End() {
	if (used == TRUE) {
		if (pMaterials != NULL) {
			delete pMaterials;
		}
		if (pTextures != NULL) {
			for (DWORD j = 0; j < numMaterials; j++) {
				pTextures[j]->Release();
			}
			delete pTextures;
		}
		if (pMesh != NULL) {
			pMesh->Release();
		}
	}
}
