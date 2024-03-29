#include "CStage1.h"
#include "CField_Worlds_1.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CGameCamera.h"
#include "CEnemyManager.h"
#include "CRotateFloorTimeGimmick.h"


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
	CResourceManager::Load<CModel>("Stage",			"Field\\GameStage(Worlds_1)\\GameStage_1(Stage).obj");			// ステージモデル
	CResourceManager::Load<CModel>("FloorCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(floorCol).obj");		// 床のコライダー
	CResourceManager::Load<CModel>("WallCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(wallCol).obj");		// 壁のコライダー
	CResourceManager::Load<CModel>("FallCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(FallCol).obj");		// 落下判定コライダー
	CResourceManager::Load<CModel>("ClimbWall_1",	"Field\\GameStage(Worlds_1)\\GameStage_1(ClimbWall(1)).obj");	// 登頂後斜めに移動する壁
	CResourceManager::Load<CModel>("ClimbWall_2",	"Field\\GameStage(Worlds_1)\\GameStage_1(ClimbWall(2)).obj");	// 登頂後真横に移動する壁
	CResourceManager::Load<CModel>("Load",			"Field\\GameStage(Worlds_1)\\GameStage_1(load).obj");			// 道モデル
	CResourceManager::Load<CModel>("Cloud",			"Field\\GameStage(Worlds_1)\\GameStage_1(cloud).obj");			// 雲モデル
	CResourceManager::Load<CModel>("Fance",			"Field\\GameStage(Worlds_1)\\GameStage_1(fance).obj");			// フェンスモデル
	CResourceManager::Load<CModel>("Flowers",		"Field\\GameStage(Worlds_1)\\GameStage_1(flowers).obj");		// 花モデル
	CResourceManager::Load<CModel>("GoalPost",		"Field\\GameStage(Worlds_1)\\GameStage_1(GoalPost).obj");		// ゴールポストモデル
	CResourceManager::Load<CModel>("GoalBlock",		"Field\\GameStage(Worlds_1)\\GameStage_1(GoalBlock).obj");		// ゴールブロックモデル
	CResourceManager::Load<CModel>("Grass",			"Field\\GameStage(Worlds_1)\\GameStage_1(grass).obj");			// 草モデル
	CResourceManager::Load<CModel>("Mushroom",		"Field\\GameStage(Worlds_1)\\GameStage_1(mushroom).obj");		// キノコモデル
	CResourceManager::Load<CModel>("RockShrub",		"Field\\GameStage(Worlds_1)\\GameStage_1(rock&shrub).obj");		// 岩と低木モデル
	CResourceManager::Load<CModel>("SkyIsland",		"Field\\GameStage(Worlds_1)\\GameStage_1(skyisland).obj");		// 空島モデル
	CResourceManager::Load<CModel>("TreeBranch",	"Field\\GameStage(Worlds_1)\\GameStage_1(Tree&Branch).obj");	// 木と切り株と木の枝モデル
	CResourceManager::Load<CModel>("Arrowsign",		"Field\\GameStage(Worlds_1)\\GameStage_1(arrowsign).obj");		// 矢印看板モデル

	CResourceManager::Load<CModel>("Signboard",		"Field\\Object\\signboard.obj");								// 看板オブジェクト(ジャンプヒント)
	CResourceManager::Load<CModel>("Number0", "Field\\Object\\number0.obj");										// 零番目の床
	CResourceManager::Load<CModel>("Number1", "Field\\Object\\number1.obj");										// 一番目の床ブロック
	CResourceManager::Load<CModel>("Number2", "Field\\Object\\number2.obj");										// 二番目の床ブロック
	CResourceManager::Load<CModel>("Number3", "Field\\Object\\number3.obj");

	CResourceManager::Load<CModel>("RotateFloor",		"Field\\Gimmick\\RotateFloor.obj");							// 回転する床
	CResourceManager::Load<CModel>("RotateFloorFrame",	"Field\\Gimmick\\RotateFloorFrame.obj");					// 回転する床枠

	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);


	// フィールド
	CField_Worlds_1* field = new CField_Worlds_1();
	field->Scale(10.0f, 10.f, 10.f);
	AddTask(field);

	
	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(-195.0f, 200.0f, 9.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, -180.0f, 0.0f);
	}
	// カメラの位置と向きを設定
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 30.0f, -100.0f);
	CGameCamera* mainCamera = new CGameCamera
		//CCamera* mainCamera = new CCamera
		(
			camPos,
			player->Position() + CVector(0.0f, 10.0f, 0.0f)
		);
	mainCamera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	mainCamera->AddCollider(field->GetWallCol());


	// 回転する床ギミック(常に)
	CRotateFloorTimeGimmick* rotatetimegimmick = new CRotateFloorTimeGimmick(
		CVector(285.0f, 170.0f, -24.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector rotatetimegimmickPos = CVector(285.0f, 170.0f, -24.0f);
	if (rotatetimegimmick != nullptr)
	{
		rotatetimegimmick->SetStartPosition(rotatetimegimmickPos);
		rotatetimegimmick->Rotation(0.0f, 0.0f, 180.0f);
	}
	AddTask(rotatetimegimmick);
}


// ステージ破棄
void CStage1::Unload()
{
	// ベースステージ破棄処理
	CStageBase::Unload();
}
