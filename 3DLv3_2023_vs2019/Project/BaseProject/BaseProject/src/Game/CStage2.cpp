#include "CStage2.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CGoalObject.h"
#include "CHopsAndHoopsField.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CJumpingKinoko.h"
#include "CJumpingKinokoLeftRight.h"
#include "CJumpingKinokoUpDown.h"
#include "CHopsAndHoopsFallCol.h"
#include "CSavePoint1.h"
#include "CRingBeamer.h"

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
	// 跳ねるキノココライダー								 
	CResourceManager::Load<CModel>("JumpingKinokoCol",		"Field\\Gimmick\\Jump\\JumpingKinoko(Col).obj");
	// リングビーマモデル(上)								  
	CResourceManager::Load<CModel>("RingBeamerUP",			"Effect\\BeamObj(Upper).obj");
	// リングビーマモデル(下)								  
	CResourceManager::Load<CModel>("RingBeamerLO",			"Effect\\BeamObj(Lower).obj");
	// ビリビリエフェクト							    
	CResourceManager::Load<CModel>("Biribiri",				"Effect\\BhimaEffect.obj");
	// リングビーマモデル(コライダー)						  
	CResourceManager::Load<CModel>("BiribiriCol",			"Effect\\BhimaEffect(Col).obj");

	// 肉モデル
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");

	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	CHopsAndHoopsField* field = new CHopsAndHoopsField();
	field->Position(0.0f, 0.0f, 0.0f);
	field->Scale(4.0f, 4.0f, 4.0f);
	field->Rotate(0.0f, 180.0f, 0.0f);
	AddTask(field);
	// 落下コライダー
	mpHopsAndHoopsFallCol = new CHopsAndHoopsFallCol();
	mpHopsAndHoopsFallCol->Scale(4.0f, 4.0f, 4.0f);
	AddTask(mpHopsAndHoopsFallCol);

	// セーブポイント
	CSavePoint1* savepoint1 = new CSavePoint1
	(
		CVector(0.0f, 0.0f, 480.0f),
		CVector(7.0f, 7.0f, 7.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint1);

	// ゴールポスト
	CGoalObject* goal = new CGoalObject
	(
		CVector(0.0f, 0.0f, 1000.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(goal);

	// 動かないキノコ
	// オブジェクトを配置するループ
	for (int i = 0; i < 4; ++i) {

		// X軸の位置を設定
		float xPos = 0.0f;
		if (i == 3) xPos = -80.0f;

		// Y軸の位置を設定
		float yPos = 0.0f;
		/*if (i == 0) yPos = 2.5f;*/

		// Z軸の位置を設定
		float zPos = i * 55.0f;
		if (i == 0) zPos = 144.0f;
		if (i == 1) zPos = 199.0f;
		if (i == 2) zPos = 254.0f;
		if (i == 3) zPos = 480.0f;

		// X軸のスケール値を設定
		float xScale = 1.0f;	

		// Z軸のスケール値を設定
		float zScale = 1.0f;
	
		// オブジェクトを作成してタスクに追加
		CJumpingKinoko* jumpkinoko = new CJumpingKinoko
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 1.0f, zScale),
			CVector(0.0f, 90.0f, 0.0f),
			ETag::ePlayer, ELayer::ePlayer
		);

		AddTask(jumpkinoko); // タスクに追加
	}

	// 動くキノコ(左右)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight1 = new CJumpingKinokoLeftRight
	(
		CVector(0.0f, 0.0f, 309.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(40.0f, 0.0f, 0.0f),
		10.0f,
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(jumpkinokoLeftRight1);
	// 動くキノコ(左右)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight2 = new CJumpingKinokoLeftRight
	(
		CVector(-135.0f, 0.0f, 480.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.0f, 0.0f, 50.0f),
		10.0f,
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(jumpkinokoLeftRight2);

	// 動くキノコ(上下)
	CJumpingKinokoUpDown* jumpkinokoUpDown1 = new CJumpingKinokoUpDown
	(
		CVector(0.0f, 0.0f, 364.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.0f, 40.0f, 0.0f),
		10.0f,
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(jumpkinokoUpDown1);

	// リングビーマ1
	CRingBeamerUpper* beamerUp1 = new CRingBeamerUpper
	(
		CVector(-55.0f, 8.0f, 199.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp1);
	// リングビーマ1
	CRingBeamerLower* beamerLow1 = new CRingBeamerLower
	(
		CVector(-55.0f, 7.5f, 199.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow1);

	// リングビーマ2
	CRingBeamerUpper* beamerUp2 = new CRingBeamerUpper
	(
		CVector(70.0f, 8.0f, 299.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp2);
	// リングビーマ2
	CRingBeamerLower* beamerLow2 = new CRingBeamerLower
	(
		CVector(70.0f, 7.5f, 299.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow2);

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

	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = CVector(0.0f, 20.0f, 50.0f);
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