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
#include "CStageSelectCamera.h"
#include "CStage1MenuObject.h"
#include "CStage1Button.h"
#include "CStage3MenuObject.h"
#include "CStage3Button.h"

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
			playerPos = CVector(-180, 30.0f, 0.0f);
		}
		else
		{
			// ステージ3をクリアしていない場合の初期位置
			playerPos = CVector(-160.0f, 20.0f, 0.0f);
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
	CResourceManager::Load<CModel>("SkyIslandMenu",		"Field\\Object\\Skyisland.obj");	// 空島モデル
	CResourceManager::Load<CModel>("Number3", "Field\\Object\\number3.obj");					// 三番目の床ブロック

	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	// フィールド
	CStageSelection* field = new CStageSelection();
	AddTask(field);


	// ステージ1選択モデル
	CStage1Button* stage1button = new CStage1Button(
		CVector(-60.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(stage1button);

	// ステージ3選択モデル
	CStage3Button* stage3button = new CStage3Button(
		CVector(-160.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(stage3button);

	// ステージメニューオブジェクト(ステージ1)
	CStageMenuObject* menuobj1 = new CStageMenuObject(
		CVector(-60.0f, 12.0f, -55.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 40.0f, 0.0f),
		ETag::ePlayer, ELayer::eDamageCol);
	AddTask(menuobj1);

	// ステージメニューオブジェクト(ステージ3)
	CStage3MenuObject* menuobj3 = new CStage3MenuObject(
		CVector(-160.0f, 12.0f, -55.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 40.0f, 0.0f),
		ETag::ePlayer, ELayer::eDamageCol);
	AddTask(menuobj3);



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

	// ステージ選択画面は、ステージ選択画面用のカメラを使用するため、
	// ゲームのカメラを削除する
	CCamera* camera = CCamera::MainCamera();
	if (camera != nullptr)
	{
		camera->Kill();
	}

	// カメラの位置をプレイヤーから一定量離れた位置に設定
	CVector camPos = playerPos + CVector(0.0f, 70.0f, 100.0f);
	// ステージ選択カメラを生成
	camera = new CStageSelectCamera
	(
		camPos,
		playerPos,	// カメラの注視点はプレイヤーの座標
		true
	);
	// カメラをプレイヤーに追従させる
	camera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	//mainCamera->AddCollider(field->GetWallCol());
}

// ステージ破棄
void CStageSelectionStage::Unload()
{
	// ベースステージ破棄処理
	CStageBase::Unload();

	// ステージ選択画面のカメラを削除
	CCamera* camera = CCamera::MainCamera();
	if (camera != nullptr)
	{
		camera->Kill();
	}
	// ステージ中のカメラを生成
	new CGameCamera
	(
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);

}