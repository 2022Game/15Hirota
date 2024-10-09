#include "CStage3.h"
#include "CPlayer.h"
#include "CSoldier.h"
#include "CVanguard.h"
#include "CStageSky.h"
#include "CCamera.h"
#include "CStageTime.h"
#include "CGameCamera.h"
#include "CEnemyManager.h"
#include "CInput.h"
#include "CFinalStageField.h"
#include "CFinalStageFallCol.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"

// コンストラクタ
CStage3::CStage3()
{
	mStageNo = 3;
}

// デストラクタ
CStage3::~CStage3()
{

}

// ステージ読み込み
void CStage3::Load()
{
	// ステージ関連
	// ステージの空
	CResourceManager::Load<CModel>("StageSky",						"Field\\StageSky\\Sky(Sphere).obj");
	// ステージモデル
	CResourceManager::Load<CModel>("Stage3Base",							"Field\\GameStage(Worlds_3)\\GameStage_1(Stage).obj");
	// ステージ空モデル
	CResourceManager::Load<CModel>("StageSky",						"Field\\GameStage(Worlds_3)\\GameStage_1(StageSky).obj");
	// 床のコライダー
	CResourceManager::Load<CModel>("Stage3FallCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(floorCol).obj");
	// 壁のコライダー
	CResourceManager::Load<CModel>("WallCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(wallCol).obj");
	// 落下判定コライダー
	CResourceManager::Load<CModel>("FallCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(FallCol).obj");
	
	// 肉モデル
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");

	// 背景色設定
	System::SetClearColor(0.1960784f, 0.6f, 0.8f, 1.0f);

	CInput::ShowCursor(false);

	//// フィールド関連 /////////////////////////////////////////////////////////////////

	// フィールド
	mpFinalStage = new CFinalStageField();
	mpFinalStage->Scale(1.0f, 1.0f, 1.0f);
	AddTask(mpFinalStage);
	// 落下コライダー
	mpFinalStageFallCol = new CFinalStageFallCol();
	mpFinalStageFallCol->Scale(1.0f, 1.0f, 1.0f);
	AddTask(mpFinalStageFallCol);
	// 空
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);

	
	// スコアアイテム

	//// ブルーメダル1
	//CBlueMedal* blueMedal1 = new CBlueMedal
	//(
	//	CVector(317.0f, 126.0f, -18.0f) ,
	//	CVector(3.0f, 3.0f, 3.0f)
	//);
	//AddTask(blueMedal1);
	//// ブルーメダル2
	//CBlueMedal* blueMedal2 = new CBlueMedal
	//(
	//	CVector(330.0f, 126.0f, -83.0f),
	//	CVector(3.0f, 3.0f, 3.0f)
	//);
	//AddTask(blueMedal2);
	//// ブルーメダル3
	//CBlueMedal* blueMedal3 = new CBlueMedal
	//(
	//	CVector(401.0f, 140.0f, -436.0f),
	//	CVector(3.0f, 3.0f, 3.0f)
	//);
	//AddTask(blueMedal3);

	//// 肉オブジェクト /////////////////////////////////////////////////////////////////

	CMeat1* meat1 = new CMeat1
	(
		CVector(0.0f, 430.0f, -1950.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat1->SetMeatNumber(1);
	AddTask(meat1);

	CMeat2* meat2 = new CMeat2
	(
		CVector(0.0f, 430.0f, -2000.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat2->SetMeatNumber(2);
	AddTask(meat2);

	CMeat3* meat3 = new CMeat3
	(
		CVector(0.0f, 430.0f, -2050.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat3->SetMeatNumber(3);
	AddTask(meat3);

	/////////////////////////////////////////////////////////////////////////////////////

	//// キャラクター関連 ///////////////////////////////////////////////////////////////

	// キャラクター
	
	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	// 初期値点 : 190.0f, 130.0f.0f, 269.0f
	// 中間地点 : 0.0f, 320.0f, -1050.0f
	// ボス前	: 0.0f, 430.0f, -1890.0f
	// ゴール付近:	-367.0f, 395.0f, -2040.0f
	// 火炎放射器の前 : -207.0f, 126.0f, -912.0f
	CVector playerPos = CVector(0.0f, 10.0f, 0.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 20.0f, 0.0f);
	}
	// カメラの位置と向きを設定
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 20.0f, -80.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt(
		camPos,
		playerPos,
		CVector::up
	);
	mainCamera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	//mainCamera->AddCollider(mpPlainsStageField->GetWallCol());

}

// ステージ破棄
void CStage3::Unload()
{
	// カメラから衝突するコライダーを取り除く
	CCamera* mainCamera = CCamera::MainCamera();
	//mainCamera->RemoveCollider(mpPlainsStageField->GetWallCol());
	// ベースステージ破棄処理
	CStageBase::Unload();
}