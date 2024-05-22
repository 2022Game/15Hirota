#include "CStage1.h"
#include "CField_Worlds_1.h"
#include "CField_Worlds_1_FallCol.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CGameCamera.h"
#include "CEnemyManager.h"
#include "CRotateFloorTimeGimmick.h"
#include "CRotateFloorGimmick.h"
#include "CWireMeshClimbWall.h"
#include "CWireMeshMoveClimbWall.h"
#include "CVanguard.h"
#include "CStageTime.h"
#include "CBlueMedal.h"
#include "CRotationg.h"
#include "CFixedFlamethrower.h"
#include "CJumpingObject.h"
#include "CSavePoint.h"
#include "CNumberFloor1.h"
#include "CNumberFloorOnce.h"
#include "CTreasureChest.h"
#include "CHatenaBlock.h"
#include "CRengaBlock.h"


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
	CResourceManager::Load<CModel>("Stage",				 "Field\\GameStage(Worlds_1)\\GameStage_1(Stage).obj");					// ステージモデル
	CResourceManager::Load<CModel>("StageSky",			 "Field\\GameStage(Worlds_1)\\GameStage_1(StageSky).obj");				// ステージ空モデル
	CResourceManager::Load<CModel>("FloorCol",			 "Field\\GameStage(Worlds_1)\\GameStage_1(floorCol).obj");				// 床のコライダー
	CResourceManager::Load<CModel>("WallCol",			 "Field\\GameStage(Worlds_1)\\GameStage_1(wallCol).obj");				// 壁のコライダー
	CResourceManager::Load<CModel>("FallCol",			 "Field\\GameStage(Worlds_1)\\GameStage_1(FallCol).obj");				// 落下判定コライダー
	CResourceManager::Load<CModel>("WireMesh",			 "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_Stop).obj");			// 金網モデル
	CResourceManager::Load<CModel>("WireMeshCol",		 "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_StopCol).obj");		// 金網コライダー
	CResourceManager::Load<CModel>("WireMeshTopCol",	 "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_StopTopCol).obj");	// 金網頂上コライダー
	CResourceManager::Load<CModel>("WireMeshMove",		 "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_Move).obj");			// 動く金網モデル
	CResourceManager::Load<CModel>("WireMeshMoveCol",	 "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_MoveCol).obj");		// 動く金網コライダー
	CResourceManager::Load<CModel>("WireMeshMoveTopCol", "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_MoveTopCol).obj");	// 動く金網頂上コライダー
	CResourceManager::Load<CModel>("Load",				 "Field\\GameStage(Worlds_1)\\GameStage_1(load).obj");					// 道モデル
	CResourceManager::Load<CModel>("Cloud",				 "Field\\GameStage(Worlds_1)\\GameStage_1(cloud).obj");					// 雲モデル
	CResourceManager::Load<CModel>("Fance",				 "Field\\GameStage(Worlds_1)\\GameStage_1(fance).obj");					// フェンスモデル
	CResourceManager::Load<CModel>("Flowers",			 "Field\\GameStage(Worlds_1)\\GameStage_1(flowers).obj");				// 花モデル
	CResourceManager::Load<CModel>("GoalPost",			 "Field\\GameStage(Worlds_1)\\GameStage_1(GoalPost).obj");				// ゴールポストモデル
	CResourceManager::Load<CModel>("GoalBlock",			 "Field\\GameStage(Worlds_1)\\GameStage_1(GoalBlock).obj");				// ゴールブロックモデル
	CResourceManager::Load<CModel>("Grass",				 "Field\\GameStage(Worlds_1)\\GameStage_1(grass).obj");					// 草モデル
	CResourceManager::Load<CModel>("Mushroom",			 "Field\\GameStage(Worlds_1)\\GameStage_1(mushroom).obj");				// キノコモデル
	CResourceManager::Load<CModel>("RockShrub",			 "Field\\GameStage(Worlds_1)\\GameStage_1(rock&shrub).obj");			// 岩と低木モデル
	CResourceManager::Load<CModel>("SkyIsland",			 "Field\\GameStage(Worlds_1)\\GameStage_1(skyisland).obj");				// 空島モデル
	CResourceManager::Load<CModel>("Tree",				 "Field\\GameStage(Worlds_1)\\GameStage_1(Tree).obj");					// 木モデル
	CResourceManager::Load<CModel>("Branch",			 "Field\\GameStage(Worlds_1)\\GameStage_1(Branch).obj");				// 切り株と木の枝モデル
	CResourceManager::Load<CModel>("Arrowsign",			 "Field\\GameStage(Worlds_1)\\GameStage_1(arrowsign).obj");				// 矢印看板モデル

	
	// ステージギミック関連
	CResourceManager::Load<CModel>("Rotationg",				"Field\\GameStage(Worlds_1)\\GameStage_1(RotationgObject).obj");	// 回転する床のモデル
	CResourceManager::Load<CModel>("RotationgCol",			"Field\\GameStage(Worlds_1)\\GameStage_1(RotationgObjectCol).obj");	// 回転する床のコライダー
	CResourceManager::Load<CModel>("Signboard",				"Field\\Object\\signboard.obj");									// 看板オブジェクト(ジャンプヒント)
	CResourceManager::Load<CModel>("Number0",				"Field\\Object\\number0.obj");										// 零番目の床
	CResourceManager::Load<CModel>("Number1",				"Field\\Object\\number1.obj");										// 一番目の床ブロック
	CResourceManager::Load<CModel>("Number2",				"Field\\Object\\number2.obj");										// 二番目の床ブロック
	CResourceManager::Load<CModel>("Number3",				"Field\\Object\\number3.obj");										// 三番目の床ブロック
	CResourceManager::Load<CModel>("FieldCube",				"Field\\Object\\cube.obj");											// 初期の四角のモデル
	CResourceManager::Load<CModel>("BlueMedal",				"Field\\Object\\Bluemedal.obj");									// ブルーメダルモデル
	CResourceManager::Load<CModel>("RotateFloor",			"Field\\Gimmick\\RotateFloor.obj");									// 回転する床
	CResourceManager::Load<CModel>("RotateFloorFrontCol",	"Field\\Gimmick\\RotateFloorFrontCol.obj");							// 回転する床の前コライダー
	CResourceManager::Load<CModel>("RotateFloorBackCol",	"Field\\Gimmick\\RotateFloorBackCol.obj");							// 回転する床の後ろコライダー
	CResourceManager::Load<CModel>("FlamethrowerModel",		"Field\\Gimmick\\Flamethrower(foundation).obj");					// 火炎放射器(土台)
	CResourceManager::Load<CModel>("FlamethrowerTank",		"Field\\Gimmick\\Flamethrower(tank).obj");							// 火炎放射器(タンク)
	CResourceManager::Load<CModel>("FlamethrowerCol",		"Field\\Gimmick\\Flamethrower(WallCol).obj");						// 火炎放射器(コライダー)
	CResourceManager::Load<CModel>("SavePoint",				"Field\\Gimmick\\SavePoint.obj");									// セーブポイントモデル
	CResourceManager::Load<CModel>("TreasureChest",			"Field\\Gimmick\\TreasureChest.obj");								// 宝箱
	CResourceManager::Load<CModel>("TreasureChestTwo",		"Field\\Gimmick\\TreasureChestTwo.obj");							// 宝箱(蓋)
	CResourceManager::Load<CModel>("TreasureChestCol",		"Field\\Gimmick\\TreasureChest(FloorCol).obj");						// 宝箱(蓋コライダー)
	CResourceManager::Load<CModel>("TreasureChestWallCol",	"Field\\Gimmick\\TreasureChest(WallCol).obj");						// 宝箱(壁コライダー)


	CResourceManager::Load<CModel>("HatenaBlock",			 "Field\\Object\\hatena.obj");						// ハテナブロック(アイテム保有)
	CResourceManager::Load<CModel>("HatenaBlockAfter",		 "Field\\Object\\UsedHatenaBlock.obj");				// ハテナブロック(アイテム不保有)
	CResourceManager::Load<CModel>("RengaBlock",			 "Field\\Object\\RengaBlock.obj");					// レンガブロック
	
	CResourceManager::Load<CModel>("Heart",					"Item\\StatusItem\\Heart.obj");				// 回復オブジェクト
	CResourceManager::Load<CModel>("Star",					"Item\\StatusItem\\Star.obj");				// 無敵オブジェクト
	CResourceManager::Load<CModel>("Medal",					"Item\\StatusItem\\Medal.obj");				// 得点オブジェクト
	CResourceManager::Load<CModel>("Healing",				"Item\\StatusItem\\HealingItem.obj");		// 回復薬オブジェクト
	CResourceManager::Load<CModel>("AttackPotion",			"Item\\StatusItem\\AttackPotion.obj");		// 攻撃力アップモデル

	// キャラクター関連
	//CResourceManager::Load<CModelX>("Vanguard", "Character\\Vanguard\\VanguardModel.x");										// ヴァンガード

	// 背景色設定
	System::SetClearColor(0.1960784f, 0.6f, 0.8f, 1.0f);

	// フィールド
	mpField_Worlds_1 = new CField_Worlds_1();
	mpField_Worlds_1->Scale(8.0f, 8.0f, 8.0f);
	AddTask(mpField_Worlds_1);
	// 落下コライダー
	mpFallCol = new CField_Worlds_1_FallCol();
	mpFallCol->Scale(8.0f, 8.0f, 8.0f);
	AddTask(mpFallCol);

	/////////////////////////////////////////////////////////////////////////////////////

	// ステージギミック

	// 登れる金網を作成
	CWireMeshClimbWall* wiremeshWall = new CWireMeshClimbWall
	(
		"WireMesh", "WireMeshTopCol",
		CVector(0.0f, 14.5f, 0.0f),	// 上方向の移動
		CVector(0.0f, 0.0f, 10.0f)	// 正面方向の移動
	);
	wiremeshWall->Scale(8.0f, 8.0f, 8.0f);
	AddTask(wiremeshWall);

	// 動く登れる金網を作成
	CWireMeshMoveClimbWall* wiremeshmoveWall = new CWireMeshMoveClimbWall
	(
		"WireMeshMove", "WireMeshMoveTopCol",
		CVector(0.0f, 14.5f, 0.0f),	// 上方向の移動
		CVector(0.0f, 0.0f, 10.0f),	// 正面方向の移動
		CVector(-0.5f,0.3f,0.0f),
		CVector(40.0f,0.0f,0.0f),
		10.0f
	);
	wiremeshmoveWall->Scale(8.0f, 8.0f, 8.0f);
	AddTask(wiremeshmoveWall);

	//// ずっと回転するモデル
	//CRotationg* rotationg = new CRotationg
	//(
	//	CVector(804.0f, 212.0f, -182.0f),
	//	CVector(5.0f, 5.0f, 5.0f),
	//	1.0f
	//);
	//AddTask(rotationg);

	//// 火炎放射器モデル
	//// 正面方向
	//CFixedFlamethrower* flamethrower1 = new CFixedFlamethrower
	//(
	//	CVector(810.0f, 125.0f, -384.0f),
	//	CVector(2.0f, 2.0f, 2.0f),
	//	CVector(0.0f, 0.0f, 0.0f)
	//);
	//AddTask(flamethrower1);

	//// 火炎放射器モデル
	//// 右方向
	//CFixedFlamethrower* flamethrower2 = new CFixedFlamethrower
	//(
	//	CVector(1115.0f, 213.0f, -447.0f),
	//	CVector(1.0f, 1.0f, 1.0f),
	//	CVector(0.0f, 0.0f, 0.0f)
	//);
	//flamethrower2->Rotate(-90.0f, 0.0f, -90.0f);
	//AddTask(flamethrower2);

	//// ジャンプオブジェクト
	//CJumpingObject* jumping1 = new CJumpingObject
	//(
	//	CVector(1183.0f, 250.0f, -350.0f),
	//	CVector(0.5f, 0.5f, 0.5f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(jumping1);

	//// ジャンプオブジェクト
	//CJumpingObject* jumping2 = new CJumpingObject
	//(
	//	CVector(1244.0f, 285.0f, -211.0f),
	//	CVector(0.5f, 0.5f, 0.5f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(jumping2);

	// 回数オブジェクト(一回)
	CNumberFloorOnce* numberfloor1 = new CNumberFloorOnce
	(
		CVector(-9.0f, 323.0f, -1273.0f),
		CVector(4.0f, 3.0f, 4.0f),
		CVector(0.0f, -90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(numberfloor1);


	// 回転する床ギミック(時間)
	CRotateFloorTimeGimmick* rotatetimegimmick = new CRotateFloorTimeGimmick(
		CVector(190.0f, 123.0f, -110.0f),
		CVector(4.5f, 4.5f, 6.5f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotatetimegimmick);

	//// 回転する床ギミック(ジャンプ)
	//CRotateFloorGimmick* rotategimmick = new CRotateFloorGimmick(
	//	CVector(1500.0f, 360.0f, -209.0f),
	//	CVector(3.3f, 3.3f, 3.3f),
	//	CVector(0.0f, 90.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(rotategimmick);

	//// 回転する床ギミック(ジャンプ)
	//CRotateFloorGimmick* rotategimmick2 = new CRotateFloorGimmick(
	//	CVector(1560.0f, 370.0f, -209.0f),
	//	CVector(3.3f, 3.3f, 3.3f),
	//	CVector(0.0f, 90.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(rotategimmick2);

	// セーブポイント
	CSavePoint* savepoint = new CSavePoint
	(
		CVector(-9.0f, 320.0f, -1173.0f),
		CVector(8.0f, 8.0f, 8.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint);


	/////////////////////////////////////////////////////////////////////////////////////

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

	/////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////

	// 438,358,-1221

	// 宝箱
	CTreasureChest* treasure1 = new CTreasureChest
	(
		CVector(438.0f, 350.0f, -1221.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure1);
	// 宝箱蓋
	CTreasureChestTwo* treasureTwo1 = new CTreasureChestTwo
	(
		CVector(438.0f, 354.8f, -1221.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo1);

	// 宝箱
	CTreasureChest* treasure2 = new CTreasureChest
	(
		CVector(-207.0f, 194.0f, -454.0f),
		CVector(6.0f, 6.0f, 6.0f),
		CVector(0.0f, -90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure2);
	// 宝箱蓋
	CTreasureChestTwo* treasureTwo2 = new CTreasureChestTwo
	(
		CVector(-207, 197.8f, -454.0f),
		CVector(6.0f, 6.0f, 6.0f),
		CVector(0.0f, -90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo2);


	// レンガブロック
	CRengaBlock* hatena = new CRengaBlock(
		CVector(-9.0f, 322.0f, -1243.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena);

	// レンガブロック
	CRengaBlock* hatena1 = new CRengaBlock(
		CVector(-19.0f, 322.0f, -1243.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena1);

	// レンガブロック
	CRengaBlock* hatena2 = new CRengaBlock(
		CVector(9.0f, 322.0f, -1243.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena2);

	// レンガブロック
	CRengaBlock* hatena3 = new CRengaBlock(
		CVector(19.0f, 322.0f, -1243.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena3);

	/////////////////////////////////////////////////////////////////////////////////////

	// キャラクター

	//// ヴァンガード
	//CVanguard* van = new CVanguard();
	//CVanguard* vanPos = CVanguard::Instance();
	//van->Scale(1.4f, 1.4f, 1.4f);
	//van->Position(496.0f, 335.0f, -167.0f);
	//AddTask(van);
	
	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(190.0f, 125.0f, 269.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 180.0f, 0.0f);
	}
	// カメラの位置と向きを設定
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 30.0f, -100.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt(
		camPos,
		playerPos,
		CVector::up
	);
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
