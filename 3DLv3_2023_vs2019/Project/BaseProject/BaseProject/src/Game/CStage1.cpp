#include "CStage1.h"
#include "CField_Worlds_1.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CGameCamera.h"
#include "CEnemyManager.h"
#include "CRotateFloorTimeGimmick.h"
#include "CRotateFloorGimmick.h"
#include "CWireMeshClimbWall.h"


// コンストラクタ
CStage1::CStage1()
{
	mStageNo = 1;
}

// デストラクタ
CStage1::~CStage1()
{
	
}

// ステージ読み込み
void CStage1::Load()
{
	// ステージ関連
	CResourceManager::Load<CModel>("Stage",			"Field\\GameStage(Worlds_1)\\GameStage_1(Stage).obj");				// ステージモデル
	CResourceManager::Load<CModel>("StageSky",		"Field\\GameStage(Worlds_1)\\GameStage_1(StageSky).obj");			// ステージ空モデル
	CResourceManager::Load<CModel>("FloorCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(floorCol).obj");			// 床のコライダー
	CResourceManager::Load<CModel>("WallCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(wallCol).obj");			// 壁のコライダー
	CResourceManager::Load<CModel>("FallCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(FallCol).obj");			// 落下判定コライダー
	CResourceManager::Load<CModel>("WireMesh",		"Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_Stop).obj");		// 金網モデル
	CResourceManager::Load<CModel>("WireMeshCol",	"Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_StopCol).obj");	// 金網コライダー
	CResourceManager::Load<CModel>("WireMeshTopCol","Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_StopTopCol).obj");// 金網頂上コライダー
	CResourceManager::Load<CModel>("Load",			"Field\\GameStage(Worlds_1)\\GameStage_1(load).obj");				// 道モデル
	CResourceManager::Load<CModel>("Cloud",			"Field\\GameStage(Worlds_1)\\GameStage_1(cloud).obj");				// 雲モデル
	CResourceManager::Load<CModel>("Fance",			"Field\\GameStage(Worlds_1)\\GameStage_1(fance).obj");				// フェンスモデル
	CResourceManager::Load<CModel>("Flowers",		"Field\\GameStage(Worlds_1)\\GameStage_1(flowers).obj");			// 花モデル
	CResourceManager::Load<CModel>("GoalPost",		"Field\\GameStage(Worlds_1)\\GameStage_1(GoalPost).obj");			// ゴールポストモデル
	CResourceManager::Load<CModel>("GoalBlock",		"Field\\GameStage(Worlds_1)\\GameStage_1(GoalBlock).obj");			// ゴールブロックモデル
	CResourceManager::Load<CModel>("Grass",			"Field\\GameStage(Worlds_1)\\GameStage_1(grass).obj");				// 草モデル
	CResourceManager::Load<CModel>("Mushroom",		"Field\\GameStage(Worlds_1)\\GameStage_1(mushroom).obj");			// キノコモデル
	CResourceManager::Load<CModel>("RockShrub",		"Field\\GameStage(Worlds_1)\\GameStage_1(rock&shrub).obj");			// 岩と低木モデル
	CResourceManager::Load<CModel>("SkyIsland",		"Field\\GameStage(Worlds_1)\\GameStage_1(skyisland).obj");			// 空島モデル
	CResourceManager::Load<CModel>("Tree",			"Field\\GameStage(Worlds_1)\\GameStage_1(Tree).obj");				// 木モデル
	CResourceManager::Load<CModel>("Branch",		"Field\\GameStage(Worlds_1)\\GameStage_1(Branch).obj");				// 切り株と木の枝モデル
	CResourceManager::Load<CModel>("Arrowsign",		"Field\\GameStage(Worlds_1)\\GameStage_1(arrowsign).obj");			// 矢印看板モデル

	CResourceManager::Load<CModel>("Signboard",		"Field\\Object\\signboard.obj");									// 看板オブジェクト(ジャンプヒント)
	CResourceManager::Load<CModel>("Number0",		"Field\\Object\\number0.obj");										// 零番目の床
	CResourceManager::Load<CModel>("Number1",		"Field\\Object\\number1.obj");										// 一番目の床ブロック
	CResourceManager::Load<CModel>("Number2",		"Field\\Object\\number2.obj");										// 二番目の床ブロック
	CResourceManager::Load<CModel>("Number3",		"Field\\Object\\number3.obj");										// 三番目の床ブロック

	CResourceManager::Load<CModel>("RotateFloor",			"Field\\Gimmick\\RotateFloor.obj");							// 回転する床
	CResourceManager::Load<CModel>("RotateFloorFrontCol",	"Field\\Gimmick\\RotateFloorFrontCol.obj");					// 回転する床の前コライダー
	CResourceManager::Load<CModel>("RotateFloorBackCol",	"Field\\Gimmick\\RotateFloorBackCol.obj");					// 回転する床の後ろコライダー

	// 背景色設定
	System::SetClearColor(0.1960784f, 0.6f, 0.8f, 1.0f);


	// フィールド
	mpField_Worlds_1 = new CField_Worlds_1();
	mpField_Worlds_1->Scale(8.0f, 8.f, 8.f);
	AddTask(mpField_Worlds_1);

	// 登れる金網を作成
	CWireMeshClimbWall* wiremeshWall = new CWireMeshClimbWall
	(
		"WireMesh", "WireMeshTopCol",
		CVector(0.0f, 14.5f, 0.0f),	// 上方向の移動
		CVector(0.0f, 0.0f, 10.0f)	// 正面方向の移動
	);
	wiremeshWall->Scale(8.0f, 8.0f, 8.0f);
	AddTask(wiremeshWall);

	// 回転する床ギミック(常に)
	CRotateFloorTimeGimmick* rotatetimegimmick = new CRotateFloorTimeGimmick(
		CVector(216.0f, 112.0f, -18.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotatetimegimmick);


	/////////////////////////////////////////////////////////////////////////////////////
	
	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(-150.0f, 136.0f, -5.3f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, -90.0f, 0.0f);
	}
	// カメラの位置と向きを設定
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 30.0f, -100.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt(
		camPos,
		playerPos,
		CVector::up
	);
	//  + CVector(0.0f, 10.0f, 0.0f)
	mainCamera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	mainCamera->AddCollider(mpField_Worlds_1->GetWallCol());
}


// ステージ破棄
void CStage1::Unload()
{
	// カメラから衝突するコライダーを取り除く
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->RemoveCollider(mpField_Worlds_1->GetWallCol());
	// ベースステージ破棄処理
	CStageBase::Unload();
}
