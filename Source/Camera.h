#pragma once
#include"Main.h"
#include"BaseObject.h"
#include"LoadModel.h"

class Camera {

	/*//ワールドトランスフォーム（絶対座標変換）
	D3DXMATRIXA16 WorldPosition, Rotation;

	D3DXVECTOR3 vecEyePt;	//カメラ(視点)位置
	D3DXVECTOR3 vecLookatPt;	//注視位置
	D3DXVECTOR3 vecUpVec;	//上方位置
	D3DXMATRIXA16 matView;

	// プロジェクショントランスフォーム（射影変換）
	D3DXMATRIXA16 matProj;

	// ライトをあてる 白色で鏡面反射ありに設定
	D3DXVECTOR3 vecDirection;
	D3DLIGHT9 light;*/
public:
	Camera();
	//bool Create(IDirect3DDevice9* pDevice);
	void Render(LoadModel* model, BaseObject* baseObject, IDirect3DDevice9* pDevice3D);
	void Render(LoadModel* model, IDirect3DDevice9* pDevice3D);
};