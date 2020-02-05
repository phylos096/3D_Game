#pragma once
#pragma comment(lib, "d3dx9.lib")
#include"d3dx9math.h"

class BaseObject {
private:
#pragma region 変数定義

	//現在の座標
	double pos_X;
	double pos_Y;
	double pos_Z;
	D3DXVECTOR3 position;
	D3DXMATRIX worldPosition;

	//次の座標(nextX,nextY,nextZの略)
	double pos_nX;
	double pos_nY;
	double pos_nZ;
	D3DXVECTOR3 positionN;

	//角度
	double rad;     //ラジアン
	double angle;   //角度
	double sin;     //Sine
	double cos;     //cosine
	double tan;     //tangent

	D3DXVECTOR3 vec_X;
	D3DXVECTOR3 vec_Y;
	D3DXVECTOR3 vec_Z;
	D3DXMATRIX rotation;

	//サイズ
	double scal_X;
	double scal_Y;
	double scal_Z;
	D3DXMATRIX scaling;

	//パラメーター
	double hp;          //体力
	double mp;          //魔力
	double st;          //スタミナ
	double attack;      //攻撃
	double defense;     //防御
	double speed;       //速度

	//情報
	char* name;
	char* tag;

#pragma endregion

public:
#pragma region コンストラクタ
	/// <summary>
	/// <para>@brief コンストラクタ</para>
	/// <para>@note 初期化関数</para>
	/// </summary>
	/// <remarks>
	/// 特に呼ぶ必要はないです
	/// </remarks>
	BaseObject() {
		ZeroMemory(this, sizeof(BaseObject));
		D3DXMatrixIdentity(&worldPosition);

		vec_X = D3DXVECTOR3(1.0f, 0, 0);
		vec_Y = D3DXVECTOR3(0, 1.0f, 0);
		vec_Z = D3DXVECTOR3(0, 0, 01.0f);
		D3DXMatrixIdentity(&rotation);

		scal_X = 1.0f;
		scal_Y = 1.0f;
		scal_Z = 1.0f;
		D3DXMatrixIdentity(&scaling);
	};
#pragma endregion

#pragma region Acceser関数

	///<summary>
	///オブジェクトのX座標設定取得関数
	///</summary>
	///<pragma name="Value_PosX">Value_PosX</pragma>
	///<returns>引数:double型</returns>
	double Value_PosX()
	{
		return position.x;
		//return pos_X;
	};
	void Value_PosX(double n)
	{
		//position.x += n;
		position += vec_X * n;
		//pos_X += n;
	};

	/// <summary>
	/// オブジェクトのY座標設定取得関数
	/// </summary>
	///<pragma name="Value_PosY">Value_PosY</pragma>
	///<returns>引数:double型</returns>
	double Value_PosY()
	{
		return position.y;
		//return pos_Y;
	}
	void Value_PosY(double n) {
		//position.y += n;
		position += vec_Y * n;
		//pos_Y += n;
	}

	/// <summary>
	/// オブジェクトのZ座標設定取得関数
	/// </summary>
	///<pragma name="Value_PosZ">Value_PosZ</pragma>
	///<returns>引数:double型</returns>
	double Value_PosZ()
	{
		return position.z;
		//return pos_Z;
	}
	void Value_PosZ(double n) {
		//position.z += n;
		position += vec_Z * n;
		//pos_Z += n;
	}

	///<summary>
	///オブジェクトの3次元座標取得関数
	///</summary>
	///<pragma name="Value_Position">Value_Positopn</pragma>
	///<returns>引数:D3DXVECTOR3型</returns>
	D3DXVECTOR3 Value_Position()
	{
		return position;
	}
	void Value_Position(D3DXVECTOR3 n)
	{
		position += n;
	}

	///<summary>
	///オブジェクトのワールド座標取得関数
	///</summary>
	///<pragma name="Value_WorldPosition">Value_WorldPositopn</pragma>
	///<returns>引数:D3DXMATRIX型</returns>
	D3DXMATRIX Value_WorldPosition() {
		return worldPosition;
	}
	void Value_WorldPosition(D3DXMATRIX n) {
		worldPosition += n;
	}


