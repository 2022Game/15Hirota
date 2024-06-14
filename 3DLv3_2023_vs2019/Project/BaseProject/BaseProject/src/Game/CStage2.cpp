#include "CStage2.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CGoalObject.h"
#include "CHopsAndHoopsField.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"

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
	CResourceManager::Load<CModel>("HopsAndHoops(Base)", "Field\\HopsAndHoops\\Stage2(Base).obj");
	// ステージ床コライダー
	CResourceManager::Load<CModel>("HopsAndHoops(Col)",	 "Field\\HopsAndHoops\\Stage2(FloorCol).obj");
	// セーブポイントモデル
	CResourceManager::Load<CModel>("SavePoint",			 "Field\\Gimmick\\SavePoint.obj");
	// ゴールポストモデル							    
	CResourceManager::Load<CModel>("GoalPost",			 "Field\\Object\\GoalPost.obj");
	// ゴールブロックモデル							   
	CResourceManager::Load<CModel>("GoalCube",			 "Field\\Object\\GoalCube.obj");
	// 跳ねるキノコモデル							    
	CResourceManager::Load<CModel>("JumpingKinoko",		 "Field\\Gimmick\\Jump\\JumpingKinoko(Base).obj");
	// 跳ねるキノココライダー							  
	CResourceManager::Load<CModel>("JumpingKinokoCol",	 "Field\\Gimmick\\Jump\\JumpingKinoko(Col).obj");
	// リングビーマモデル(上)							   
	CResourceManager::Load<CModel>("RingBeamerUP",		 "Effect\\BeamObj(Upper).obj");
	// リングビーマモデル(下)							   
	CResourceManager::Load<CModel>("RingBeamerLO",		 "Effect\\BeamObj(Lower).obj");
	// ビリビリエフェクト							    
	CResourceManager::Load<CModel>("Biribiri",			 "Effect\\BhimaEffect.obj");
	// リングビーマモデル(コライダー)					   
	CResourceManager::Load<CModel>("BiribiriCol",		 "Effect\\BhimaEffect(Col).obj");

	// 肉モデル
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");

	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	CHopsAndHoopsField* field = new CHopsAndHoopsField();
	field->Scale(4.0f, 4.0f, 4.0f);
	field->Position(0.0f, 0.0f, 0.0f);
	AddTask(field);


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
	CVector playerPos = CVector(0.0f, 20.0f, 0.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 180.0f, 0.0f);//0.0f, 225.0f, 0.0f
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