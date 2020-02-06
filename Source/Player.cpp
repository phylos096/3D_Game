#include"Player.h"


static KeyInput* input = NULL;

#pragma region �R���X�g���N�^
///<summary>
///Player�̃R���X�g���N�^	
///</summary>
Player::Player(HINSTANCE hInstance, HWND hWnd, IDirect3DDevice9* pDevice3D) {


	input = new KeyInput();
	input->Create(hInstance, hWnd);

	model = new LoadModel();
	model->Load(_T("../Model/Human.x"), pDevice3D, &Value_Position());

	baseobject = new BaseObject();

	camera = new Camera();
};
#pragma endregion

#pragma region �f�X�g���N�^
///<summary>
///Player�̃f�X�g���N�^	
///</summary>
//Player::~Player() {};
#pragma endregion

#pragma region Move�֐�
///<summary>
///Player�̈ړ�����
///</summary>
void Player::Move() {
	input->Update();

	//MessageBox(hWnd, TEXT("���Ă��"), NULL, MB_ICONINFORMATION);
	if (input->CheckKey(DIK_A)) {
		baseobject->Value_PosX(-PLAYER_MOVE_SPEED);
		//MessageBox(NULL, TEXT("Key Down"), NULL, MB_ICONINFORMATION);
	}
	if (input->CheckKey(DIK_D)) {
		baseobject->Value_PosX(PLAYER_MOVE_SPEED);
	}
	if (input->CheckKey(DIK_W)) {
		baseobject->Value_PosZ(PLAYER_MOVE_SPEED);
	}
	if (input->CheckKey(DIK_S)) {
		baseobject->Value_PosZ(-PLAYER_MOVE_SPEED);
	}
	if (input->CheckKey(DIK_SPACE)) {
		baseobject->Value_PosY(PLAYER_MOVE_SPEED);
	}
	if (input->CheckKey(DIK_LSHIFT)) {
		baseobject->Value_PosY(-PLAYER_MOVE_SPEED);
	}
	if (input->CheckKey(DIK_Z)) {
		baseobject->Value_Angle(-0.025f);
	}
	if (input->CheckKey(DIK_C)) {
		baseobject->Value_Angle(0.025f);
	}
};
#pragma endregion

#pragma region Update�֐�
/// <summary>
/// Player��Update�֐�
/// </summary>
/// <param name="Update">Update</param>
/// <returns></returns>
void Player::Update() {
	Move();
	baseobject->Update();
}

#pragma endregion

#pragma region Draw�֐�
void Player::Draw(IDirect3DDevice9* pDevice3D) {

	camera->Render(model, baseobject, pDevice3D);

}
#pragma endregion
