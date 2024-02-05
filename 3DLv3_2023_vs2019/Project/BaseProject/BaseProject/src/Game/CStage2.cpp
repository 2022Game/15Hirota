#include "CStage2.h"
#include "CDamageObject.h"
#include "CGoalObject.h"
#include "CStone1.h"
#include "CField1.h"
#include "CSoldier.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CAppearFloor.h"
#include "CGameCamera.h"

// コンストラクタ
CStage2::CStage2()
{
	mStageNo = 0;
}

// デストラクタ
CStage2::~CStage2()
{

}

// ステージ読み込み
void CStage2::Load()
{
	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);


	// フィールド
	CField1* field = new CField1();
	field->Scale(10.0f, 10.0f, 10.0f);
	AddTask(field);


	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = CVector(1000.0f, 30.0f, 260.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
	}

	// カメラの位置と向きを設定
	CGameCamera* mainCamera = new CGameCamera
		//CCamera* mainCamera = new CCamera
		(
			CVector(1000.0f, 50.0f, 310.0f),
			player->Position() + CVector(0.0f, 10.0f, 0.0f)
		);
	mainCamera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	//mainCamera->AddCollider(field->GetWallCol());

	//// カメラの位置と向きを設定
	//CCamera* mainCamera = CCamera::MainCamera();
	//if (mainCamera != nullptr)
	//{
	//	CVector eye = CVector(0.0f, 80.0f, 45.0f);
	//	CVector at = playerPos + CVector(0.0f, 0.0f, 0.0f);
	//	mainCamera->LookAt(eye, at, CVector::up);
	//}
	//mainCamera->SetFollowTargetTf(player);
	//// スフィアかメッシュぐらい
	//mainCamera->AddCollider(field->GetWallCol());
}

// ステージ破棄
void CStage2::Unload()
{
	// ベースステージ破棄処理
	CStageBase::Unload();
}