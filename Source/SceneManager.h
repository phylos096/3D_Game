#pragma once
#include"Main.h"

enum class GameScene : int
{
	GameScene_StartMenu,
	GameScene_Play,
	GameScene_Result,
	GameScene_End,
	GameScene_None

};

class SceneManager
{
private:
	SceneManager();
	~SceneManager();
	GameScene NowScene;
	GameScene NextScene;
public:
	void Init();
	void Play();
	void Draw();
	void End();
	void ChangeScene();
};

