#include"Player.h"


static KeyInput* input = NULL;

#pragma region コンストラクタ
///<summary>
///Playerのコンストラクタ	
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

#pragma region デストラクタ
///<summary>
///Playerのデストラクタ	
///</summary>
//Player::~Player() {};
#pragma endregion

#pragma region Move関数
///<summary>
///Playerの移動処理
///</summary>
void Player::Move() {
	input->Update();

	//MessageBox(hWnd, TEXT("来てるよ"), NULL, MB_ICONINFORMATION);
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

#pragma region Update関数
/// <summary>
/// PlayerのUpdate関数
/// </summary>
/// <param name="Update">Update</param>
/// <returns></returns>
void Player::Update() {
	Move();
	baseobject->Update();
}

#pragma endregion

#pragma region Draw関数
void Player::Draw(IDirect3DDevice9* pDevice3D) {

	camera->Render(model, baseobject, pDevice3D);

}
#pragma endregion
