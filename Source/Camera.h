#pragma once
#include"Main.h"
#include"BaseObject.h"
#include"LoadModel.h"

class Camera {

	/*//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	D3DXMATRIXA16 WorldPosition, Rotation;

	D3DXVECTOR3 vecEyePt;	//�J����(���_)�ʒu
	D3DXVECTOR3 vecLookatPt;	//�����ʒu
	D3DXVECTOR3 vecUpVec;	//����ʒu
	D3DXMATRIXA16 matView;

	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	D3DXMATRIXA16 matProj;

	// ���C�g�����Ă� ���F�ŋ��ʔ��˂���ɐݒ�
	D3DXVECTOR3 vecDirection;
	D3DLIGHT9 light;*/
public:
	Camera();
	//bool Create(IDirect3DDevice9* pDevice);
	void Render(LoadModel* model, BaseObject* baseObject, IDirect3DDevice9* pDevice3D);
	void Render(LoadModel* model, IDirect3DDevice9* pDevice3D);
};