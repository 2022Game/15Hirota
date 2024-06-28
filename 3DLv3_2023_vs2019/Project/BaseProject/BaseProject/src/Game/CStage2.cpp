#include "CStage2.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CGoalObject.h"
#include "CHopsAndHoopsField.h"
#include "CStageSky.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CJumpingKinoko.h"
#include "CJumpingKinokoLeftRight.h"
#include "CJumpingKinokoUpDown.h"
#include "CJumpingKinokoTurnRight.h"
#include "CJumpingKinokoTurnLeft.h"
#include "CHopsAndHoopsFallCol.h"
#include "CSavePoint1.h"
#include "CSavePoint2.h"
#include "CRingBeamer.h"
#include "CElectricLaser.h"
#include "CHatenaBlock.h"
#include "CTreasureChest.h"
#include "CMetalLadder.h"
#include "CRengaBlock.h"
#include "CPropeller.h"
#include "CMeat1Event.h"
#include "CJumpingKinokoHigh.h"

// コンストラクタ
CStage2::CStage2()
{
	mStageNo = 2;
}

// デストラクタ
CStage2::~CStage2()
{

}

// ステージ読み込み
void CStage2::Load()
{
	// ステージの空
	CResourceManager::Load<CModel>("StageSky",				"Field\\StageSky\\Sky(Sphere).obj");
	// ステージモデル
	CResourceManager::Load<CModel>("HopsAndHoops(Base)",	"Field\\HopsAndHoops\\Stage2(Base).obj");
	// ステージ床コライダー
	CResourceManager::Load<CModel>("HopsAndHoops(Col)",		"Field\\HopsAndHoops\\Stage2(FloorCol).obj");
	// ステージ床コライダー
	CResourceManager::Load<CModel>("HopsAndHoops(FallCol)", "Field\\HopsAndHoops\\Stage2(FallCol).obj");
	// セーブポイントモデル
	CResourceManager::Load<CModel>("SavePoint",				"Field\\Gimmick\\SavePoint.obj");
	// ゴールポストモデル							    
	CResourceManager::Load<CModel>("GoalPost",				"Field\\Object\\GoalPost.obj");
	// ゴールブロックモデル							   
	CResourceManager::Load<CModel>("GoalCube",				"Field\\Object\\GoalCube.obj");
	// 跳ねるキノコモデル							    
	CResourceManager::Load<CModel>("JumpingKinoko",			"Field\\Gimmick\\Jump\\JumpingKinoko(Base).obj");
	// 跳ねるキノコモデル2						    
	CResourceManager::Load<CModel>("JumpingKinoko2Color",	"Field\\Gimmick\\Jump\\JumpingKinoko(Base_2Color).obj");
	// 跳ねるキノコモデル3						    
	CResourceManager::Load<CModel>("JumpingKinoko3Color",	"Field\\Gimmick\\Jump\\JumpingKinoko(Base_3Color).obj");
	// 跳ねるキノココライダー								 
	CResourceManager::Load<CModel>("JumpingKinokoCol",		"Field\\Gimmick\\Jump\\JumpingKinoko(Col).obj");
	// 超ジャンプキノコモデル
	CResourceManager::Load<CModel>("HighKinoko",			"Field\\Gimmick\\Jump\\HighJumpKinoko.obj");
	// 超ジャンプキノココライダー
	CResourceManager::Load<CModel>("JumpingKinokoCol",		"Field\\Gimmick\\Jump\\HighJumpKinokoCol.obj");
	// リングビーマモデル(上)								  
	CResourceManager::Load<CModel>("RingBeamerUP",			"Effect\\BeamObj(Upper).obj");
	// リングビーマモデル(下)								  
	CResourceManager::Load<CModel>("RingBeamerLO",			"Effect\\BeamObj(Lower).obj");
	// ビリビリエフェクト							    
	CResourceManager::Load<CModel>("Biribiri",				"Effect\\BhimaEffect.obj");
	// リングビーマモデル(コライダー)						  
	CResourceManager::Load<CModel>("BiribiriCol",			"Effect\\BhimaEffect(Col).obj");
	// リングビーマモデル(コライダー)						  
	CResourceManager::Load<CTexture>("LightningBolt",		"Effect\\lightning_bolt.png");
	// ハテナブロック(アイテム保有)
	CResourceManager::Load<CModel>("HatenaBlock",			"Field\\Object\\hatena.obj");
	// ハテナブロック(アイテム不保有)
	CResourceManager::Load<CModel>("HatenaBlockAfter",		"Field\\Object\\UsedHatenaBlock.obj");
	// レンガブロック
	CResourceManager::Load<CModel>("RengaBlock",			"Field\\Object\\RengaBlock.obj");
	// 宝箱
	CResourceManager::Load<CModel>("TreasureChest",			"Field\\Gimmick\\Chest\\TreasureChest.obj");
	// 宝箱(蓋)
	CResourceManager::Load<CModel>("TreasureChestTwo",		"Field\\Gimmick\\Chest\\TreasureChestTwo.obj");
	// 宝箱(蓋コライダー)
	CResourceManager::Load<CModel>("TreasureChestCol",		"Field\\Gimmick\\Chest\\TreasureChest(FloorCol).obj");
	// 宝箱(壁コライダー)
	CResourceManager::Load<CModel>("TreasureChestWallCol",	"Field\\Gimmick\\Chest\\TreasureChest(WallCol).obj");
	// プロペラ
	CResourceManager::Load<CModel>("Propeller",				"Field\\Gimmick\\propeller.obj");
	// プロペラ(Col)
	CResourceManager::Load<CModel>("PropellerWallCol",		"Field\\Gimmick\\propeller(Col).obj");

	// 金属の梯子オブジェクト
	CResourceManager::Load<CModel>("Metalladder",			"Field\\HopsAndHoops\\Metalladder(Base).obj");
	// 金属の梯子オブジェクト(Col)
	CResourceManager::Load<CModel>("MetalladderCol",		"Field\\HopsAndHoops\\Metalladder(Col).obj");
	// 金属の梯子オブジェクト(TopCol)
	CResourceManager::Load<CModel>("MetalladderTopCol",		"Field\\HopsAndHoops\\Metalladder(TopCol).obj");

	// 肉モデル
	CResourceManager::Load<CModel>("Meat",			"Item\\StageItem\\niku.obj");
	// 回復薬オブジェクト
	CResourceManager::Load<CModel>("Healing",		"Item\\StatusItem\\HealingItem.obj");
	// 回復オブジェクト
	CResourceManager::Load<CModel>("Heart",			"Item\\StatusItem\\Heart.obj");
	// 無敵オブジェクト
	CResourceManager::Load<CModel>("Star",			"Item\\StatusItem\\Star.obj");
	// 攻撃力アップモデル
	CResourceManager::Load<CModel>("AttackPotion",	"Item\\StatusItem\\AttackPotion.obj");

	// エフェクト
	CResourceManager::Load<CModel>("CircleEffect1",			"Effect\\CharacterEffect\\CharaEffectCircle.obj");
	CResourceManager::Load<CModel>("CircleEffect2",			"Effect\\CharacterEffect\\CharaEffectCircle(Widthver).obj");
	// キャラクターエフェクト
	CResourceManager::Load<CModel>("CharEffect",			"Effect\\CharacterEffect\\CharacterEffect(Up).obj");
	// キャラクターエフェクト(ライン)
	CResourceManager::Load<CModel>("LineEffect",			"Effect\\CharacterEffect\\CharacterEffect(Line).obj");

	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	CHopsAndHoopsField* field = new CHopsAndHoopsField();
	field->Position(0.0f, 0.0f, 0.0f);
	field->Scale(4.0f, 4.0f, 4.0f);
	field->Rotate(0.0f, 180.0f, 0.0f);
	AddTask(field);
	// 空
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);
	// 落下コライダー
	mpHopsAndHoopsFallCol = new CHopsAndHoopsFallCol();
	mpHopsAndHoopsFallCol->Scale(10.0f, 3.0f, 10.0f);
	AddTask(mpHopsAndHoopsFallCol);

	// セーブポイント1
	CSavePoint1* savepoint1 = new CSavePoint1
	(
		CVector(0.0f, 0.0f, 480.0f),
		CVector(7.0f, 7.0f, 7.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint1);
	// セーブポイント2
	CSavePoint2* savepoint2 = new CSavePoint2
	(
		CVector(0.0f, 53.0f, 994.0f),
		CVector(7.0f, 7.0f, 7.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint2->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint2);

	// ゴールポスト
	CGoalObject* goal = new CGoalObject
	(
		CVector(0.0f, 0.0f, 1520.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(goal);

	// 動かないキノコ　
	// オブジェクトを配置するループ
	for (int i = 0; i < 13; ++i) {

		// X軸の位置を設定
		float xPos = 0.0f;
		if (i == 3) xPos = -100.0f;
		if (i == 4) xPos = -210.0f;
		if (i == 5) xPos = -210.0f;
		if (i == 6) xPos = -265.0f;
		if (i == 7) xPos = 0.0f;
		if (i == 8) xPos = 0.0f;
		if (i == 9) xPos = 0.0f;
		if (i == 10) xPos = 0.0f;
		if (i == 11) xPos = 160.0f;
		if (i == 12) xPos = 160.0f;

		// Y軸の位置を設定
		float yPos = 0.0f;
		if (i == 9) yPos = 55.0f;
		if (i == 10) yPos = 55.0f;
		if (i == 11) yPos = 0.0f;
		if (i == 12) yPos = 0.0f;

		// Z軸の位置を設定
		float zPos = i * 55.0f;
		if (i == 0) zPos = 144.0f;
		if (i == 1) zPos = 199.0f;
		if (i == 2) zPos = 254.0f;
		if (i == 3) zPos = 480.0f;
		if (i == 4) zPos = 450.0f;
		if (i == 5) zPos = 510.0f;
		if (i == 6) zPos = 480.0f;
		if (i == 7) zPos = 570.0f;
		if (i == 8) zPos = 680.0f;
		if (i == 9) zPos = 1050.0f;
		if (i == 10) zPos = 1105.0f;
		if (i == 11) zPos = 1235.0f;
		if (i == 12) zPos = 1290.0f;

		// X軸のスケール値を設定
		float xScale = 1.0f;
		if (i == 8) xScale = 2.0f;

		// Z軸のスケール値を設定
		float zScale = 1.0f;
		if (i == 8) zScale = 2.0f;
	
		// オブジェクトを作成してタスクに追加
		CJumpingKinoko* jumpkinoko = new CJumpingKinoko
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 1.0f, zScale),
			CVector(0.0f, 90.0f, 0.0f)
		);

		AddTask(jumpkinoko); // タスクに追加
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// 動くキノコ(左右)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight1 = new CJumpingKinokoLeftRight
	(
		CVector(0.0f, 0.0f, 309.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(40.0f, 0.0f, 0.0f),
		10.0f
	);
	AddTask(jumpkinokoLeftRight1);
	// 動くキノコ(左右)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight2 = new CJumpingKinokoLeftRight
	(
		CVector(-155.0f, 0.0f, 480.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.0f, 0.0f, 50.0f),
		10.0f
	);
	AddTask(jumpkinokoLeftRight2);
	// 動くキノコ(左右)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight3 = new CJumpingKinokoLeftRight
	(
		CVector(-360.0f, 0.0f, 480.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(50.0f, 0.0f, 0.0f),
		13.0f
	);
	AddTask(jumpkinokoLeftRight3);
	// 動くキノコ(左右)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight4 = new CJumpingKinokoLeftRight
	(
		CVector(-60.0f, 0.0f, 625.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(30.0f, 0.0f, 0.0f),
		5.0f
	);
	AddTask(jumpkinokoLeftRight4);
	// 動くキノコ(左右)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight5 = new CJumpingKinokoLeftRight
	(
		CVector(60.0f, 0.0f, 625.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(-30.0f, 0.0f, 0.0f),
		5.0f
	);
	AddTask(jumpkinokoLeftRight5);
	/////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
	// 動くキノコ(上下)
	CJumpingKinokoUpDown* jumpkinokoUpDown1 = new CJumpingKinokoUpDown
	(
		CVector(0.0f, 0.0f, 364.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.0f, 40.0f, 0.0f),
		10.0f
	);
	AddTask(jumpkinokoUpDown1);
	// 動くキノコ(上下)
	CJumpingKinokoUpDown* jumpkinokoUpDown2 = new CJumpingKinokoUpDown
	(
		CVector(120.0f, 30.0f, 1180.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(40.0f, -30.0f, 0.0f),
		10.0f
	);
	AddTask(jumpkinokoUpDown2);
	/////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
	// 動くキノコ(右円回転)
	CJumpingKinokoTurnRight* rotatekinoko1 = new CJumpingKinokoTurnRight
	(
		CVector(0.0f, 55.0f, 1180.0f),
		CVector(1.3f, 1.0f, 1.3f),
		CVector(0.0f, 0.0f, 0.0f),
		30.0f, 30.0f, 80.0f,
		true
	);
	AddTask(rotatekinoko1);
	//////////////////////////////////////////////////////////////////////////////////////

	// リングビーマ1
	CRingBeamerUpper* beamerUp1 = new CRingBeamerUpper
	(
		CVector(-55.0f, 8.0f, 254.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp1);
	// リングビーマ1
	CRingBeamerLower* beamerLow1 = new CRingBeamerLower
	(
		CVector(-55.0f, 7.5f, 254.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow1);

	// リングビーマ2
	CRingBeamerUpper* beamerUp2 = new CRingBeamerUpper
	(
		CVector(-210.0f, 8.0f, 390.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp2);
	// リングビーマ2
	CRingBeamerLower* beamerLow2 = new CRingBeamerLower
	(
		CVector(-210.0f, 7.5f, 390.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow2);

	// リングビーマ3
	CRingBeamerUpper* beamerUp3 = new CRingBeamerUpper
	(
		CVector(-210.0f, 8.0f, 570.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp3);
	// リングビーマ3
	CRingBeamerLower* beamerLow3 = new CRingBeamerLower
	(
		CVector(-210.0f, 7.5f, 570.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow3);

	// 横状の電流1
	CElectricLaser* laser1 = new CElectricLaser
	(
		CVector(0.0f, 20.0f, 810.0f),
		CVector(0.0f, 40.0f, 0.0f),
		2.0f,
		CVector(-75.0f, 5.0f, 0.0f),
		CVector(75.0f, 5.0f, 0.0f),
		CVector(-75.0f, 5.0f, 0.0f),
		CVector(75.0f, 5.0f, 0.0f)
	);
	AddTask(laser1);
	// 横状の電流2
	CElectricLaser* laser2 = new CElectricLaser
	(
		CVector(0.0f, 50.0f, 810.0f),
		CVector(0.0f, -40.0f, 0.0f),
		2.0f,
		CVector(-75.0f, 5.0f, 0.0f),
		CVector(75.0f, 5.0f, 0.0f),
		CVector(-75.0f, 5.0f, 0.0f),
		CVector(75.0f, 5.0f, 0.0f)
	);
	AddTask(laser2);

	// 横状の電流3
	CElectricLaser* laser3 = new CElectricLaser
	(
		CVector(0.0f, 50.0f, 935.0f),
		CVector(0.0f, 50.0f, 0.0f),
		2.0f,
		CVector(-75.0f, 0.0f, 0.0f),
		CVector(75.0f, 0.0f, 0.0f),
		CVector(-75.0f, 0.0f, 0.0f),
		CVector(75.0f, 0.0f, 0.0f)
	);
	AddTask(laser3);
	// 横状の電流4
	CElectricLaser* laser4 = new CElectricLaser
	(
		CVector(0.0f, 0.0f, 935.0f),
		CVector(0.0f, -50.0f, 0.0f),
		2.0f,
		CVector(-75.0f, 0.0f, 0.0f),
		CVector(75.0f, 0.0f, 0.0f),
		CVector(-75.0f, 0.0f, 0.0f),
		CVector(75.0f, 0.0f, 0.0f)
	);
	AddTask(laser4);

	// 横状の電流5
	CElectricLaser* laser5 = new CElectricLaser
	(
		CVector(-340.0f, 15.0f, 480.0f),
		CVector(0.0f, 10.0f, 0.0f),
		3.0f,
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f),
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f)
	);
	AddTask(laser5);

	// 横状の電流6
	CElectricLaser* laser6 = new CElectricLaser
	(
		CVector(-450.0f, 10.0f, 480.0f),
		CVector(0.0f, 0.0f, 0.0f),
		0.1f,
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f),
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f)
	);
	AddTask(laser6);

	// 横状の電流7
	CElectricLaser* laser7 = new CElectricLaser
	(
		CVector(-450.0f, 30.0f, 480.0f),
		CVector(0.0f, 0.0f, 0.0f),
		0.1f,
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f),
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f)
	);
	AddTask(laser7);

	// 横状の電流
	CElectricLaser* laser8 = new CElectricLaser
	(
		CVector(0.0f, 0.0f, 935.0f),
		CVector(40.0f, 0.0f, 0.0f),
		2.0f,
		CVector(0.0f, -75.0f, 0.0f),
		CVector(0.0f, 75.0f, 0.0f),
		CVector(0.0f, -75.0f, 0.0f),
		CVector(0.0f, 75.0f, 0.0f)
	);
	AddTask(laser8);
	// 横状の電流
	CElectricLaser* laser9 = new CElectricLaser
	(
		CVector(0.0f, 0.0f, 935.0f),
		CVector(-40.0f, 0.0f, 0.0f),
		2.0f,
		CVector(0.0f, -75.0f, 0.0f),
		CVector(0.0f, 75.0f, 0.0f),
		CVector(0.0f, -75.0f, 0.0f),
		CVector(0.0f, 75.0f, 0.0f)
	);
	AddTask(laser9);

	// レンガブロック1
	CRengaBlock* renga1 = new CRengaBlock
	(
		CVector(0.0f, 1.0f, 10.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga1);

	// プロペラ
	CPropeller* propeller = new CPropeller
	(
		CVector(0.0f, 30.0f, 950.0f),
		CVector(1.0f, 1.0f, 1.0f),
		0.5f
	);
	AddTask(propeller);

	// 宝箱1
	CTreasureChest* treasure1 = new CTreasureChest
	(
		CVector(0.0f, 0.0f, 60.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure1);
	// 宝箱蓋1
	CTreasureChestTwo* treasureTwo1 = new CTreasureChestTwo
	(
		CVector(0.0f, 3.8f, 60.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo1);

	// 宝箱2
	CTreasureChest* treasure2 = new CTreasureChest
	(
		CVector(-50.0f, 56.5f, 994.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 180.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure2);
	// 宝箱蓋2
	CTreasureChestTwo* treasureTwo2 = new CTreasureChestTwo
	(
		CVector(-50.0f, 59.5f, 994.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 180.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo2);

	// 登れる金網を作成
	CMetalLadder* metalladder = new CMetalLadder
	(
		"Metalladder", "MetalladderTopCol",
		CVector(0.0f, 15.0f, 0.0f),	// 上方向の移動
		CVector(0.0f, 0.0f, 15.0f)	// 正面方向の移動
	);
	metalladder->Scale(4.0f, 4.0f, 4.0f);
	metalladder->Rotate(0.0f, 180.0f, 0.0f);
	AddTask(metalladder);

	//// 肉オブジェクト /////////////////////////////////////////////////////////////////
	
	// 肉1獲得イベントを生成
	CMeat1Event* mtEvent = new CMeat1Event();
	AddTask(mtEvent);

	CMeat1* meat1 = new CMeat1
	(
		CVector(-483.0f, 10.0f, 483.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	AddTask(meat1);
	meat1->SetMeatNumber(1);
	meat1->SetEvent(mtEvent);
	mtEvent->AddMeat1(meat1);

	// 肉1を取得すると
	// ハイジャンプキノコを作成
	CJumpingKinokoHigh* highkinoko = new CJumpingKinokoHigh
	(
		CVector(-483.0f, 5.0f, 500.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(highkinoko);
	highkinoko->SetEvent(mtEvent);
	mtEvent->SetHighKinoko(highkinoko);

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

	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	// 初期値点 : 0.0f, 20.0f, 50.0f
	// 中間ポイント : 0.0f, 0.0f, 480.0f
	// 中間ポイント2 : 0.0f, 53.0f, 994.0f
	// 肉1の場所 : -483.0f, 10.0f, 483.0f
	CVector playerPos = CVector(0.0f, 53.0f, 994.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 0.0f, 0.0f);//0.0f, 225.0f, 0.0f
	}

	// カメラの位置と向きを設定 -1109.0f, 90.0f, 1200.0f
	// CVector(-757.0f, 90.0f, -958.0f),
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 30.0f, -100.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt(camPos, playerPos, CVector::up);
	mainCamera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	//mainCamera->AddCollider(mpField1->GetWallCol());
}

// ステージ破棄
void CStage2::Unload()
{
	CCamera* mainCamera = CCamera::MainCamera();
	//mainCamera->RemoveCollider(mpField1->GetWallCol());
	// ベースステージ破棄処理
	CStageBase::Unload();
}