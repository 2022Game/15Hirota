#include "CStage2.h"
#include "CDamageObject.h"
#include "CGoalObject.h"
#include "CStone1.h"
#include "CTree1.h"
#include "CField1.h"
#include "CSoldier.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CAppearFloor.h"
#include "CGameCamera.h"
#include "CRotateFloorGimmick.h"

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
	CVector playerPos = CVector(-757.0f, 60.0f, -858.0f);//-757,858-1109.0f, 60.0f, 1133.0f
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 225.0f, 0.0f);//0.0f, 225.0f, 0.0f
	}

	// カメラの位置と向きを設定 -1109.0f, 90.0f, 1200.0f
	CGameCamera* mainCamera = new CGameCamera
		//CCamera* mainCamera = new CCamera
		(
			CVector(-757.0f, 90.0f, -958.0f),
			player->Position() + CVector(0.0f, 0.0f, 0.0f)
		);
	mainCamera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	mainCamera->AddCollider(field->GetWallCol());


	// 回転する床ギミック
	CRotateFloorGimmick* rotategimmick = new CRotateFloorGimmick(
		CVector(-770.0f, 7.0f, -888.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector rotategimmickPos = CVector(-770.0f, 7.0f, -888.0f);
	if (rotategimmick != nullptr)
	{
		rotategimmick->SetStartPosition(rotategimmickPos);
	}
	AddTask(rotategimmick);

	//// 木1 //////////////////////////////////////////////

	// 木1
	CTree1Obj* tree1 = new CTree1Obj(
		CVector(-1100.0f, 0.0f, 1100.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f));
	AddTask(tree1);

	// 木2
	CTree1Obj* tree2 = new CTree1Obj(
		CVector(-1000.0f, 0.0f, 1000.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f));
	AddTask(tree2);


	///////////////////////////////////////////////////////
}

// ステージ破棄
void CStage2::Unload()
{
	// ベースステージ破棄処理
	CStageBase::Unload();
}