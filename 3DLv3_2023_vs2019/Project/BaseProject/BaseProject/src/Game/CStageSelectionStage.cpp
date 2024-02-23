#include "CStageSelectionStage.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CStageSelection.h"
#include "CPlayer.h"
#include "CStageButton.h"
#include "CNeedle.h"

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

	// ステージ選択モデル
	CStageButton* button = new CStageButton(
		CVector(150.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(button);

	// 針モデル
	CNeedle* needle = new CNeedle(
		CVector(100.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	CVector needlePos = CVector(100.0f, 11.0f, 0.0f);
	if (needle != nullptr)
	{
		needle->SetStartPosition(needlePos);
	}
	AddTask(needle);
	// 針モデルベース
	CNeedleBase* needlebase = new CNeedleBase(
		CVector(100.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	CVector needlebasePos = CVector(100.0f, 11.0f, 0.0f);
	if (needlebase != nullptr)
	{
		needlebase->SetStartPosition(needlebasePos);
	}
	AddTask(needlebase);

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
			CVector(-245.0f, 80.0f, 55.0f),
			player->Position() + CVector(0.0f, 0.0f, 0.0f)
		);
	mainCamera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	//mainCamera->AddCollider(field->GetWallCol());
}

// ステージ破棄
void CStageSelectionStage::Unload()
{
	// ベースステージ破棄処理
	CStageBase::Unload();
}