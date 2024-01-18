#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CSoundManager.h"
#include "CBGMManager.h"
#include "CSceneManager.h"
#include "CGamePause.h"
#include "CSignboardPause.h"
#include "CFade.h"

CApplication::~CApplication()
{
}

void CApplication::Start()
{
	// デバッグカメラを作成
	CDebugCamera::DebugCamera();

	// フェードクラスを作成
	CFade::Instance();
	// ゲームポーズクラスを作成
	new CGamePause();
	// サウンド管理クラスを作成
	CSoundManager::Instance();
	// BGM管理クラスを作成
	CBGMManager::Instance();

	// 最初のシーンを読み込み
	new CSignboardPause();
	CSoundManager::Instance();
	CSceneManager::Instance()->LoadScene(EScene::eBootMenu);
}

void CApplication::End()
{
	CSceneManager::ClearInstance();
	CTaskManager::ClearInstance();
	CCollisionManager::ClearInstance();
	CResourceManager::ClearInstance();
	CSoundManager::ClearInstance();
}


void CApplication::Update()
{
	CTaskManager::Instance()->Delete();
	// タスクの更新処理
	CTaskManager::Instance()->Update();
	// 衝突処理
	CCollisionManager::Instance()->CollisionAll();

	// サウンドの更新
	CSoundManager::Instance()->Update();

	// シーンの更新
	CSceneManager::Instance()->Update();

	// タスクの描画処理
	CTaskManager::Instance()->Render();
	// コライダの描画
	CCollisionManager::Instance()->Render();
}
