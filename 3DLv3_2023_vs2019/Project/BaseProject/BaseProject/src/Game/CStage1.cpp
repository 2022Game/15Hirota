#include "CStage1.h"
#include "CMoveFloor.h"
#include "CGoalObject.h"
#include "CStone1.h"
#include "CField.h"
#include "CSoldier.h"
#include "CPlayer.h"
#include "CCamera.h"

// コンストラクタ
CStage1::CStage1()
{
	mStageNo = 0;
}

// デストラクタ
CStage1::~CStage1()
{
	
}

// ステージ読み込み
void CStage1::Load()
{
	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);


	// フィールド
	CField* field = new CField();
	AddTask(field);


	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(0.0f, 60.0f, -20.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
	}

	// カメラの位置と向きを設定
	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 80.0f, 45.0f),
		player->Position() + CVector(0.0f, 10.0f, 0.0f)
	);
	mainCamera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	mainCamera->AddCollider(field->GetWallCol());

	//// カメラの位置と向きを設定
	//CCamera* mainCamera = CCamera::MainCamera();
	//if (mainCamera != nullptr)
	//{
	//	CVector eye = CVector(0.0f, 80.0f, 75.0f);
	//	CVector at = player->Position() + CVector(0.0f,10.0f,0.0f);
	//	CVector forward = (at - eye).Normalized();
	//	CVector side = CVector::Cross(forward, CVector::up);
	//	CVector up = CVector::Cross(side, forward);
	//	mainCamera->LookAt(eye, at, up);
	//	mainCamera->SetFollowTargetTf(player);
	//	// スフィアかメッシュぐらい
	//	mainCamera->AddCollider(field->GetWallCol());
	//}

	// 四角モデル
	CMoveFloor* floor = new CMoveFloor( 
		CVector(-20.0f, -20.0f, -340.0f), 
		CVector(5.5f, 1.0f, 3.25f), 
		CVector(0.0f, 0.0f, 0.0f), 
		5.0f);
	AddTask(floor);

	// ゴールオブジェクト
	CGoalObject* goal = new CGoalObject(
		CVector(0.0f, 0.0f, -100.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 90.0f, 0.0f));
	AddTask(goal);

	// 岩1
	CStone1* stone1 = new CStone1(
		CVector(-80.0f, 0.0f, -200.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f));
	AddTask(stone1);

	// 敵(ガスマスク兵士) ///////////////////////////
	CSoldier* sol1 = new CSoldier();
	sol1->Scale(1.0f, 1.0f, 1.0f);
	sol1->Position(-100.0f, 150, -100);
	AddTask(sol1);
	

	CSoldier* sol2 = new CSoldier();
	sol2->Scale(1.0f, 1.0f, 1.0f);
	sol2->Position(-50.0f, 150.0f, -100.0f);
	AddTask(sol2);

	CSoldier* sol3 = new CSoldier();
	sol3->Scale(1.0f, 1.0f, 1.0f);
	sol3->Position(50.0f, 150.0f, -150.0f);
	AddTask(sol3);

	/////////////////////////////////////////////////
}

// ステージ破棄
void CStage1::Unload()
{
	// ベースステージ破棄処理
	CStageBase::Unload();
}