#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CSoundManager.h"
#include "CSceneManager.h"
#include "CGamePause.h"
#include "CSignboardPause.h"

CApplication::~CApplication()
{
}

void CApplication::Start()
{
	new CGamePause();
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
