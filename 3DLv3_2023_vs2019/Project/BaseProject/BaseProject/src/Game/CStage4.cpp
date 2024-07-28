#include "CStage4.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSeesawAdventure.h"
#include "CSeesaw.h"
#include "CStageSky.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CMeat1Event.h"
#include "CInput.h"

// コンストラクタ
CStage4::CStage4()
{
	mStageNo = 4;
}

// デストラクタ
CStage4::~CStage4()
{

}

// ステージ読み込み
void CStage4::Load()
{
	// ステージの空
	CResourceManager::Load<CModel>("StageSky", "Field\\StageSky\\Sky(Sphere).obj");
	// ステージモデル
	CResourceManager::Load<CModel>("SeesawStage(Base)", "Field\\SeesawStage\\SeesawStage(Base).obj");
	// ステージ床コライダー
	CResourceManager::Load<CModel>("SeesawStage(Floor)", "Field\\SeesawStage\\SeesawStage(FloorCol).obj");
	// ステージ壁コライダー
	CResourceManager::Load<CModel>("SeesawStage(Wall)", "Field\\SeesawStage\\SeesawStage(WallCol).obj");
	// ステージ落下コライダー
	CResourceManager::Load<CModel>("SeesawStage(Fall)", "Field\\SeesawStage\\SeesawStage(FallCol).obj");

	// シーソーモデル
	CResourceManager::Load<CModel>("SeesawModel", "Field\\Gimmick\\SeesawGimmick\\SeesawModel.obj");
	// シーソーモデル
	CResourceManager::Load<CModel>("SeesawModelCol", "Field\\Gimmick\\SeesawGimmick\\SeesawModel(Col).obj");
	
	// 肉モデル
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");
	// サークルエフェクト
	CResourceManager::Load<CModel>("CircleEffect1", "Effect\\CharacterEffect\\CharaEffectCircle.obj");
	CResourceManager::Load<CModel>("CircleEffect2", "Effect\\CharacterEffect\\CharaEffectCircle(Widthver).obj");
	// キャラクターエフェクト
	CResourceManager::Load<CModel>("CharEffect", "Effect\\CharacterEffect\\CharacterEffect(Up).obj");
	// キャラクターエフェクト(ライン)
	CResourceManager::Load<CModel>("LineEffect", "Effect\\CharacterEffect\\CharacterEffect(Line).obj");

	// Tキーの画像
	CResourceManager::Load<CTexture>("TUI", "UI\\GimmickUI\\T.png");

	CResourceManager::Load<CTexture>("Laser", "Effect\\laser.png");

	CInput::ShowCursor(false);

	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	mpFeild = new CSeesawAdventure();
	mpFeild->Position(0.0f, 0.0f, 0.0f);
	mpFeild->Scale(4.0f, 4.0f, 4.0f);
	mpFeild->Rotate(0.0f, 0.0f, 0.0f);
	AddTask(mpFeild);

	// 空
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);

	//// 落下コライダー
	//mpFallCol = new CHopsAndHoopsFallCol();
	//mpFallCol->Scale(20.0f, 3.0f, 20.0f);
	//AddTask(mpFallCol);


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

	//// 肉1を取得すると
	//// ハイジャンプキノコを作成
	//CJumpingKinokoHigh* highkinoko = new CJumpingKinokoHigh
	//(
	//	CVector(-483.0f, 5.0f, 500.0f),
	//	CVector(1.0f, 1.0f, 1.0f),
	//	CVector(0.0f, 0.0f, 0.0f)
	//);
	//AddTask(highkinoko);
	//highkinoko->SetEvent(mtEvent);
	//mtEvent->SetHighKinoko(highkinoko);

	CMeat2* meat2 = new CMeat2
	(
		CVector(337.0f, 35.0f, 1290.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat2->SetMeatNumber(2);
	AddTask(meat2);

	CMeat3* meat3 = new CMeat3
	(
		CVector(-337.0f, 35.0f, 1290.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat3->SetMeatNumber(3);
	AddTask(meat3);

	/////////////////////////////////////////////////////////////////////////////////////

	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	// 初期値点 : 329.0f, -275.0f, -954.0f
	CVector playerPos = CVector(329.0f, -275.0f, -954.0f);
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
	mainCamera->AddCollider(mpFeild->GetWallCol());
}

// ステージ破棄
void CStage4::Unload()
{
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->RemoveCollider(mpFeild->GetWallCol());
	// ベースステージ破棄処理
	CStageBase::Unload();
}