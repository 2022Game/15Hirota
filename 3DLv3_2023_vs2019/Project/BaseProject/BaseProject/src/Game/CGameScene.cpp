#include "CGameScene.h"
#include "CSceneManager.h"
#include "CGameOverScene.h"
#include "CClearScene.h"
#include "CField.h"
#include "CCamera.h"
#include "CUIBase.h"
#include "CInput.h"
#include "CStageManager.h"
#include "CGameManager.h"
#include "CPlayer.h"
#include "CSoldier.h"


//コンストラクタ
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
{
}


//デストラクタ
CGameScene::~CGameScene()
{
}


//シーン読み込み
void CGameScene::Load()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//ここでゲーム中に必要な
	//リソースの読み込みやクラスの生成を行う

	// フィールド関連
	CResourceManager::Load<CModel>("Field",			"Field\\GameStage(1).obj");			// 仮1面
	CResourceManager::Load<CModel>("FloorCol",		"Field\\GameStageFloor(1).obj");	// 仮1面の床
	CResourceManager::Load<CModel>("WallCol",		"Field\\GameStageWall(1).obj");		// 仮1面の壁
	CResourceManager::Load<CModel>("FieldCube",		"Field\\Object\\cube.obj");			// 初期の四角のモデル
	CResourceManager::Load<CModel>("FieldCylinder", "Field\\Object\\cylinder.obj");		// 初期の回転する四角モデル
	CResourceManager::Load<CModel>("GoalCube",		"Field\\Object\\GoalCube.obj");		// ゴールの土台
	CResourceManager::Load<CModel>("GoalPost",		"Field\\Object\\GoalPost.obj");		// ゴールのポスト
	CResourceManager::Load<CModel>("Stone1",		"Field\\Object\\Stone1.obj");		// 石1


	// キャラクター関連
	CResourceManager::Load<CModelX>("Player",	"Character\\Monster1\\Monster_1.x");						// プレイヤー
	CResourceManager::Load<CModelX>("Soldier",	"Character\\Gas mask soldier\\GasMask_Soldier_Model.x");	// ソルジャー
	//CResourceManager::Load<CModelX>("UnityChan", "Character\\UnityChan\\unitychan.x");					// ユニティちゃん
	CResourceManager::Load<CModelX>("Yukari", "Character\\Yukari\\Yukari_Model.x");							// ゆかりさん


	// アイテム関連
	CResourceManager::Load<CModel>("Bullet",	 "Item\\Bullet1\\Bullet.obj");				// 弾
	CResourceManager::Load<CModel>("Gun_M1G",	 "Item\\Gun_M1Garand\\Gun_M1Garand.obj");	// M1ガーランド(銃)
	CResourceManager::Load<CModel>("MajicSword", "Item\\MajicSword\\MajicSword.obj");		// 魔法剣


	// UI関連
	CResourceManager::Load<CTexture>("PFrame",		"UI\\Image_Gauge_Frame.png");		// プレイヤーのフレーム
	CResourceManager::Load<CTexture>("PBarImage",	"UI\\WhiteUI.png");					// プレイヤーのバー
	CResourceManager::Load<CTexture>("PStamina",	"UI\\Sutamina.png");				// プレイヤーのスタミナ
	CResourceManager::Load<CTexture>("SFrame",		"UI\\Image_Gauge_Frame.png");		// ソルジャーのフレーム
	CResourceManager::Load<CTexture>("SBar",		"UI\\Gauge.png");					// ソルジャーのバー
	CResourceManager::Load<CTexture>("YFrame",		"UI\\Image_Gauge_Frame.png");		// ゆかりさんのフレーム
	CResourceManager::Load<CTexture>("YBar",		"UI\\Gauge.png");					// ゆかりさんのバー

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// ユニティちゃん
	//CUnityChan* unity = new CUnityChan();
	//unity->Scale(1.0f, 1.0f, 1.0f);
	//unity->Position(0.0f, 20.0f, 0.0f);


	// フィールド
	CField* field = new CField();

	// モンスター(プレイヤー)
	CPlayer* player = new CPlayer();

	//CCamera* mainCamera = new CCamera
	//(
	//	CVector(0.0f, 80.0f, 45.0f),
	//	player->Position() + CVector(0.0f, 10.0f, 0.0f)
	//);
	//mainCamera->SetFollowTargetTf(player);
	//// スフィアかメッシュぐらい
	//mainCamera->AddCollider(field->GetWallCol());


	CGameManager::GameStart();
}

//シーンの更新処理
void CGameScene::Update()
{
	CDebugPrint::Print("enemy: %d\n", CSoldier::GetEnemyCount());
	//CDebugPrint::Print("enemy: %d\n", CSoldier::GetEnemyCount());
	//// hp取得
	//int currentHP = CPlayer::Instance()->GetHp();
	//// 最大hp取得
	//int maxHP = CPlayer::Instance()->GetMaxHp();

	//int Enemy = CSoldier::GetEnemyCount();

	//if (Enemy <= 0)
	//{
	//	CSceneManager::Instance()->LoadScene(EScene::eClear);
	//}

	/*if (currentHP <= 0)
	{
		CSceneManager::Instance()->LoadScene(EScene::eOver);
	}*/

	//// hpが半分を切るとeOverに遷移させる
	//if (currentHP <= 0) {
	//	CSceneManager::Instance()->LoadScene(EScene::eOver);
	//}
	/*else if (currentHP <= 5 && Clear)
	{
		if (Clear)
		{
			image->Load("UI\\Clear.jpeg");
			if (CInput::PushKey('C'))
			{
				CSceneManager::Instance()->LoadScene(EScene::eClear);
			}
		}
	}*/
}