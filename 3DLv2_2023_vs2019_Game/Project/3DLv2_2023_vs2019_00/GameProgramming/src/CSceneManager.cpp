#include "CSceneManager.h"
#include "CTitleScene.h"
#include "CGameScene.h"

CSceneManager* CSceneManager::mpInstance = nullptr;

//インスタンスを取得
CSceneManager* CSceneManager::Instance()
{
	//インスタンスが存在しない場合は新しく生成する
	if (mpInstance == nullptr)
	{
		mpInstance = new CSceneManager();
	}
	return mpInstance;
}

//インスタンスを破棄
void CSceneManager::ClearInstance()
{
	delete mpInstance;
	mpInstance = nullptr;
}

//コンストラクタ
CSceneManager::CSceneManager()
	:mpScene(nullptr)
	,mNextScene(EScene::eNone)
{
}

//デストラクタ
CSceneManager::~CSceneManager()
{
	//読み込んでいるシーンがあれば、破棄する
	UnloadScene();
}

//シーン読み込み
void CSceneManager::LoadScene(EScene scene)
{
	//次に読み込むシーンを設定
	mNextScene = scene;

	////すでにシーンが読み込まれていたら、
	////そのシーンを破棄
	//UnloadScene();

	////読み込むシーンの種類に合わせて
	////生成するシーンのクラスを変更する
	//switch (scene)
	//{
	//	//タイトルシーン
	//case EScene::eTitle:	mpScene = new CTitleScene();	break;
	//	//ゲームシーン
	//case EScene::eGame:		mpScene = new CGameScene();		break;
	//}

	////シーンを新しく生成したら読み込み
	////シーン読み込み開始
	//if (mpScene != nullptr)
	//{
	//	mpScene->Load();
	//}
}

//読み込んでいるシーンを破棄
void CSceneManager::UnloadScene()
{
	delete mpScene;
	mpScene = nullptr;
}

void CSceneManager::LoadNextScene()
{
	//すでにシーンが読み込まれていたら
	//そのシーンを破棄
	UnloadScene();

	//読み込むシーンの種類に合わせて
	//生成するシーンのクラスを変更する
	switch (mNextScene)
	{
		//タイトルシーン
	case EScene::eTitle:	mpScene = new CTitleScene(); break;
		//ゲームのシーン
	case EScene::eGame:		mpScene = new CGameScene();  break;
	}

	//シーンを新しく生成したら読み込み
	//シーン読み込み開始
	if (mpScene != nullptr)
	{
		mpScene->Load();
	}
	//次のシーンの読み込みが終わったので
	//次のシーンのタイプは初期化
	mNextScene = EScene::eNone;
}

//読み込んでいるシーンの更新処理
void CSceneManager::Update()
{
	//シーンが読み込まれていたら、シーン更新
	if (mpScene != nullptr)
	{
		mpScene->Update();
	}

	//次のシーンが設定されていたら、次のシーン読み込み
	if (mNextScene != EScene::eNone)
	{
		LoadNextScene();
	}
	////シーンが読み込まれていない場合は、処理しない
	//if (mpScene == nullptr) return;
	////シーン更新
	//mpScene->Update();
}