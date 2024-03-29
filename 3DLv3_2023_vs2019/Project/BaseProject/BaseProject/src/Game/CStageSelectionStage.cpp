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
	mStageNo = 0;
}

// デストラクタ
CStageSelectionStage::~CStageSelectionStage()
{

}

// ステージ読み込み
void CStageSelectionStage::Load()
{
	CResourceManager::Load<CModel>("StageSelection", "Field\\StageSentaku.obj");				// ステージセレクトステージ
	CResourceManager::Load<CModel>("StageSelectionFloorCol", "Field\\StageSentakuFloor.obj");	// ステージセレクトステージ(床)
	CResourceManager::Load<CModel>("StageSelectionWallCol", "Field\\StageSentakuWall.obj");		// ステージセレクトステージ(壁)
	CResourceManager::Load<CModel>("StageButton", "Field\\Object\\StageBotan.obj");				// ステージボタン
	CResourceManager::Load<CModel>("Needle", "Field\\Gimmick\\NeedleObject(needle).obj");		// 針オブジェクトの針
	CResourceManager::Load<CModel>("Needlebase", "Field\\Gimmick\\NeedleObject(base).obj");		// 針オブジェクトの土台
	CResourceManager::Load<CModel>("NeedleCol", "Field\\Gimmick\\NeedleObjectCol.obj");			// 針オブジェクトのコライダー
	CResourceManager::Load<CModel>("NeedleBaseCol", "Field\\Gimmick\\NeedleObjectBaseCol.obj");	// 針オブジェクトのベースコライダー

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