	/// <summary>
	/// オブジェクトの次のX座標設定取得関数
	/// </summary>
	///<pragma name="Value_NextPosX">Value_NextPosX</pragma>
	///<returns>引数:double型</returns>
	double Value_NextPosX()
	{
		return pos_nX;
	}
	void Value_NextPosX(double n) {
		pos_nX += n;
	}

	/// <summary>
	/// オブジェクトの次のY座標設定取得関数
	/// </summary>
	///<pragma name="Value_NextPosY">Value_NextPosY</pragma>
	///<returns>引数:double型</returns>
	double Value_NextPosY() {
		return pos_nY;
	}
	void Value_NextPosY(double n) {
		pos_nY += n;
	}

	/// <summary>
	/// オブジェクトの次のZ座標設定取得関数
	/// </summary>
	///<pragma name="Value_NextPosZ">Value_NextPosZ</pragma>
	///<returns>引数:double型</returns>
	double Value_NextPosZ() {
		return pos_nZ;
	}
	void Value_NextPosZ(double n) {
		pos_nZ += n;
	}

	///<summary>
	///オブジェクトの移動先の3次元座標取得関数
	///</summary>
	///<pragma name="Value_NextPosition">Value_NextPositopn</pragma>
	///<returns>引数:D3DXVECTOR3型</returns>
	D3DXVECTOR3 Value_NextPosition()
	{
		positionN = D3DXVECTOR3(pos_nX, pos_nY, pos_nZ);
		return positionN;
	}
	void Value_NextPosition(D3DXVECTOR3 n)
	{
		positionN += n;
	}


	/// <summary>
	/// ラジアン値の設定取得関数
	/// </summary>
	///<pragma name="Value_Rad">Value_Rad</pragma>
	///<returns>引数:double型</returns>
	double Value_Rad() {
		return rad;
	}
	double Value_Rad(double n) {
		rad = n;
	}

	/// <summary>
	/// 角度の座標設定取得関数
	/// </summary>
	///<pragma name="Value_Angle">Value_Angle</pragma>
	///<returns>引数:double型</returns>
	double Value_Angle() {
		return angle;
	}
	void Value_Angle(double n) {
		angle += n;
	}
	///<summary>
	///オブジェクトのX軸ベクトル取得関数
	///</summary>
	///<pragma name="Value_Vector_X">Value_Vector_X</pragma>
	///<returns>引数:D3DXVECTOR3型</returns>
	D3DXVECTOR3 Value_Vector_X()
	{
		return vec_X;
	}
	void Value_Vector_X(D3DXVECTOR3 n)
	{
		vec_X += n;
	}

	///<summary>
	///オブジェクトのY軸ベクトル標取得関数
	///</summary>
	///<pragma name="Value_Vector_Y">Value_Vector_Y</pragma>
	///<returns>引数:D3DXVECTOR3型</returns>
	D3DXVECTOR3 Value_Vector_Y()
	{
		return vec_Y;
	}
	void Value_Vector_Y(D3DXVECTOR3 n)
	{
		vec_Y += n;
	}

	///<summary>
	///オブジェクトのZ軸ベクトル取得関数
	///</summary>
	///<pragma name="Value_Vector_Z">Value_Vector_Z</pragma>
	///<returns>引数:D3DXVECTOR3型</returns>
	D3DXVECTOR3 Value_Vector_Z()
	{
		return vec_Z;
	}
	void Value_Vector_Z(D3DXVECTOR3 n)
	{
		vec_Z += n;
	}
	///<summary>
	///オブジェクトの角度取得関数
	///</summary>
	///<pragma name="Value_Rotation">Value_Rotation</pragma>
	///<returns>引数:D3DXMATRIX型</returns>
	D3DXMATRIX Value_Rotation() {
		return rotation;
	}
	void Value_Rotation(D3DXMATRIX n) {
		rotation += n;
	}

