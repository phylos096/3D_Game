#include"SceneManager.h"

SceneManager::SceneManager() {
	NowScene = GameScene::GameScene_StartMenu;
	NextScene = GameScene::GameScene_None;
};

SceneManager::~SceneManager() {

};

//init 初期化
void SceneManager::Init() {
	switch (NowScene) {
	case GameScene::GameScene_StartMenu:
		break;
	case GameScene::GameScene_Play:
		break;
	case GameScene::GameScene_Result:
		break;
	case GameScene::GameScene_End:
		break;
	default:
		break;
	};
};

void SceneManager::Play() {
	if (NextScene != GameScene::GameScene_None) {		//次のシーンがセットされていたら
		End();	    //現在のシーンの終了処理を実行
		NowScene = NextScene;			//次のシーンを現在のシーンにセット
		NextScene = GameScene::GameScene_None;			//次のシーン情報をクリア
		Init();	//現在のシーンを初期化
	}
	switch(NowScene) {
	case GameScene::GameScene_StartMenu:
		break;
	case GameScene::GameScene_Play:
		break;
	case GameScene::GameScene_Result:
		break;
	case GameScene::GameScene_End:
		break;
	default:
		break;
	};
};

void SceneManager::Draw() {

	switch (NowScene) {
	case GameScene::GameScene_StartMenu:
		break;
	case GameScene::GameScene_Play:
		break;
	case GameScene::GameScene_Result:
		break;
	case GameScene::GameScene_End:
		break;
	default:
		break;
	};
};

void SceneManager::ChangeScene() {
	NowScene = NextScene;
};

//End
void SceneManager::End() {
	switch (NowScene) {
	case GameScene::GameScene_StartMenu:
		break;
	case GameScene::GameScene_Play:
		break;
	case GameScene::GameScene_Result:
		break;
	case GameScene::GameScene_End:
		break;
	default:
		break;
	};
};
