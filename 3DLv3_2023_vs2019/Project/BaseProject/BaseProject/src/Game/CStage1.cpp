#include "CStage1.h"
#include "COneShotFloorField.h"
#include "CStageSky.h"
#include "CPlayer.h"
#include "CNumberFloor1.h"
#include "CNumberFloor2.h"
#include "CNumberFloor3.h"
#include "CRisingObject.h"
#include "CTreasureChest.h"
#include "CSavePoint1.h"
#include "CFixedFlamethrower.h"
#include "CGoalObject.h"
#include "CBlueMedalEvent.h"
#include "CBlueMedal.h"
#include "CObstacleWall.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CNeedleUpDown.h"
#include "CNeedleLeftRight.h"
#include "CInput.h"
#include "CRotationg.h"

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
	// オブジェクト関連
	// ステージの空
	CResourceManager::Load<CModel>("StageSky", "Field\\StageSky\\Sky(Sphere).obj");
	// 初期の四角のモデル
	CResourceManager::Load<CModel>("FieldCube", "Field\\Object\\cube.obj");
	// 落下判定コライダー
	CResourceManager::Load<CModel>("NumberFallCol", "Field\\FallCol.obj");

	// ギミック関連
	// 回転する床のモデル
	CResourceManager::Load<CModel>("Rotationg", "Field\\Gimmick\\Rotate\\Rotationg.obj");
	// 回転する床のコライダー
	CResourceManager::Load<CModel>("RotationgCol", "Field\\Gimmick\\Rotate\\RotationgCol.obj");
	// 零番目の床
	CResourceManager::Load<CModel>("Number0", "Field\\Object\\number0.obj");
	// 一番目の床ブロック
	CResourceManager::Load<CModel>("Number1", "Field\\Object\\number1.obj");
	// 二番目の床ブロック
	CResourceManager::Load<CModel>("Number2", "Field\\Object\\number2.obj");
	// 三番目の床ブロック
	CResourceManager::Load<CModel>("Number3", "Field\\Object\\number3.obj");
	// 宝箱
	//CResourceManager::Load<CModel>("TreasureChest", "Field\\Gimmick\\TreasureChest.obj");
	// // 宝箱(蓋)
	//CResourceManager::Load<CModel>("TreasureChestTwo", "Field\\Gimmick\\TreasureChestTwo.obj");
	// // 宝箱(蓋コライダー)
	//CResourceManager::Load<CModel>("TreasureChestCol", "Field\\Gimmick\\TreasureChest(FloorCol).obj");
	// // 宝箱(壁コライダー)
	//CResourceManager::Load<CModel>("TreasureChestWallCol", "Field\\Gimmick\\TreasureChest(WallCol).obj");
	// 火炎放射器(土台)
	CResourceManager::Load<CModel>("FlamethrowerModel", "Field\\Gimmick\\Fire\\Flamethrower(foundation).obj");
	// 火炎放射器(タンク)
	CResourceManager::Load<CModel>("FlamethrowerTank", "Field\\Gimmick\\Fire\\Flamethrower(tank).obj");
	// 火炎放射器(コライダー)
	CResourceManager::Load<CModel>("FlamethrowerCol", "Field\\Gimmick\\Fire\\Flamethrower(WallCol).obj");
	// セーブポイントモデル
	CResourceManager::Load<CModel>("SavePoint", "Field\\Gimmick\\SavePoint.obj");
	// ゴールポストモデル
	CResourceManager::Load<CModel>("GoalPost", "Field\\Object\\GoalPost.obj");
	// ゴールブロックモデル
	CResourceManager::Load<CModel>("GoalCube", "Field\\Object\\GoalCube.obj");
	// 針モデル(上下)
	CResourceManager::Load<CModel>("Needle", "Field\\Gimmick\\Needle\\NeedleObject(needle).obj");
	// 針モデルコライダー(上下)
	CResourceManager::Load<CModel>("NeedleCol", "Field\\Gimmick\\Needle\\NeedleObjectCol.obj");
	// 針ベースモデル(上下)
	CResourceManager::Load<CModel>("NeedleBase", "Field\\Gimmick\\Needle\\NeedleObject(base).obj");
	// 針ベースコライダー(上下)
	CResourceManager::Load<CModel>("NeedleBaseCol", "Field\\Gimmick\\Needle\\NeedleObjectBaseCol.obj");
	// 針モデル(左右)
	CResourceManager::Load<CModel>("NeedleLeftRight", "Field\\Gimmick\\Needle\\NeedleObjLeftRight(Needle).obj");
	// 針モデルコライダー(左右)
	CResourceManager::Load<CModel>("NeedleColLeftRight", "Field\\Gimmick\\Needle\\NeedleObjLeftRight(NeedleCol).obj");
	// 針ベースモデル(左右)
	CResourceManager::Load<CModel>("NeedleBaseLeftRight", "Field\\Gimmick\\Needle\\NeedleObjLeftRight(Base).obj");
	// 針ベースコライダー(左右)
	CResourceManager::Load<CModel>("NeedleBaseColLeftRight", "Field\\Gimmick\\Needle\\NeedleObjLeftRight(BaseCol).obj");
	// 肉モデル
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");

	// アイテム関連
	// ブルーメダルモデル
	CResourceManager::Load<CModel>("BlueMedal", "Field\\Object\\Bluemedal.obj");

	// 背景色設定
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	CInput::ShowCursor(false);

	COneShotFloorField* field = new COneShotFloorField();
	field->Scale(1.0f, 1.0f, 1.0f);
	field->Position(0.0f, -200.0f, 0.0f);
	AddTask(field);

	// 空
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);

	// 初期値点
	CRisingObject* rising = new CRisingObject
	(
		CVector(0.0f, 12.0f, -70.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising);


	CNumberFloor1* floor1 = new CNumberFloor1
	(
		CVector(-60.0f, 0.0f, -70.0f),
		CVector(4.0f, 3.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(floor1);

	CNumberFloor2* floor2 = new CNumberFloor2
	(
		CVector(-120.0f, 0.0f, -70.0f),
		CVector(4.0f, 3.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(floor2);

	CNumberFloor3* floor3 = new CNumberFloor3
	(
		CVector(-180.0f, 0.0f, -70.0f),
		CVector(4.0f, 3.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(floor3);

	// ずっと回転するモデル1
	CRotationg* rotationg = new CRotationg
	(
		CVector(60.0f, 12.0f, -70.0f),
		CVector(10.0f, 10.0f, 10.0f),
		1.0f
	);
	AddTask(rotationg);

	// 中間値点
	CRisingObject* rising1 = new CRisingObject
	(
		CVector(0.0f, 12.0f, 325.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising1);

	// ゴール値点
	CRisingObject* rising2 = new CRisingObject
	(
		CVector(0.0f, 12.0f, 670.0f),
		CVector(2.0f, 1.0f, 2.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising2);

	// ゴールポスト0.0f, 10.0f, 720.0f
	CGoalObject* goal = new CGoalObject
	(
		CVector(0.0f, 0.5f, 669.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(goal);

	// オブジェクトを配置するループ
	for (int i = 0; i < 14; ++i) {

		// X軸の位置を設定
		float xPos = 0.0f;
		if (i == 5) xPos = 70.0f;
		if (i == 6) xPos = -70.0f;
		if (i == 7) xPos = 70.0f;
		if (i == 8) xPos = -70.0f;
		if (i == 9) xPos = 70.0f;
		if (i == 10) xPos = -70.0f;
		if (i == 11) xPos = 50.0f;
		if (i == 12) xPos = -50.0f;
		if (i == 13) xPos = 0.0f;

		// Y軸の位置を設定
		float yPos = i * 0.0f;
		if (i == 4) yPos = 2.5f;

		// Z軸の位置を設定
		float zPos = i * 65.0f;
		if (i == 5)   zPos = 5 * 65.0f;
		if (i == 6)   zPos = 5 * 65.0f;
		if (i == 7)   zPos = 6 * 65.0f;
		if (i == 8)   zPos = 6 * 65.0f;
		if (i == 9)   zPos = 7 * 65.0f;
		if (i == 10)  zPos = 7 * 65.0f;
		if (i == 11)  zPos = 8 * 65.0f;
		if (i == 12)  zPos = 8 * 65.0f;
		if (i == 13)  zPos = 9 * 65.0f;

		// X軸のスケール値を設定
		float xScale = 4.0f;
		if (i == 2) xScale = 6.0f;
		if (i == 13)xScale = 6.0f;


		// Z軸のスケール値を設定
		float zScale = 4.0f;
		if (i == 2) zScale = 6.0f;
		if (i == 13) zScale = 6.0f;

		// オブジェクトを作成してタスクに追加
		CNumberFloor1* numberfloor1 = new CNumberFloor1
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 3.0f, zScale),
			CVector(0.0f, 90.0f, 0.0f)
		);

		AddTask(numberfloor1); // タスクに追加
	}

	// セーブポイント
	CSavePoint1* savepoint1 = new CSavePoint1
	(
		CVector(0.0f, 15.0f, 325.0f),
		CVector(8.0f, 8.0f, 8.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint1);

	// 針モデル1
	CNeedleUpDown* needle1 = new CNeedleUpDown(
		CVector(0.0f, 10.0f, 450.0f),
		CVector(20.0f, 20.0f, 20.0f),
		CVector(0.0f, 0.0f, 0.0f),
		3.6f,
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(needle1);
	// 針モデルベース1
	CNeedleUpDownBase* needlebase1 = new CNeedleUpDownBase(
		CVector(0.0f, 10.0f, 450.0f),
		CVector(20.0f, 20.0f, 20.0f),
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
	// 火炎放射器モデル
	// 左方向
	CFixedFlamethrower* flamethrower1 = new CFixedFlamethrower
	(
		CVector(-100.0f, 15.0f, 140.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, -90.0f, 0.0f)
	);
	AddTask(flamethrower1);
	// 火炎放射器の土台
	CRisingObject* dodai = new CRisingObject
	(
		CVector(-100.0f, 15.0f, 140.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(dodai);

	// 火炎放射器モデル
	// 右方向 
	CFixedFlamethrower* flamethrower2 = new CFixedFlamethrower
	(
		CVector(-100.0f, 15.0f, 625.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, -90.0f, 0.0f)
	);
	AddTask(flamethrower2);
	// 火炎放射器の土台
	CRisingObject* dodai2 = new CRisingObject
	(
		CVector(-100.0f, 15.0f, 625.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(dodai2);

	CMeat1* meat1 = new CMeat1
	(
		CVector(0.0f, 45.0f, 134.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	AddTask(meat1);
	meat1->SetMeatNumber(1);

	CMeat2* meat2 = new CMeat2
	(
		CVector(70.0f, 25.0f, 390.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat2->SetMeatNumber(2);
	AddTask(meat2);

	CMeat3* meat3 = new CMeat3
	(
		CVector(-70.0f, 25.0f, 390.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat3->SetMeatNumber(3);
	AddTask(meat3);


	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(0.0f, 25.5f, -70.0f);	//197.0f,1235.0f,279.0f
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 0.0f, 0.0f);
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
	//mainCamera->AddCollider(mpField_Worlds_1->GetWallCol());



	// ブルーメダル獲得イベントを生成
	CBlueMedalEvent* bmEvent = new CBlueMedalEvent();
	AddTask(bmEvent);

	///////////////////////////////////////////////////////////////////////////

	// ブルーメダルを作成
	CBlueMedal* medal1 = new CBlueMedal
	(
		CVector(70.0f, 22.0f, 325.0f),
		CVector(3.0f, 3.0f, 3.0f)
	);
	AddTask(medal1);
	medal1->SetEvent(bmEvent);
	bmEvent->AddBlueMedal(medal1);

	CBlueMedal* medal2 = new CBlueMedal
	(
		CVector(-70.0f, 22.0f, 455.0f),
		CVector(3.0f, 3.0f, 3.0f)
	);
	AddTask(medal2);
	medal2->SetEvent(bmEvent);
	bmEvent->AddBlueMedal(medal2);

	CBlueMedal* medal3 = new CBlueMedal
	(
		CVector(70.0f, 22.0f, 455.0f),
		CVector(3.0f, 3.0f, 3.0f)
	);
	AddTask(medal3);
	medal3->SetEvent(bmEvent);
	bmEvent->AddBlueMedal(medal3);

	CBlueMedal* medal4 = new CBlueMedal
	(
		CVector(0.0f, 22.0f, 130.0f),
		CVector(3.0f, 3.0f, 3.0f)
	);
	AddTask(medal4);
	medal4->SetEvent(bmEvent);
	bmEvent->AddBlueMedal(medal4);

	///////////////////////////////////////////////////////////////////////////

	//障害物の壁を作成
	CObstacleWall* wall = new CObstacleWall
	(
		CVector(0.0f, 25.0f, 623.0f),
		CQuaternion(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 20.0f, 0.2f)
	);
	AddTask(wall);
	wall->SetEvent(bmEvent);
	bmEvent->SetObstacle(wall);
}

// ステージ破棄
void CStage1::Unload()
{
	// カメラから衝突するコライダーを取り除く
	//CCamera* mainCamera = CCamera::MainCamera();
	//mainCamera->RemoveCollider(mpField_Worlds_1->GetWallCol());
	CStageBase::Unload();
}