	/// <summary>
	/// スケールのX座標設定取得関数
	/// </summary>
	///<pragma name="Value_Scale_X">Value_Scale_X</pragma>
	///<returns>引数:double型</returns>
	double Value_Scale_X() {
		return scal_X;
	}
	void Value_Scale_X(double n) {
		scal_X += n;
	}

	/// <summary>
	/// スケールのY座標設定取得関数
	/// </summary>
	///<pragma name="Value_Scale_Y">Value_Scal_Y</pragma>
	///<returns>引数:double型</returns>
	double Value_Scale_Y() {
		return scal_Y;
	}
	void Value_Scale_Y(double n) {
		scal_Y += n;
	}

	/// <summary>
	/// スケールのZ座標設定取得関数
	/// </summary>
	///<pragma name="Value_Scale_Z">Value_Scale_Z</pragma>
	///<returns>引数:double型</returns>
	double Value_Scale_Z() {
		return scal_Z;
	}
	void Value_Scale_Z(double n) {
		scal_Z += n;
	}

	///<summary>
	///オブジェクトのスケール取得関数
	///</summary>
	///<pragma name="Value_Scaling">Value_Scaling</pragma>
	///<returns>引数:D3DXMATRIX型</returns>
	D3DXMATRIX Value_Scaling() {
		return scaling;
	}
	void Value_Scaling(D3DXMATRIX n) {
		scaling += n;
	}


	///<summary>
	///Objectの名前取得関数
	///</summary>
	///<pragma name="Name">Name</pragma>
	///<returns>引数:char *型</returns>
	void Name(char* Name) {
		name = Name;
	};
	const char* Name() {
		return name;
	};

	///<summary>
	///Objectのタグ取得関数
	///</summary>
	///<pragma name="Tag">Tag</pragma>
	///<returns>引数:char *型</returns>
	void Tag(char* Tag) {
		tag = Tag;
	};
	const char* Tag() {
		return tag;
	};


#pragma endregion

#pragma region Update関数
	/// <summary>
	/// BaseObjectのUpdate関数
	/// <para>各メンバの同期を行います</para>
	/// </summary>
	/// <pragma name="Update">Update</pragma>
	/// <returns></returns>
	void Update() {
		D3DXMATRIX Position;

		//引数を単位行列として、初期化する
		D3DXMatrixIdentity(&scaling);
		D3DXMatrixIdentity(&rotation);
		D3DXMatrixIdentity(&worldPosition);

		//オブジェクトのスケーリング
		D3DXMatrixScaling(&scaling, scal_X, scal_Y, scal_Z);

		Update_Rotation();

		//回転＊サイズ*移動
		D3DXMatrixTranslation(&Position, position.x, position.y, position.z);
		D3DXMatrixMultiply(&scaling, &scaling, &Position);
		D3DXMatrixMultiply(&worldPosition, &rotation, &scaling);
	}

	void Update_Rotation() {
		//オブジェクトの回転
		D3DXMatrixRotationY(&rotation, angle);

		//初期化
		vec_X = D3DXVECTOR3(1.0f, 0, 0);
		vec_Y = D3DXVECTOR3(0, 1.0f, 0);
		vec_Z = D3DXVECTOR3(0, 0, 01.0f);

		//ベクトルを現在の回転状態で更新
		D3DXVec3TransformCoord(&vec_X, &vec_X, &rotation);
		D3DXVec3TransformCoord(&vec_Y, &vec_Y, &rotation);
		D3DXVec3TransformCoord(&vec_Z, &vec_Z, &rotation);

	}
#pragma endregion

};

