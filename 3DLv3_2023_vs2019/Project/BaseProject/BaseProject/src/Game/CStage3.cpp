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
#include "CNumberFloor1.h"
#include "CNumberFloor2.h"
#include "CNumberFloor3.h"
#include "CNbFlMove2.h"
#include "CCircleNbFlLeft2.h"
#include "CCircleNbFlRight2.h"
#include "CMoveToNbFl1.h"
#include "CHorizontalCannon.h"
#include "CCannon.h"
#include "CPowerfulCannon.h"
#include "CJumpingKinoko.h"
#include "CJumpingKinokoMoveTo.h"
#include "CRingBeamer.h"
#include "CFixedFlamethrower.h"
#include "CRotateFloorGimmick.h"
#include "CRotateFloorGimmickOpposition.h"
#include "CRotateFloorTimeGimmick.h"
#include "CSavePoint1.h"
#include "CSavePoint2.h"
#include "CGoalObject.h"
#include "CRengaBlock.h"
#include "CHatenaBlock.h"
#include "CPicoChan.h"
#include "CSoldier.h"
#include "CVanguard.h"
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
	CResourceManager::Load<CModel>("StageSky",		"Field\\StageSky\\Sky(Sphere).obj");
	// ステージモデル
	CResourceManager::Load<CModel>("Stage3Base",	"Field\\Final Stage\\Base.obj");
	// ステージのラインモデル
	CResourceManager::Load<CModel>("Stage3Line",	"Field\\Final Stage\\Line.obj");
	// 床のコライダー
	CResourceManager::Load<CModel>("Stage3FloorCol","Field\\Final Stage\\FloorCol.obj");
	// 壁のコライダー
	//CResourceManager::Load<CModel>("WallCol",		"Field\\GameStage(Worlds_3)\\GameStage_1(wallCol).obj");
	// 落下判定コライダー
	CResourceManager::Load<CModel>("Stage3FallCol", "Field\\Final Stage\\FallCol.obj");

	// 零番目の床
	CResourceManager::Load<CModel>("Number0", "GameGimmick\\Gimmick\\NumberFloor\\number0.obj");
	// 一番目の床ブロック
	CResourceManager::Load<CModel>("Number1", "GameGimmick\\Gimmick\\NumberFloor\\number1.obj");
	// 二番目の床ブロック
	CResourceManager::Load<CModel>("Number2", "GameGimmick\\Gimmick\\NumberFloor\\number2.obj");
	// 三番目の床ブロック
	CResourceManager::Load<CModel>("Number3", "GameGimmick\\Gimmick\\NumberFloor\\number3.obj");

	// 大砲土台モデル
	CResourceManager::Load<CModel>("CannonFound", "GameGimmick\\Gimmick\\Cannon\\CannonFoundations.obj");
	// 水平大砲土台モデル
	CResourceManager::Load<CModel>("HorizontalCannonFound", "GameGimmick\\Gimmick\\Cannon\\CannonFoundation(Horizontal).obj");
	// 大砲
	CResourceManager::Load<CModel>("Cannon", "GameGimmick\\Gimmick\\Cannon\\Cannon.obj");
	// 水平大砲
	CResourceManager::Load<CModel>("HorizontalCannon", "GameGimmick\\Gimmick\\Cannon\\HorizontalCannon.obj");
	// 大砲玉モデル
	CResourceManager::Load<CModel>("CannonBall", "GameGimmick\\Gimmick\\Cannon\\CannonBall.obj");

	// 火炎放射器(タンク)
	CResourceManager::Load<CModel>("", "");	
	// 火炎放射器(土台)
	CResourceManager::Load<CModel>("", "");
	// 火炎放射器(コライダー)
	CResourceManager::Load<CModel>("", "");

	// 跳ねるキノコモデル							    
	CResourceManager::Load<CModel>("JumpingKinoko", "GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Base).obj");
	// 跳ねるキノコモデル2						    
	CResourceManager::Load<CModel>("JumpingKinoko2Color", "GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Base_2Color).obj");
	// 跳ねるキノコモデル3						    
	CResourceManager::Load<CModel>("JumpingKinoko3Color", "GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Base_3Color).obj");
	// 跳ねるキノココライダー								 
	CResourceManager::Load<CModel>("JumpingKinokoCol", "GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Col).obj");
	
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

	// オブジェクトを配置するループ
	for (int i = 0; i < 1; ++i) {

		// X軸の位置を設定
		float xPos = 0.0f;
		//if (i == 0) xPos = 26.0f;

		// 左ルート
		//if (i == 2) xPos = 95.0f;
		
		// ゴール付近
		//if (i == 7) xPos = 26.0f;


		// Y軸の位置を設定
		float yPos = -2.0f;
		//if (i == 0) yPos = -35.0f;
		
		// 左ルート
		//if (i == 2) yPos = 0.0f;
		
		// ゴール付近
		//if (i == 7) yPos = 5.0f;		

		// Z軸の位置を設定
		float zPos = 0.0f;
		if (i == 0) zPos = 80.0f;

		// 左ルート
		//if (i == 2) zPos = 720.0f;

		// ゴール付近
		//if (i == 7) zPos = 1450.0f;

		// X軸のスケール値を設定
		float xScale = 2.0f;
		//if (i == 5) xScale = 5.0f;

		// Z軸のスケール値を設定
		float zScale = 2.0f;
		//if (i == 5) zScale = 5.0f;

		// Y軸の回転値を設定
		float yRotate = 45.0f;
		//if (i == 2) yRotate = 30.0f;

		// オブジェクトを作成してタスクに追加
		CNumberFloor3* numberfloor3 = new CNumberFloor3
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 2.0f, zScale),
			CVector(0.0f, yRotate, 0.0f)
		);

		AddTask(numberfloor3); // タスクに追加
	}

	// 動く床(右円回転)
	CCircleNbFlRight2* floor2right1 = new CCircleNbFlRight2
	(
		CVector(-60.0f, -15.0f, 153.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 45.0f, 0.0f),
		30.0f, 30.0f, 40.0f,
		true
	);
	AddTask(floor2right1);

	// 動く床(左円回転)
	CCircleNbFlLeft2* floor2left2 = new CCircleNbFlLeft2
	(
		CVector(63.0f, -15.0f, 153.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 45.0f, 0.0f),
		30.0f, 30.0f, 40.0f,
		false
	);
	AddTask(floor2left2);


	// 指定した移動ポイント間を移動する回数制限床
	CMoveToNbFl1* mn1f1 = new CMoveToNbFl1
	(
		CVector(3.0f, 2.0f, 3.0f),
		CVector(0.0f, 45.0f, 0.0f),
		2.0f
	);
	mn1f1->SetReturnRoute(false);
	mn1f1->AddMovePoint(CVector(78.0f, -15.0f, 237), 3.0f);
	mn1f1->AddMovePoint(CVector(-78.0f, -15.0f, 237), 3.0f);
	AddTask(mn1f1);

	// 大砲(揺れる大砲の弾)
	CHorizontalCannon* cannon1 = new CHorizontalCannon
	(
		CVector(-178.0f, 8.0f, 153.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, -90.0f, 0.0f)
	);
	AddTask(cannon1);
	// 大砲土台
	CCannonFoundationsHorizontal* cannonfound1 = new CCannonFoundationsHorizontal
	(
		CVector(-178.0f, 8.0f, 153.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, -90.0f, 0.0f)
	);
	AddTask(cannonfound1);

	// 大砲(揺れる大砲の弾)
	CHorizontalCannon* cannon2 = new CHorizontalCannon
	(
		CVector(173.0f, 8.0f, 153.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(cannon2);
	// 大砲土台
	CCannonFoundationsHorizontal* cannonfound2 = new CCannonFoundationsHorizontal
	(
		CVector(173.0f, 8.0f, 153.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(cannonfound2);

	// ジャンプキノコ
	CJumpingKinoko* jumpkinoko = new CJumpingKinoko
	(
		CVector(0.0f, -2.0f, 650.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 90.0f, 0.0f)
	);

	AddTask(jumpkinoko);

	
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

	// ピコちゃん
	CPicoChan* pico = new CPicoChan();
	pico->Position(0.0f, 8.0f, 453.0f);
	pico->Scale(15.5f, 15.5f, 15.5f);
	pico->SetCenterPoint(CVector(0.0f, 0.0f, 453.0f), 30.0f);
	AddTask(pico);
	
	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	// 初期値点 : 0.0f, 10.0f, 0.0f
	// 中間地点 : 0.0f, 320.0f, -1050.0f
	// ボス前	: 0.0f, 430.0f, -1890.0f
	// ゴール付近:	-367.0f, 395.0f, -2040.0f
	// 火炎放射器の前 : -207.0f, 126.0f, -912.0f
	CVector playerPos = CVector(0.0f, 15.0f, 0.0f);
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