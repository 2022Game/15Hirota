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
#include "CSignboard.h"
#include "CGameCamera.h"
#include "CGameMenu.h"
#include "CEnemyManager.h"
#include "CRisingObject.h"
#include "CStage1.h"
#include "CSound.h"

//コンストラクタ
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
	, mpGameMenu(nullptr)
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
	CResourceManager::Load<CModel>("Field",				"Field\\GameStage(1).obj");					// 仮1面
	CResourceManager::Load<CModel>("FloorCol",			"Field\\GameStageFloor(1).obj");			// 仮1面の床
	CResourceManager::Load<CModel>("WallCol",			"Field\\GameStageWall(1).obj");				// 仮1面の壁
	CResourceManager::Load<CModel>("FieldCube",			"Field\\Object\\cube.obj");					// 初期の四角のモデル
	CResourceManager::Load<CModel>("FieldCylinder",		"Field\\Object\\cylinder.obj");				// 初期の回転する四角モデル
	CResourceManager::Load<CModel>("GoalCube",			"Field\\Object\\GoalCube.obj");				// ゴールの土台
	CResourceManager::Load<CModel>("GoalPost",			"Field\\Object\\GoalPost.obj");				// ゴールのポスト
	CResourceManager::Load<CModel>("Stone1",			"Field\\Object\\Stone1.obj");				// 石1
	CResourceManager::Load<CModel>("Signboard",			"Field\\Object\\signboard.obj");			// 看板オブジェクト(ジャンプヒント)
	CResourceManager::Load<CModel>("HatenaBlock",		"Field\\Object\\hatena.obj");				// ハテナブロック(アイテム保有)
	CResourceManager::Load<CModel>("HatenaBlockAfter",	"Field\\Object\\UsedHatenaBlock.obj");		// ハテナブロック(アイテム不保有)
	CResourceManager::Load<CModel>("RengaBlock",		"Field\\Object\\RengaBlock.obj");			// レンガブロック


	// キャラクター関連
	CResourceManager::Load<CModelX>("Player",			"Character\\Monster1\\Monster_1.x");						// プレイヤー
	CResourceManager::Load<CModelX>("Soldier",			"Character\\Gas mask soldier\\GasMask_Soldier_Model.x");	// ソルジャー
	//CResourceManager::Load<CModelX>("UnityChan",		"Character\\UnityChan\\unitychan.x");						// ユニティちゃん
	CResourceManager::Load<CModelX>("Yukari",			"Character\\Yukari\\Yukari_Model.x");						// ゆかりさん


	// アイテム関連
	CResourceManager::Load<CModel>("Bullet",			"Item\\Bullet1\\Bullet.obj");				// 弾
	CResourceManager::Load<CModel>("Gun_M1G",			"Item\\Gun_M1Garand\\Gun_M1Garand.obj");	// M1ガーランド(銃)
	CResourceManager::Load<CModel>("MajicSword",		"Item\\MajicSword\\MajicSword.obj");		// 魔法剣
	CResourceManager::Load<CModel>("Heart",				"Item\\StatusItem\\Heart.obj");				// 回復オブジェクト
	CResourceManager::Load<CModel>("Star",				"Item\\StatusItem\\Star.obj");				// 無敵オブジェクト
	CResourceManager::Load<CModel>("Medal",				"Item\\StatusItem\\Medal.obj");				// 得点オブジェクト


	// UI関連
	CResourceManager::Load<CTexture>("PFrame",			"UI\\Image_Gauge_Frame.png");		// プレイヤーのフレーム
	CResourceManager::Load<CTexture>("PBarImage",		"UI\\WhiteUI.png");					// プレイヤーのバー
	CResourceManager::Load<CTexture>("PStamina",		"UI\\Sutamina.png");				// プレイヤーのスタミナ
	CResourceManager::Load<CTexture>("SFrame",			"UI\\Image_Gauge_Frame.png");		// ソルジャーのフレーム
	CResourceManager::Load<CTexture>("SBar",			"UI\\Gauge.png");					// ソルジャーのバー
	CResourceManager::Load<CTexture>("YFrame",			"UI\\Image_Gauge_Frame.png");		// ゆかりさんのフレーム
	CResourceManager::Load<CTexture>("YBar",			"UI\\Gauge.png");					// ゆかりさんのバー
	CResourceManager::Load<CTexture>("CSignboardUI",	"UI\\Ukye_1.png");					// Uキーの画像


	// エフェクト関連
	CResourceManager::Load<CTexture>("Laser",			"Effect\\laser.png");			// 弾のエフェクト


	// BGM関連
	CResourceManager::Load<CSound>("SlashSound", "SE\\slash.wav");

	// ゲームBGMを読み込み
	mpGameBGM = CResourceManager::Load<CSound>("GameBGM", "BGM\\game.wav");
	// ゲームBGMのループ範囲を設定
	mpGameBGM->SetLoopRange(0, 2801203);
	// ゲームBGMをループ再生開始
	mpGameBGM->PlayLoop();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

	// ゲームメニューを作成
	mpGameMenu = new CGameMenu();


	CGameManager::GameStart();
}

//シーンの更新処理
void CGameScene::Update()
{
	if (CInput::PushKey('H'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eTitle);
	}


	// ゲームメニューを開いてなければ、[Ｍ]キーでメニューを開く
	if (!mpGameMenu->IsOpened())
	{
		if (CInput::PushKey('M'))
		{
			mpGameMenu->Open();
		}
	}

	// [CStage1] の処理 /////////////////////////////////////////////////////////////

	int enemyCount = CEnemyManager::GetEnemyCount();	// ソルジャーの数

	static bool Rising = false;

	if (enemyCount <= 0 && !Rising)	// ステージ番号
	{
		int currentStage = CGameManager::StageNo();
		if (currentStage == 0)
		{
			// 上昇するオブジェクト
			CRisingObject* rising = new CRisingObject
			(
				CVector(-30.0f, 3.0f, -450.0f),
				CVector(0.5f, 0.5f, 0.5f),
				ETag::ePlayer, ELayer::ePlayer
			);
			CVector risingPos = CVector(-30.0f, 3.0f, -450.0f);
			if (rising != nullptr)
			{
				rising->SetStartPosition(risingPos);
			}
			AddTask(rising);

			// 二度目以降はオブジェクトが作成されないようにする
			Rising = true;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////

	// ステージ番号の確認
	CDebugPrint::Print("StageNo:%d\n", CGameManager::StageNo());
	// ソルジャーの数の確認
	CDebugPrint::Print("count:%d\n", CEnemyManager::GetEnemyCount());
}