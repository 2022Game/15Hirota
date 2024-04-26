#include "CStage3.h"
#include "CNumberField.h"
#include "CPlayer.h"
#include "CNumberFloor1.h"
#include "CNumberFloorOnce.h"
#include "CRisingObject.h"
#include "CTreasureChest.h"
#include "CSavePoint.h"
#include "CFixedFlamethrower.h"
#include "CGoalObject.h"

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
	CResourceManager::Load<CModel>("NumberFallCol",			"Field\\FallCol.obj");							// 落下判定コライダー

	// ギミック関連
	CResourceManager::Load<CModel>("Number0",				"Field\\Object\\number0.obj");					// 零番目の床
	CResourceManager::Load<CModel>("Number1",				"Field\\Object\\number1.obj");					// 一番目の床ブロック
	CResourceManager::Load<CModel>("Number2",				"Field\\Object\\number2.obj");					// 二番目の床ブロック
	CResourceManager::Load<CModel>("Number3",				"Field\\Object\\number3.obj");					// 三番目の床ブロック
	CResourceManager::Load<CModel>("FieldCube",				"Field\\Object\\cube.obj");						// 初期の四角のモデル
	CResourceManager::Load<CModel>("TreasureChest",			"Field\\Gimmick\\TreasureChest.obj");			// 宝箱
	CResourceManager::Load<CModel>("TreasureChestTwo",		"Field\\Gimmick\\TreasureChestTwo.obj");		// 宝箱(蓋)
	CResourceManager::Load<CModel>("TreasureChestCol",		"Field\\Gimmick\\TreasureChest(FloorCol).obj");	// 宝箱(蓋コライダー)
	CResourceManager::Load<CModel>("TreasureChestWallCol",	"Field\\Gimmick\\TreasureChest(WallCol).obj");	// 宝箱(壁コライダー)
	CResourceManager::Load<CModel>("SavePoint",				"Field\\Gimmick\\SavePoint.obj");				// セーブポイントモデル
	CResourceManager::Load<CModel>("FlamethrowerModel",		"Field\\Gimmick\\Flamethrower(foundation).obj");// 火炎放射器(土台)
	CResourceManager::Load<CModel>("FlamethrowerTank",		"Field\\Gimmick\\Flamethrower(tank).obj");		// 火炎放射器(タンク)
	CResourceManager::Load<CModel>("FlamethrowerCol",		"Field\\Gimmick\\Flamethrower(WallCol).obj");	// 火炎放射器(コライダー)
	CResourceManager::Load<CModel>("GoalPost",				"Field\\Object\\GoalPost.obj");					// ゴールポストモデル
	CResourceManager::Load<CModel>("GoalCube",				"Field\\Object\\GoalCube.obj");					// ゴールブロックモデル

	// 背景色設定
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	CNumberField* field = new CNumberField();
	field->Scale(1.0f, 1.0f, 1.0f);
	field->Position(0.0f, -190.0f, 0.0f);
	AddTask(field);

	// 初期値点
	CRisingObject* rising = new CRisingObject
	(
		CVector(0.0f, 12.0f, -70.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising);

	// 中間値点
	CRisingObject* rising1 = new CRisingObject
	(
		CVector(0.0f, 12.0f, 350.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising1);

	// ゴール値点
	CRisingObject* rising2 = new CRisingObject
	(
		CVector(0.0f, 12.0f, 740.0f),
		CVector(2.0f, 1.0f, 2.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising2);

	// ゴールポスト0.0f, 10.0f, 720.0f
	CGoalObject* goal = new CGoalObject
	(
		CVector(0.0f, 4.5f, -50.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(goal);

	// オブジェクトを配置するループ
	for (int i = 0; i < 14; ++i) {

		// X軸の位置を設定
		float xPos = 0.0f;
		if (i == 5) xPos	=	70.0f;
		if (i == 6) xPos	= -	70.0f;
		if (i == 7) xPos	=	70.0f;
		if (i == 8) xPos	= -	70.0f;
		if (i == 9) xPos	=	70.0f;
		if (i == 10) xPos	= -	70.0f;
		if (i == 11) xPos	=	50.0f;
		if (i == 12) xPos	= -	50.0f;
		if (i == 13) xPos	=	 0.0f;
		
		// Y軸の位置を設定
		float yPos = i * 0.0f;
		if (i == 4) yPos = 2.5f;

		// Z軸の位置を設定
		float zPos = i * 70.0f;
		if (i == 5)   zPos = 5 * 70.0f;
		if (i == 6)   zPos = 5 * 70.0f;
		if (i == 7)   zPos = 6 * 70.0f;
		if (i == 8)   zPos = 6 * 70.0f;
		if (i == 9)   zPos = 7 * 70.0f;
		if (i == 10)  zPos = 7 * 70.0f;
		if (i == 11)  zPos = 8 * 70.0f;
		if (i == 12)  zPos = 8 * 70.0f;
		if (i == 13)  zPos = 9 * 70.0f;

		// X軸のスケール値を設定
		float xScale = 4.0f;
		if (i == 2) xScale = 6.0f;
		if (i == 13)xScale = 6.0f;


		// Z軸のスケール値を設定
		float zScale = 4.0f;
		if (i == 2) zScale = 6.0f;
		if (i == 13) zScale = 6.0f;
		
		// オブジェクトを作成してタスクに追加
		CNumberFloorOnce* numberfloor = new CNumberFloorOnce
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 3.0f, zScale),
			CVector(0.0f, 90.0f, 0.0f),
			ETag::ePlayer, ELayer::ePlayer
		);

		AddTask(numberfloor); // タスクに追加
	}

	// セーブポイント
	CSavePoint* savepoint = new CSavePoint
	(
		CVector(0.0f, 15.0f, 350.0f),
		CVector(8.0f, 8.0f, 8.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint);


	// 宝箱
	CTreasureChest* treasure = new CTreasureChest
	(
		CVector(0.0f, 18.0f, 779.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure);
	// 宝箱蓋
	CTreasureChestTwo* treasureTwo = new CTreasureChestTwo
	(
		CVector(0.0f, 20.8f, 779.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo);


	// 火炎放射器モデル
	// 左方向
	CFixedFlamethrower* flamethrower1 = new CFixedFlamethrower
	(
		CVector(-100.0f, 15.0f, 140.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 0.0f, 0.0f)
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
		CVector(-100.0f, 15.0f, 630.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(flamethrower2);
	// 火炎放射器の土台
	CRisingObject* dodai2 = new CRisingObject
(
		CVector(-100.0f, 15.0f, 630.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(dodai2);


	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(0.0f, 14.5f, -70.0f);	//197.0f,1235.0f,279.0f
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 0.0f, 0.0f);
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
	//mainCamera->AddCollider(mpField_Worlds_1->GetWallCol());
}

// ステージ破棄
void CStage3::Unload()
{
	// カメラから衝突するコライダーを取り除く
	//CCamera* mainCamera = CCamera::MainCamera();
	//mainCamera->RemoveCollider(mpField_Worlds_1->GetWallCol());
	CStageBase::Unload();
}