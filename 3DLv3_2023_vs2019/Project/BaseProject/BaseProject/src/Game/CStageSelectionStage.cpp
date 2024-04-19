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

// ステージ読み込み
void CStageSelectionStage::Load()
{
	CResourceManager::Load<CModel>("StageSelection", "Field\\StageSentaku.obj");				// ステージセレクトステージ
	CResourceManager::Load<CModel>("StageSelectionFloorCol", "Field\\StageSentakuFloor.obj");	// ステージセレクトステージ(床)
	CResourceManager::Load<CModel>("StageSelectionWallCol", "Field\\StageSentakuWall.obj");		// ステージセレクトステージ(壁)
	CResourceManager::Load<CModel>("StageButton", "Field\\Object\\StageBotan.obj");				// ステージボタン
	CResourceManager::Load<CModel>("FlamethrowerModel", "Field\\Gimmick\\Flamethrower(foundation).obj");					// 火炎放射器(土台)
	CResourceManager::Load<CModel>("FlamethrowerTank", "Field\\Gimmick\\Flamethrower(tank).obj");							// 火炎放射器(タンク)
	CResourceManager::Load<CModel>("FlamethrowerCol", "Field\\Gimmick\\Flamethrower(WallCol).obj");						// 火炎放射器(コライ
	CResourceManager::Load<CModel>("TreasureChest", "Field\\Gimmick\\TreasureChest.obj");								// 宝箱
	CResourceManager::Load<CModel>("TreasureChestTwo", "Field\\Gimmick\\TreasureChestTwo.obj");							// 宝箱(蓋)
	CResourceManager::Load<CModel>("TreasureChestCol", "Field\\Gimmick\\TreasureChest(FloorCol).obj");						// 宝箱(蓋コライダー)
	CResourceManager::Load<CModel>("TreasureChestWallCol", "Field\\Gimmick\\TreasureChest(WallCol).obj");						// 宝箱(壁コライダー)
	//CResourceManager::Load<CModel>("Needle", "Field\\Gimmick\\NeedleObject(needle).obj");		// 針オブジェクトの針
	//CResourceManager::Load<CModel>("Needlebase", "Field\\Gimmick\\NeedleObject(base).obj");		// 針オブジェクトの土台
	//CResourceManager::Load<CModel>("NeedleCol", "Field\\Gimmick\\NeedleObjectCol.obj");			// 針オブジェクトのコライダー
	//CResourceManager::Load<CModel>("NeedleBaseCol", "Field\\Gimmick\\NeedleObjectBaseCol.obj");	// 針オブジェクトのベースコライダー
	
	//CResourceManager::Load<CModelX>("Vanguard", "Character\\Vanguard\\VanguardModel.x");

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

	// 火炎放射器モデル
	// 右方向
	/*CFixedFlamethrower* flamethrower2 = new CFixedFlamethrower
	(
		CVector(-10.0f, 12.0f, 0.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(flamethrower2);*/

	//// 宝箱
	//CTreasureChest* treasure = new CTreasureChest
	//(
	//	CVector(-15.0f, 11.0f, 0.0f),
	//	CVector(7.0f, 7.0f, 7.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(treasure);
	//// 宝箱蓋
	//CTreasureChestTwo* treasureTwo = new CTreasureChestTwo
	//(
	//	CVector(-15.0f, 15.8f, 0.0f),
	//	CVector(7.0f, 7.0f, 7.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(treasureTwo);


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

	//// ヴァンガード
	//CVanguard* van = new CVanguard();
	//CVanguard* vanPos = CVanguard::Instance();
	//van->Scale(1.4f, 1.4f, 1.4f);
	//van->Position(50.0f, 60.0f, 0.0f);
	//AddTask(van);

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