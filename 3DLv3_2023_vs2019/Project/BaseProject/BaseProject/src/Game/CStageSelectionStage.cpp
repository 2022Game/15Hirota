#include "CStageSelectionStage.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CStageSelection.h"
#include "CPlayer.h"
#include "CStageButton.h"
#include "CNeedle.h"
#include "CVanguard.h"
#include "CFixedFlamethrower.h"
#include "CTreasureChest.h"

// コンストラクタ
CStageSelectionStage::CStageSelectionStage()
{
	mStageNo = 0;
}

// デストラクタ
CStageSelectionStage::~CStageSelectionStage()
{

}

CVector CStageSelectionStage::GetPlayerStartPosition()
{
	CVector playerPos;

	// プレイヤーを取得
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		// ステージ3をクリアしているかどうかをチェック(仮)
		bool playerStage3 = player->IsStageClear();

		// プレイヤーの初期位置を設定
		if (playerStage3)
		{
			// ステージ3をクリアしている場合の初期位置
			playerPos = CVector(-160, 50.0f, 0.0f);
		}
		else
		{
			// ステージ3をクリアしていない場合の初期位置
			playerPos = CVector(-235.0f, 20.0f, 0.0f);
		}
	}

	return playerPos;
}

// ステージ読み込み
void CStageSelectionStage::Load()
{
	CResourceManager::Load<CModel>("StageSelection", "Field\\StageSentaku.obj");				// ステージセレクトステージ
	CResourceManager::Load<CModel>("StageSelectionFloorCol", "Field\\StageSentakuFloor.obj");	// ステージセレクトステージ(床)
	CResourceManager::Load<CModel>("StageSelectionWallCol", "Field\\StageSentakuWall.obj");		// ステージセレクトステージ(壁)
	CResourceManager::Load<CModel>("StageButton", "Field\\Object\\StageBotan.obj");				// ステージボタン

	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	// フィールド
	CStageSelection* field = new CStageSelection();
	AddTask(field);

	// ステージ選択モデル
	CStageButton* button = new CStageButton(
		CVector(-160.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(button);


	//// 針モデル
	//CNeedle* needle = new CNeedle(
	//	CVector(100.0f, 11.0f, 0.0f),
	//	CVector(10.0f, 10.0f, 10.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer);
	//CVector needlePos = CVector(100.0f, 11.0f, 0.0f);
	//if (needle != nullptr)
	//{
	//	needle->SetStartPosition(needlePos);
	//}
	//AddTask(needle);
	//// 針モデルベース
	//CNeedleBase* needlebase = new CNeedleBase(
	//	CVector(100.0f, 11.0f, 0.0f),
	//	CVector(10.0f, 10.0f, 10.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer);
	//CVector needlebasePos = CVector(100.0f, 11.0f, 0.0f);
	//if (needlebase != nullptr)
	//{
	//	needlebase->SetStartPosition(needlebasePos);
	//}
	//AddTask(needlebase);

	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	bool playerStage3 = player->IsStage3Clear();
	// プレイヤーの初期位置を取得
	CVector playerPos = GetPlayerStartPosition();
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, -90.0f, 0.0f);
	}

	// カメラの位置と向きを設定
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 30.0f, -100.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt(camPos, playerPos, CVector::up);
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