﻿#include "CApplication.h"
//OpenGL
#include "glut.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CSceneManager.h"

CApplication::~CApplication()
{
}

void CApplication::Start()
{
	CSceneManager::Instance()->LoadScene(EScene::eBootMenu);
}

void CApplication::Update()
{
	CTaskManager::Instance()->Delete();
	// タスクの更新処理
	CTaskManager::Instance()->Update();
	// 衝突処理
	CCollisionManager::Instance()->CollisionAll();

	CSceneManager::Instance()->Update();

	// タスクの描画処理
	CTaskManager::Instance()->Render();
	// コライダの描画
	CCollisionManager::Instance()->Render();
}
