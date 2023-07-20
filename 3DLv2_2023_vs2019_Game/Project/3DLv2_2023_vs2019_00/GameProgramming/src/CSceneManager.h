#ifndef CSCENEMANAGER_H
#define CSCENEMANAGER_H

#include "CSceneBase.h"
#include "SceneType.h"

//シーンを管理するクラス
class CSceneManager
{
public:
	//インスタンスを取得
	static CSceneManager* Instance();
	//インスタンスを破棄
	static void ClearInstance();
	//シーン読み込み
	void LoadScene(EScene scene);
	//読み込んでいるシーンを破棄
	void UnloadScene();
	//読み込んでいるシーンの更新処理
	void Update();

private:
	//コンストラクタ
	CSceneManager();
	//デストラクタ
	~CSceneManager();

	//次のシーンを読み込み
	void LoadNextScene();

	//CSceneManagerのインスタンス
	static CSceneManager* mpInstance;
	//現在読み込んでいるシーン
	CSceneBase* mpScene;
	//次に読み込むシーン
	EScene mNextScene;
};
#endif