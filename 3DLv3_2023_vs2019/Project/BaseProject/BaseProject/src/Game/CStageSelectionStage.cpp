#include "CStageSelectionStage.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CStageSelection.h"
#include "CPlayer.h"

// コンストラクタ
CStageSelectionStage::CStageSelectionStage()
{
	mStageNo = 2;
}

// デストラクタ
CStageSelectionStage::~CStageSelectionStage()
{

}

// ステージ読み込み
void CStageSelectionStage::Load()
{
	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	// フィールド
	CStageSelection* field = new CStageSelection();
	AddTask(field);


	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = CVector(-245.0f, 60.0f, 0.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, -90.0f, 0.0f);
	}

	// カメラの位置と向きを設定
	CGameCamera* mainCamera = new CGameCamera
		//CCamera* mainCamera = new CCamera
		(
			CVector(-245.0f, 80.0f, 45.0f),
			player->Position() + CVector(0.0f, 0.0f, 0.0f)
		);
	mainCamera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	mainCamera->AddCollider(field->GetWallCol());
}

// ステージ破棄
void CStageSelectionStage::Unload()
{
	// ベースステージ破棄処理
	CStageBase::Unload();
}