/*
class BaseObject {
private:
	//座標
	//現在の座標
	double pos_X;
	double pos_Y;
	double pos_Z;
	//次の座標(nextX,nextY,nextZの略)
	double pos_nX;
	double pos_nY;
	double pos_nZ;

	//角度
	double rad;     //ラジアン
	double angle;   //角度
	double sin;     //Sine
	double cos;     //cosine
	double tan;     //tangent

	//パラメーター
	double hp;          //体力
	double mp;          //魔力
	double st;          //スタミナ
	double attack;      //攻撃
	double defense;     //防御
	double speed;       //速度

	//情報
	char* name;
	char* tag;

#pragma endregion

public:
#pragma region コンストラクタ
	/// <summary>
	/// <para>@brief コンストラクタ</para>
	/// <para>@note 初期化関数</para>
	/// </summary>
	/// <remarks>
	/// 特に呼ぶ必要はないです
	/// </remarks>
	BaseObject() {
		pos_X = 0;
		pos_Y = 0;
		pos_Z = 0;
		pos_nX = 0;
		pos_nY = 0;
		pos_nZ = 0;

		rad = 0;
		angle = 0;
		sin = 0;
		cos = 0;
		tan = 0;

		hp = 0;
		mp = 0;
		st = 0;
		attack = 0;
		defense = 0;
		speed = 0;

		name = NULL;
		tag = NULL;
	};
#pragma endregion

#pragma region Acceser関数

	///<summary>
	///オブジェクトのX座標設定取得関数
	///</summary>
	///<pragma name="Value_PosX">Value_PosX</pragma>
	///<returns>引数:double型</returns>
	double Value_PosX()
	{
		return pos_X;
	};
	void Value_PosX(double n)
	{
		pos_X += n;
	};

	/// <summary>
	/// オブジェクトのY座標設定取得関数
	/// </summary>
	///<pragma name="Value_PosY">Value_PosY</pragma>
	///<returns>引数:double型</returns>
	double Value_PosY()
	{
		return pos_Y;
	}
	void Value_PosY(double n) {
		pos_Y = n;
	}

	/// <summary>
	/// オブジェクトのZ座標設定取得関数
	/// </summary>
	///<pragma name="Value_PosZ">Value_PosZ</pragma>
	///<returns>引数:double型</returns>
	double Value_PosZ()
	{
		return pos_Z;
	}
	void Value_PosZ(double n) {
		pos_Z = n;
	}

	/// <summary>
	/// オブジェクトの次のX座標設定取得関数
	/// </summary>
	///<pragma name="Value_NextPosX">Value_NextPosX</pragma>
	///<returns>引数:double型</returns>
	double Value_NextPosX()
	{
		return pos_nX;
	}
	void Value_NextPosX(double n){
		pos_nX;
	}

	/// <summary>
	/// オブジェクトの次のY座標設定取得関数
	/// </summary>
	///<pragma name="Value_NextPosY">Value_NextPosY</pragma>
	///<returns>引数:double型</returns>
	double Value_NextPosY() {
		return pos_nY;
	}
	void Value_NextPosY(double n) {
		pos_nY = n;
	}

	/// <summary>
	/// オブジェクトの次のZ座標設定取得関数
	/// </summary>
	///<pragma name="Value_NextPosZ">Value_NextPosZ</pragma>
	///<returns>引数:double型</returns>
	double Value_NextPosZ() {
		return pos_nZ;
	}
	double Value_NextPosZ(double n) {
		pos_nZ = n;
	}

	/// <summary>
	/// ラジアン値の設定取得関数
	/// </summary>
	///<pragma name="Value_Rad">Value_Rad</pragma>
	///<returns>引数:double型</returns>
	double Value_Rad() {
		return rad;
	}
	double Value_Rad(double n) {
		rad = n;
	}

	/// <summary>
	/// 角度の座標設定取得関数
	/// </summary>
	///<pragma name="Value_Angle">Value_Angle</pragma>
	///<returns>引数:double型</returns>
	double Value_Angle() {
		return angle;
	}
	double Value_Angle(double n) {
		angle = n;
	}

	///<summary>
	///Objectの名前取得関数
	///</summary>
	///<pragma name="Name">Name</pragma>
	///<returns>引数:char *型</returns>
	const char* Name(char* Name) {
		name = Name;
	};
	const char * Name() {
		return name;
	};

	///<summary>
	///Objectのタグ取得関数
	///</summary>
	///<pragma name="Tag">Tag</pragma>
	///<returns>引数:char *型</returns>
	const char* Tag(char* Tag) {
		tag = Tag;
	};
	const char* Tag() {
		return tag;
	};


#pragma endregion

};*/
