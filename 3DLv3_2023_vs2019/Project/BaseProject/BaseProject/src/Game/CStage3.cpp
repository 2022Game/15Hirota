#include "CStage3.h"
#include "CPlayer.h"
#include "CSoldier.h"
#include "CVanguard.h"
#include "CStageSky.h"
#include "CCamera.h"
#include "CStageTime.h"
#include "CGameCamera.h"
#include "CEnemyManager.h"
#include "CPlainsStageField.h"
#include "CPlainsStageFallCol.h"
#include "CWireMeshClimbWall.h"
#include "CWireMeshMoveClimbWall.h"
#include "CRotateFloorGimmickOpposition.h"
#include "CRotateFloorTimeGimmick.h"
#include "CRotateFloorGimmick.h"
#include "CFixedFlamethrower.h"
#include "CNumberFloor3.h"
#include "CJumpingObject.h"
#include "CTreasureChest.h"
#include "CNumberFloor1.h"
#include "CHatenaBlock.h"
#include "CRengaBlock.h"
#include "CBlueMedal.h"
#include "CRotationg.h"
#include "CSavePoint1.h"
#include "CSavePoint2.h"
#include "CSeesaw.h"
#include "CJumpingKinoko.h"
#include "CNeedleUpDown.h"
#include "CNeedleLeftRight.h"
#include "CRingBeamer.h"
#include "CGoalObject.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CInput.h"
#include "CPicoChan.h"

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
	CResourceManager::Load<CModel>("Stage",							"Field\\GameStage(Worlds_3)\\GameStage_1(Stage).obj");
	// ステージ空モデル
	CResourceManager::Load<CModel>("StageSky",						"Field\\GameStage(Worlds_3)\\GameStage_1(StageSky).obj");
	// 床のコライダー
	CResourceManager::Load<CModel>("FloorCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(floorCol).obj");
	// 壁のコライダー
	CResourceManager::Load<CModel>("WallCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(wallCol).obj");
	// 落下判定コライダー
	CResourceManager::Load<CModel>("FallCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(FallCol).obj");
	// 金網モデル
	CResourceManager::Load<CModel>("WireMesh",						"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_Stop).obj");
	// 金網コライダー
	CResourceManager::Load<CModel>("WireMeshCol",					"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_StopCol).obj");
	// 金網頂上コライダー
	CResourceManager::Load<CModel>("WireMeshTopCol",				"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_StopTopCol).obj");
	// 動く金網モデル
	CResourceManager::Load<CModel>("WireMeshMove",					"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_Move).obj");
	// 動く金網コライダー
	CResourceManager::Load<CModel>("WireMeshMoveCol",				"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_MoveCol).obj");
	// 動く金網頂上コライダー
	CResourceManager::Load<CModel>("WireMeshMoveTopCol",			"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_MoveTopCol).obj");
	// 道モデル
	CResourceManager::Load<CModel>("Load",							"Field\\GameStage(Worlds_3)\\GameStage_1(load).obj");
	// 雲モデル
	CResourceManager::Load<CModel>("Cloud",							"Field\\GameStage(Worlds_3)\\GameStage_1(cloud).obj");
	// フェンスモデル
	CResourceManager::Load<CModel>("Fance",							"Field\\GameStage(Worlds_3)\\GameStage_1(fance).obj");
	// 花モデル
	CResourceManager::Load<CModel>("Flowers",						"Field\\GameStage(Worlds_3)\\GameStage_1(flowers).obj");
	//// ゴールポストモデル
	//CResourceManager::Load<CModel>("GoalPost",						"Field\\GameStage(Worlds_3)\\GameStage_1(GoalPost).obj");
	//// ゴールブロックモデル
	//CResourceManager::Load<CModel>("GoalBlock",						"Field\\GameStage(Worlds_3)\\GameStage_1(GoalBlock).obj");
	// 草モデル
	CResourceManager::Load<CModel>("Grass",							"Field\\GameStage(Worlds_3)\\GameStage_1(grass).obj");
	// キノコモデル
	CResourceManager::Load<CModel>("Mushroom",						"Field\\GameStage(Worlds_3)\\GameStage_1(mushroom).obj");
	// 岩と低木モデル
	CResourceManager::Load<CModel>("RockShrub",						"Field\\GameStage(Worlds_3)\\GameStage_1(rock&shrub).obj");
	// 空島モデル
	CResourceManager::Load<CModel>("SkyIsland",						"Field\\GameStage(Worlds_3)\\GameStage_1(skyisland).obj");
	// 木モデル
	CResourceManager::Load<CModel>("Tree",							"Field\\GameStage(Worlds_3)\\GameStage_1(Tree).obj");
	// 切り株と木の枝モデル
	CResourceManager::Load<CModel>("Branch",						"Field\\GameStage(Worlds_3)\\GameStage_1(Branch).obj");
	// 矢印看板モデル
	CResourceManager::Load<CModel>("Arrowsign",						"Field\\GameStage(Worlds_3)\\GameStage_1(arrowsign).obj");


	// ステージギミック関連
	// 回転する床のモデル
	CResourceManager::Load<CModel>("Rotationg",						"Field\\GameStage(Worlds_3)\\GameStage_1(RotationgObject).obj");
	// 回転する床のコライダー
	CResourceManager::Load<CModel>("RotationgCol",					"Field\\GameStage(Worlds_3)\\GameStage_1(RotationgObjectCol).obj");
	// 看板オブジェクト(ジャンプヒント)
	CResourceManager::Load<CModel>("Signboard",						"GameGimmick\\Object\\signboard.obj");
	// 零番目の床
	CResourceManager::Load<CModel>("Number0",						"GameGimmick\\Gimmick\\NumberFloor\\number0.obj");
	// 一番目の床ブロック
	CResourceManager::Load<CModel>("Number1",						"GameGimmick\\Gimmick\\NumberFloor\\number1.obj");
	// 二番目の床ブロック
	CResourceManager::Load<CModel>("Number2",						"GameGimmick\\Gimmick\\NumberFloor\\number2.obj");
	// 三番目の床ブロック
	CResourceManager::Load<CModel>("Number3",						"GameGimmick\\Gimmick\\NumberFloor\\number3.obj");
	// 初期の四角のモデル
	CResourceManager::Load<CModel>("FieldCube",						"GameGimmick\\Object\\cube.obj");
	// ブルーメダルモデル
	CResourceManager::Load<CModel>("BlueMedal",						"Item\\BlueMedal\\Bluemedal.obj");
	// 回転する床
	CResourceManager::Load<CModel>("RotateFloor",					"GameGimmick\\Gimmick\\Rotate\\RotateFloor.obj");
	// 回転する床の前コライダー
	CResourceManager::Load<CModel>("RotateFloorFrontCol",			"GameGimmick\\Gimmick\\Rotate\\RotateFloorFrontCol.obj");
	// 回転する床の後ろコライダー
	CResourceManager::Load<CModel>("RotateFloorBackCol",			"GameGimmick\\Gimmick\\Rotate\\RotateFloorBackCol.obj");
	// 回転する床(反対)
	CResourceManager::Load<CModel>("RotateFloorOpposition",			"GameGimmick\\Gimmick\\Rotate\\RotateFloor(Opposition).obj");
	// 回転する床の前コライダー(反対)
	CResourceManager::Load<CModel>("RotateFloorFrontColOpposition", "GameGimmick\\Gimmick\\Rotate\\RotateFloorFrontCol(Opposition).obj");
	// 回転する床の後ろコライダー(反対)
	CResourceManager::Load<CModel>("RotateFloorBackColOpposition",	"GameGimmick\\Gimmick\\Rotate\\RotateFloorBackCol(Opposition).obj");
	// 火炎放射器(土台)
	CResourceManager::Load<CModel>("FlamethrowerModel",				"GameGimmick\\Gimmick\\Flame\\Flamethrower(foundation).obj");
	// 火炎放射器(タンク)
	CResourceManager::Load<CModel>("FlamethrowerTank",				"GameGimmick\\Gimmick\\Flame\\Flamethrower(tank).obj");
	// 火炎放射器(コライダー)
	CResourceManager::Load<CModel>("FlamethrowerCol",				"GameGimmick\\Gimmick\\Flame\\Flamethrower(WallCol).obj");
	// セーブポイントモデル
	CResourceManager::Load<CModel>("SavePoint",						"GameGimmick\\Gimmick\\SaveFlag\\SavePoint.obj");
	// ゴールポストモデル
	CResourceManager::Load<CModel>("GoalPost",						"GameGimmick\\Gimmick\\Goal\\GoalPost.obj");
	// ゴールブロックモデル
	CResourceManager::Load<CModel>("GoalCube",						"GameGimmick\\Gimmick\\Goal\\GoalCube.obj");
	// 宝箱
	CResourceManager::Load<CModel>("TreasureChest",					"GameGimmick\\Gimmick\\Chest\\TreasureChest.obj");
	// 宝箱(蓋)
	CResourceManager::Load<CModel>("TreasureChestTwo",				"GameGimmick\\Gimmick\\Chest\\TreasureChestTwo.obj");
	// 宝箱(蓋コライダー)
	CResourceManager::Load<CModel>("TreasureChestCol",				"GameGimmick\\Gimmick\\Chest\\TreasureChest(FloorCol).obj");
	// 宝箱(壁コライダー)
	CResourceManager::Load<CModel>("TreasureChestWallCol",			"GameGimmick\\Gimmick\\Chest\\TreasureChest(WallCol).obj");
	// シーソーモデル
	CResourceManager::Load<CModel>("SeesawModel",					"GameGimmick\\Gimmick\\SeesawGimmick\\SeesawModel.obj");
	// シーソーモデル
	CResourceManager::Load<CModel>("SeesawModelCol",				"GameGimmick\\Gimmick\\SeesawGimmick\\SeesawModel(Col).obj");
	// シーソーモデル
	CResourceManager::Load<CModel>("centerCol",						"GameGimmick\\Gimmick\\SeesawGimmick\\SeesawModel(CenterCol).obj");
	// シーソーモデル
	CResourceManager::Load<CModel>("rightCol",						"GameGimmick\\Gimmick\\SeesawGimmick\\SeesawModel(RightCol).obj");
	// シーソーモデル
	CResourceManager::Load<CModel>("leftCol",						"GameGimmick\\Gimmick\\SeesawGimmick\\SeesawModel(LeftCol).obj");
	// 跳ねるキノコモデル
	CResourceManager::Load<CModel>("JumpingKinoko",					"GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Base).obj");
	// 跳ねるキノココライダー
	CResourceManager::Load<CModel>("JumpingKinokoCol",				"GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Col).obj");
	// 針モデル(上下)
	CResourceManager::Load<CModel>("Needle",						"GameGimmick\\Gimmick\\Needle\\NeedleObject(needle).obj");
	// 針モデルコライダー(上下)
	CResourceManager::Load<CModel>("NeedleCol",						"GameGimmick\\Gimmick\\Needle\\NeedleObjectCol.obj");
	// 針ベースモデル(上下)
	CResourceManager::Load<CModel>("NeedleBase",					"GameGimmick\\Gimmick\\Needle\\NeedleObject(base).obj");
	// 針ベースコライダー(上下)
	CResourceManager::Load<CModel>("NeedleBaseCol",					"GameGimmick\\Gimmick\\Needle\\NeedleObjectBaseCol.obj");
	// 針モデル(左右)
	CResourceManager::Load<CModel>("NeedleLeftRight",				"GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(Needle).obj");
	// 針モデルコライダー(左右)
	CResourceManager::Load<CModel>("NeedleColLeftRight",			"GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(NeedleCol).obj");
	// 針ベースモデル(左右)
	CResourceManager::Load<CModel>("NeedleBaseLeftRight",			"GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(Base).obj");
	// 針ベースコライダー(左右)
	CResourceManager::Load<CModel>("NeedleBaseColLeftRight",		"GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(BaseCol).obj");
	// リングビーマモデル(上)
	CResourceManager::Load<CModel>("RingBeamerUP",					"Effect\\BeamObj(Upper).obj");
	// リングビーマモデル(下)
	CResourceManager::Load<CModel>("RingBeamerLO",					"Effect\\BeamObj(Lower).obj");
	// ビリビリエフェクト
	CResourceManager::Load<CModel>("Biribiri",						"Effect\\BhimaEffect.obj");
	// リングビーマモデル(コライダー)
	CResourceManager::Load<CModel>("BiribiriCol",					"Effect\\BhimaEffect(Col).obj");


	// ハテナブロック(アイテム保有)
	CResourceManager::Load<CModel>("HatenaBlock",					"GameGimmick\\Gimmick\\Block\\hatena.obj");
	// ハテナブロック(アイテム不保有)
	CResourceManager::Load<CModel>("HatenaBlockAfter",				"GameGimmick\\Gimmick\\Block\\UsedHatenaBlock.obj");
	// レンガブロック
	CResourceManager::Load<CModel>("RengaBlock",					"GameGimmick\\Gimmick\\Block\\RengaBlock.obj");

	// 回復オブジェクト
	CResourceManager::Load<CModel>("Heart",							"Item\\StatusItem\\Heart.obj");
	// 無敵オブジェクト
	CResourceManager::Load<CModel>("Star",							"Item\\StatusItem\\Star.obj");
	// 得点オブジェクト
	CResourceManager::Load<CModel>("Medal",							"Item\\StatusItem\\Medal.obj");
	// 回復薬オブジェクト
	CResourceManager::Load<CModel>("Healing",						"Item\\StatusItem\\HealingItem.obj");
	// 攻撃力アップモデル
	CResourceManager::Load<CModel>("AttackPotion",					"Item\\StatusItem\\AttackPotion.obj");
	// 肉モデル
	CResourceManager::Load<CModel>("Meat",							"Item\\StageItem\\niku.obj");

	// キャラクター関連
	
	// 弾
	CResourceManager::Load<CModel>("Bullet", "Item\\Bullet1\\Bullet.obj");
	// M1ガーランド(銃)
	CResourceManager::Load<CModel>("Gun_M1G", "Item\\Gun_M1Garand\\Gun_M1Garand.obj");

	// エフェクト関連
	// 弾のエフェクト
	CResourceManager::Load<CTexture>("Laser", "Effect\\laser.png");
	// スラッシュエフェクト
	CResourceManager::Load<CModel>("Slash", "Effect\\slash.obj");
	// キャラクターエフェクト
	CResourceManager::Load<CModel>("CharEffect", "Effect\\CharacterEffect\\CharacterEffect(Up).obj");
	// キャラクターエフェクト(ライン)
	CResourceManager::Load<CModel>("LineEffect", "Effect\\CharacterEffect\\CharacterEffect(Line).obj");

	// Tキーの画像
	CResourceManager::Load<CTexture>("TUI", "UI\\GimmickUI\\T.png");

	// 背景色設定
	System::SetClearColor(0.1960784f, 0.6f, 0.8f, 1.0f);

	CInput::ShowCursor(false);

	//// フィールド関連 /////////////////////////////////////////////////////////////////

	// フィールド
	mpPlainsStageField = new CPlainsStageField();
	mpPlainsStageField->Scale(8.0f, 8.0f, 8.0f);
	AddTask(mpPlainsStageField);
	// 空
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);
	// 落下コライダー
	mpCPlainsStageFallCol = new CPlainsStageFallCol();
	mpCPlainsStageFallCol->Scale(8.0f, 8.0f, 8.0f);
	AddTask(mpCPlainsStageFallCol);

	// セーブポイント
	CSavePoint1* savepoint1 = new CSavePoint1
	(
		CVector(0.0f, 320.0f, -1173.0f),
		CVector(8.0f, 8.0f, 8.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint1);

	// セーブポイント
	CSavePoint2* savepoint2 = new CSavePoint2
	(
		CVector(0.0f, 400.0f, -1890.0f),
		CVector(8.0f, 8.0f, 8.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint2->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint2);

	// ゴールポスト
	CGoalObject* goal = new CGoalObject
	(
		CVector(-367.0f, 395.0f, -2060.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(goal);

	/////////////////////////////////////////////////////////////////////////////////////

	//// ステージオブジェクト関連 ///////////////////////////////////////////////////////
	
	// 登れる壁→跳ねるキノコ→回数オブジェクト→ずっと回転するオブジェクト→ジャンプオブジェクト→
	// 回転床オブジェクト→シーソー→宝箱→レンガブロック→火炎放射器→針オブジェクト→リングビーム

	// 登れる金網を作成
	CWireMeshClimbWall* wiremeshWall = new CWireMeshClimbWall
	(
		"WireMesh", "WireMeshTopCol",
		CVector(0.0f, 14.5f, 0.0f),	// 上方向の移動
		CVector(0.0f, 0.0f, 15.0f)	// 正面方向の移動
	);
	wiremeshWall->Scale(8.0f, 8.0f, 8.0f);
	AddTask(wiremeshWall);

	// 動く登れる金網を作成
	CWireMeshMoveClimbWall* wiremeshmoveWall = new CWireMeshMoveClimbWall
	(
		"WireMeshMove", "WireMeshMoveTopCol",
		CVector(0.0f, 14.5f, 0.0f),	// 上方向の移動
		CVector(0.0f, 0.0f, 15.0f),	// 正面方向の移動
		CVector(-0.5f, 0.3f, 0.0f),
		CVector(40.0f, 0.0f, 0.0f),
		10.0f
	);
	wiremeshmoveWall->Scale(8.0f, 8.0f, 8.0f);
	AddTask(wiremeshmoveWall);

	// 跳ねるキノコ
	CJumpingKinoko* jumping1 = new CJumpingKinoko
	(
		CVector(-148.0f, 247.0f, -1059.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(jumping1);

	// 跳ねるキノコ
	CJumpingKinoko* jumping2 = new CJumpingKinoko
	(
		CVector(0.0f, 295.0f, -1110.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(jumping2);

	// 回数オブジェクト(3回)
	CNumberFloor3* numberfloor3 = new CNumberFloor3
	(
		CVector(0.0f, 323.0f, -1273.0f),
		CVector(4.0f, 1.0f, 4.0f),
		CVector(0.0f, -90.0f, 0.0f)
	);
	AddTask(numberfloor3);

	//// 回数オブジェクト(3回)
	//CNumberFloor1* numberfloor2 = new CNumberFloor1
	//(
	//	CVector(0.0f, 366.0f, -1440.0f),
	//	CVector(4.0f, 1.0f, 4.0f),
	//	CVector(0.0f, -90.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(numberfloor2);

	//// 回数オブジェクト(3回)
	//CNumberFloor1* numberfloor3 = new CNumberFloor1
	//(
	//	CVector(0.0f, 366.0f, -1750.0f),
	//	CVector(4.0f, 1.0f, 4.0f),
	//	CVector(0.0f, -90.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(numberfloor3);

	// ずっと回転するモデル1
	CRotationg* rotationg = new CRotationg
	(
		CVector(12.3f, 212.0f, -689.0f),
		CVector(5.0f, 5.0f, 5.0f),
		1.0f
	);
	AddTask(rotationg);

	// ずっと回転するモデル2
	CRotationg* rotationg2 = new CRotationg
	(
		CVector(0.0f, 366.0f, -1590.0f),
		CVector(6.0f, 5.0f, 6.0f),
		0.5f
	);
	rotationg2->SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
	AddTask(rotationg2);

	////////////////////////////////////////////////////////////////////////////////////////
	// 回転する床ギミック(時間)
	CRotateFloorTimeGimmick* rotatetimegimmick = new CRotateFloorTimeGimmick(
		CVector(190.0f, 123.0f, -110.0f),
		CVector(4.5f, 4.5f, 6.5f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotatetimegimmick);

	// 回転する床ギミック(ジャンプ)
	// 宝箱への道のりの途中
	CRotateFloorGimmick* rotategimmick1 = new CRotateFloorGimmick(
		CVector(179.0f, 320.0f, -1212.0f),
		CVector(3.3f, 3.3f, 3.3f),
		CVector(0.0f, 90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotategimmick1);

	// 回転する床ギミック(ジャンプ)
	// ゴールまでの道のりの途中　左
	CRotateFloorGimmickOpposition* rotategimmick2 = new CRotateFloorGimmickOpposition(
		CVector(-53.0f, 335.0f, -1335.0f),
		CVector(4.3f, 4.3f, 4.3f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotategimmick2);

	// 回転する床ギミック(ジャンプ)
	// ゴールまでの道のりの途中　右
	CRotateFloorGimmick* rotategimmick3 = new CRotateFloorGimmick(
		CVector(53.0f, 335.0f, -1335.0f),
		CVector(4.3f, 4.3f, 4.3f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotategimmick3);

	// 回転する床ギミック(ジャンプ)
	// ゴールまでの道のりの途中　真ん中
	CRotateFloorTimeGimmick* rotategimmick4 = new CRotateFloorTimeGimmick(
		CVector(0.0f, 355.0f, -1388.0f),
		CVector(4.3f, 4.3f, 4.3f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotategimmick4);

	// 回転する床ギミック(ジャンプ)
	// ゴールまでの道のりの途中　真ん中
	CRotateFloorGimmick* rotategimmick5 = new CRotateFloorGimmick(
		CVector(0.0f, 386.0f, -1800.0f),
		CVector(5.3f, 5.3f, 5.3f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotategimmick5);
	////////////////////////////////////////////////////////////////////////////////////////

	//// シーソーモデル
	//CSeesaw* seesaw1 = new CSeesaw
	//(
	//	CVector(190.0f, 135.0f, 90.0f),
	//	CVector(8.5f, 5.5f, 10.5f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(seesaw1);


	//// 回転する床ギミック(ジャンプ)
	//CRotateFloorGimmick* rotategimmick2 = new CRotateFloorGimmick(
	//	CVector(1560.0f, 370.0f, -209.0f),
	//	CVector(3.3f, 3.3f, 3.3f),
	//	CVector(0.0f, 90.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(rotategimmick2);

	//////////////////////////////////////////////////////////
	// 宝箱1
	CTreasureChest* treasure1 = new CTreasureChest
	(
		CVector(438.0f, 350.0f, -1221.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure1);
	// 宝箱蓋1
	CTreasureChestTwo* treasureTwo1 = new CTreasureChestTwo
	(
		CVector(438.0f, 354.8f, -1221.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo1);

	// 宝箱2
	CTreasureChest* treasure2 = new CTreasureChest
	(
		CVector(-207.0f, 194.0f, -454.0f),
		CVector(6.0f, 6.0f, 6.0f),
		CVector(0.0f, -90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure2);
	// 宝箱蓋2
	CTreasureChestTwo* treasureTwo2 = new CTreasureChestTwo
	(
		CVector(-207, 197.8f, -454.0f),
		CVector(6.0f, 6.0f, 6.0f),
		CVector(0.0f, -90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo2);
	//////////////////////////////////////////////////////////

	// レンガブロック1
	CRengaBlock* renga1 = new CRengaBlock
	(
		CVector(-219.0f, 251.0f, -1087.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga1);
	// ハテナブロック1
	CHatenaBlock* hatena1 = new CHatenaBlock
	(
		CVector(-211.0f, 251.0f, -1087.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena1);
	// レンガブロック1
	CRengaBlock* renga2 = new CRengaBlock(
		CVector(-203.0f, 251.0f, -1087.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga2);

	// レンガブロック2
	CRengaBlock* renga3 = new CRengaBlock
	(
		CVector(83.0f, 285.0f, -1060.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga3);
	// ハテナブロック2
	CHatenaBlock* hatena2 = new CHatenaBlock
	(
		CVector(83.0f, 285.0f, -1052.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena2);
	// レンガブロック2
	CRengaBlock* renga4 = new CRengaBlock(
		CVector(83.0f, 285.0f, -1044.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga4);


	// レンガブロック5
	CRengaBlock* renga5 = new CRengaBlock
	(
		CVector(0.0f, 410.0f, -1900.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga5);

	// 針モデル1
	CNeedleUpDown* needle1 = new CNeedleUpDown(
		CVector(-150.0f, 408.0f, -1890.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		1.4f,
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(needle1);
	// 針モデルベース1
	CNeedleUpDownBase* needlebase1 = new CNeedleUpDownBase(
		CVector(-150.0f, 408.0f, -1890.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(needlebase1);

	//// 針モデル1
	//CNeedleLeftRight* needle1 = new CNeedleLeftRight(
	//	CVector(-130.0f, 280.0f, -1080.0f),
	//	CVector(10.0f, 10.0f, 10.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer);
	//AddTask(needle1);
	//// 針モデルベース1
	//CNeedleLeftRightBase* needlebase1 = new CNeedleLeftRightBase(
	//	CVector(-130.0f, 280.0f, -1080.0f),
	//	CVector(10.0f, 10.0f, 10.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer);
	//AddTask(needlebase1);

	// リングビーマ1
	CRingBeamerUpper* beamerUp1 = new CRingBeamerUpper
	(
		CVector(-70.0f, 379.0f, -1440.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp1);
	// リングビーマ1
	CRingBeamerLower* beamerLo1 = new CRingBeamerLower
	(
		CVector(-70.0f, 378.0f, -1440.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLo1);

	// リングビーマ2
	CRingBeamerUpper* beamerUp2 = new CRingBeamerUpper
	(
		CVector(100.0f, 379.0f, -1622.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp2);
	// リングビーマ2
	CRingBeamerLower* beamerLo2 = new CRingBeamerLower
	(
		CVector(100.0f, 378.0f, -1622.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLo2);

	// リングビーマ3
	CRingBeamerUpper* beamerUp3 = new CRingBeamerUpper
	(
		CVector(-100.0f, 379.0f, -1622.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp3);
	// リングビーマ3
	CRingBeamerLower* beamerLo3 = new CRingBeamerLower
	(
		CVector(-100.0f, 378.0f, -1622.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLo3);

	// 火炎放射器モデル
	// 左側
	CFixedFlamethrower* flamethrower1 = new CFixedFlamethrower
	(
		CVector(-258.0f, 173.0f, -990.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, -90.0f, -90.0f)
	);
	AddTask(flamethrower1);

	// 火炎放射器モデル
	// 右側
	CFixedFlamethrower* flamethrower2 = new CFixedFlamethrower
	(
		CVector(-149.0f, 209.0f, -990.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 90.0f)
	);
	AddTask(flamethrower2);

	/////////////////////////////////////////////////////////////////////////////////////

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
	// ソルジャー1
	CSoldier* soldier1 = new CSoldier();
	soldier1->Scale(1.5f, 1.5f, 1.5f);
	soldier1->Position(7.7f, 138.0f, -274.0f);
	soldier1->SetCenterPoint(CVector(7.7f, 130.0f, -274.0f), 40.0f);
	AddTask(soldier1);
	// ソルジャー2
	CSoldier* soldier2 = new CSoldier();
	soldier2->Scale(1.5f, 1.5f, 1.5f);
	soldier2->Position(-173.7f, 138.0f, -652.0f);
	soldier2->SetCenterPoint(CVector(-173.7f, 130.0f, -652.0f), 40.0f);
	AddTask(soldier2);

	// ピコちゃん
	CPicoChan* pico = new CPicoChan();
	pico->Scale(15.5f, 15.5f, 15.5f);
	pico->Position(-187.0f, 130.0f, -903.0f);
	pico->SetCenterPoint(CVector(-187.0f, 130.0f, -903.0f), 30.0f);
	AddTask(pico);


	// ヴァンガード
	CVanguard* van = new CVanguard();
	CVanguard* vanPos = CVanguard::Instance();
	van->Scale(1.4f, 1.4f, 1.4f);
	van->Position(0.0f, 900.0f, -2050.0f);
	AddTask(van);

	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	// 初期値点 : 190.0f, 130.0f.0f, 269.0f
	// 中間地点 : 0.0f, 320.0f, -1050.0f
	// ボス前	: 0.0f, 430.0f, -1890.0f
	// ゴール付近:	-367.0f, 395.0f, -2040.0f
	// 火炎放射器の前 : -207.0f, 126.0f, -912.0f
	CVector playerPos = CVector(190.0f, 140.0f, 269.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 180.0f, 0.0f);
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
	mainCamera->AddCollider(mpPlainsStageField->GetWallCol());

}

// ステージ破棄
void CStage3::Unload()
{
	// カメラから衝突するコライダーを取り除く
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->RemoveCollider(mpPlainsStageField->GetWallCol());
	// ベースステージ破棄処理
	CStageBase::Unload();
}