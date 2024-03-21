#include "CStage2.h"
#include "CDamageObject.h"
#include "CGoalObject.h"
#include "CStone1.h"
#include "CTree1.h"
#include "CField1.h"
#include "CSoldier.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CAppearFloor.h"
#include "CGameCamera.h"
#include "CRotateFloorGimmick.h"
#include "CRotateFloorTimeGimmick.h"
#include "CHatenaBlock.h"
#include "CRengaBlock.h"
#include "CClimbWall.h"

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
	CResourceManager::Load<CModel>("Field1",			"Field\\Stage2.obj");								// 仮2面
	CResourceManager::Load<CModel>("FloorCol1",			"Field\\Stage2Floor.obj");							// 仮2面床
	CResourceManager::Load<CModel>("WallCol1",			"Field\\Stage2Wall.obj");							// 仮2面壁
	CResourceManager::Load<CModel>("Field1",			"Field\\Stage2.obj");								// 仮2面敵の壁
	CResourceManager::Load<CModel>("Stage2Tree",		"Field\\Stage2(tree).obj");							// 仮2面の木
	CResourceManager::Load<CModel>("Stage2Climb",		"Field\\PlayerGimmick\\Stage2(Climb).obj");			// 仮2面の登れる壁
	CResourceManager::Load<CModel>("Stage2ClimbedTop",	"Field\\PlayerGimmick\\Stage2(ClimbedTop).obj");	// 仮2面の登れる壁の頂上コライダー
	CResourceManager::Load<CModel>("RotateFloor",		"Field\\Gimmick\\RotateFloor.obj");					// 回転する床
	CResourceManager::Load<CModel>("RotateFloorFrame",	"Field\\Gimmick\\RotateFloorFrame.obj");			// 回転する床枠
	CResourceManager::Load<CModel>("Tree1",				"Field\\Object\\Tree1.obj");						// 木1

	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);


	// フィールド
	CField1* field = new CField1();
	field->Scale(10.0f, 10.0f, 10.0f);
	AddTask(field);

	// 登れる壁を作成
	CClimbWall* climbWall = new CClimbWall
	(
		"Stage2Climb", "Stage2ClimbedTop",
		CVector(0.0f,20.0f,0.0f),	// 上方向の移動
		CVector(0.0f, 10.0f, 20.0f)	// 正面方向の移動
	);
	climbWall->Scale(10.0f, 10.0f, 10.0f);
	AddTask(climbWall);


	// モンスター(プレイヤー)
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = CVector(-757.0f, 60.0f, -858.0f);//-757,858-1109.0f, 60.0f, 1133.0f
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 225.0f, 0.0f);//0.0f, 225.0f, 0.0f
	}

	// カメラの位置と向きを設定 -1109.0f, 90.0f, 1200.0f
	CGameCamera* mainCamera = new CGameCamera
		//CCamera* mainCamera = new CCamera
		(
			CVector(-757.0f, 90.0f, -958.0f),
			player->Position() + CVector(0.0f, 0.0f, 0.0f)
		);
	mainCamera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	mainCamera->AddCollider(field->GetWallCol());

	// ハテナブロック
	CHatenaBlock* hatena = new CHatenaBlock
	(
		CVector(-900.0f, 8.0f, -888.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector hatenaPos = CVector(-900.0f, 8.0f, -888.0f);
	if (hatena != nullptr)
	{
		hatena->SetStartPosition(hatenaPos);
	}
	AddTask(hatena);

	// レンガブロック
	CRengaBlock* renga = new CRengaBlock
	(
		CVector(-850.0f, 8.0f, -888.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector rengaPos = CVector(-850.0f, 8.0f, -888.0f);
	if (renga != nullptr)
	{
		renga->SetStartPosition(rengaPos);
	}
	AddTask(renga);


	// 回転する床ギミック(プレイヤーに反応)
	CRotateFloorGimmick* rotategimmick = new CRotateFloorGimmick(
		CVector(-770.0f, 7.0f, -888.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector rotategimmickPos = CVector(-770.0f, 7.0f, -888.0f);
	if (rotategimmick != nullptr)
	{
		rotategimmick->SetStartPosition(rotategimmickPos);
	}
	AddTask(rotategimmick);

	// 回転する床ギミック(常に)
	CRotateFloorTimeGimmick* rotatetimegimmick = new CRotateFloorTimeGimmick(
		CVector(-740.0f, 7.0f, -888.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector rotatetimegimmickPos = CVector(-740.0f, 7.0f, -888.0f);
	if (rotatetimegimmick != nullptr)
	{
		rotatetimegimmick->SetStartPosition(rotatetimegimmickPos);
	}
	AddTask(rotatetimegimmick);

	//// 木1 //////////////////////////////////////////////

	// 木1
	CTree1Obj* tree1 = new CTree1Obj(
		CVector(-1100.0f, 0.0f, 1100.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f));
	AddTask(tree1);

	// 木2
	CTree1Obj* tree2 = new CTree1Obj(
		CVector(-1000.0f, 0.0f, 1000.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f));
	AddTask(tree2);


	///////////////////////////////////////////////////////
}

// ステージ破棄
void CStage2::Unload()
{
	// ベースステージ破棄処理
	CStageBase::Unload();
}