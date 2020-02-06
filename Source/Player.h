#pragma once
#include"Main.h"
#include"BaseObject.h"
#include"LoadModel.h"
#include"KeyInput.h"
#include"Camera.h"

class Player : public BaseObject, public LoadModel
{
private:
	KeyInput* input;
	LoadModel* model;
	Camera* camera;

public:

	BaseObject* baseobject;
	Player(HINSTANCE, HWND, IDirect3DDevice9*);
	//~Player();
	void Move();
	void Update();
	void Result();
	void Draw(IDirect3DDevice9*);
	void End();

};