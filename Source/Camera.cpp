#include"Camera.h"

Camera::Camera() {

}

void Camera::Render(LoadModel* model, BaseObject* baseObject, IDirect3DDevice9* pDevice3D) {
	//pDevice3D->SetTransform(D3DTS_WORLD, &baseObject->Value_WorldPosition());
	//�����̐ݒ�
	pDevice3D->SetRenderState(D3DRS_AMBIENT, 0xff000000);


	//���[���h�g�����X�t�H�[���i���[�J�����W�����[���h���W�ւ̕ϊ��j	
	pDevice3D->SetTransform(D3DTS_WORLD, &baseObject->Value_WorldPosition());
	// �r���[�g�����X�t�H�[���i���[���h���W���J�������W�ւ̕ϊ��j
	D3DXMATRIX matView;
	D3DXVECTOR3 vecEyePt(5.0f, 6.0f, -8.0f);//D3DXVECTOR3 vecEyePt = baseObject->Value_Position(); //�J�����i���_�j�ʒu
	//vecEyePt.z -= 2;; //�J�����i���_�j�ʒu
	D3DXVECTOR3 vecLookatPt(0.0f, 0.0f, 1.0f);//�����ʒu
	D3DXVECTOR3 vecUpVec(0.0f, 1.0f, 0.0f);//����ʒu     
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	pDevice3D->SetTransform(D3DTS_VIEW, &matView);
	// �v���W�F�N�V�����g�����X�t�H�[���i�J�������W���X�N���[�����W�ւ̕ϊ��j
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4,
		(FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 1.0f, 1000.0f);
	pDevice3D->SetTransform(D3DTS_PROJECTION, &matProj);
	// ���C�g�����Ă� ���F�Ō��򔽎˂���ɐݒ�
	D3DXVECTOR3 vecDirection(1, 1, 1);
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
	light.Range = 200.0f;
	pDevice3D->SetLight(0, &light);
	pDevice3D->LightEnable(0, TRUE);
	// �����_�����O	 
	for (DWORD i = 0; i < model->numMaterials; i++)
	{
		pDevice3D->SetMaterial(&model->pMaterials[i]);
		pDevice3D->SetTexture(0, model->pTextures[i]);
		model->pMesh->DrawSubset(i);
	}

}
void Camera::Render(LoadModel* model, IDirect3DDevice9* pDevice3D) {
	//pDevice3D->SetTransform(D3DTS_WORLD, &baseObject->Value_WorldPosition());
	//�����̐ݒ�
	pDevice3D->SetRenderState(D3DRS_AMBIENT, 0xff000000);

	//���[���h�g�����X�t�H�[���i���[�J�����W�����[���h���W�ւ̕ϊ��j	
	pDevice3D->SetTransform(D3DTS_WORLD, (0, 0, 0));
	// �r���[�g�����X�t�H�[���i���[���h���W���J�������W�ւ̕ϊ��j
	D3DXMATRIX matView;
	D3DXVECTOR3 vecEyePt(5.0f, 6.0f, -8.0f); //�J�����i���_�j�ʒu
	D3DXVECTOR3 vecLookatPt(0.0f, 0.0f, 1.0f);//�����ʒu
	D3DXVECTOR3 vecUpVec(0.0f, 1.0f, 0.0f);//����ʒu     
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	pDevice3D->SetTransform(D3DTS_VIEW, &matView);
	// �v���W�F�N�V�����g�����X�t�H�[���i�J�������W���X�N���[�����W�ւ̕ϊ��j
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4,
		(FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 1.0f, 1000.0f);
	pDevice3D->SetTransform(D3DTS_PROJECTION, &matProj);
	// ���C�g�����Ă� ���F�Ō��򔽎˂���ɐݒ�
	D3DXVECTOR3 vecDirection(1, 1, 1);
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
	light.Range = 200.0f;
	pDevice3D->SetLight(0, &light);
	pDevice3D->LightEnable(0, TRUE);
	// �����_�����O	 
	for (DWORD i = 0; i < model->numMaterials; i++)
	{
		pDevice3D->SetMaterial(&model->pMaterials[i]);
		pDevice3D->SetTexture(0, model->pTextures[i]);
		model->pMesh->DrawSubset(i);
	}

}
