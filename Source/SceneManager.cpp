#include"SceneManager.h"

SceneManager::SceneManager() {
	NowScene = GameScene::GameScene_StartMenu;
	NextScene = GameScene::GameScene_None;
};

SceneManager::~SceneManager() {

};

//init ������
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
	if (NextScene != GameScene::GameScene_None) {		//���̃V�[�����Z�b�g����Ă�����
		End();	    //���݂̃V�[���̏I�����������s
		NowScene = NextScene;			//���̃V�[�������݂̃V�[���ɃZ�b�g
		NextScene = GameScene::GameScene_None;			//���̃V�[�������N���A
		Init();	//���݂̃V�[����������
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
