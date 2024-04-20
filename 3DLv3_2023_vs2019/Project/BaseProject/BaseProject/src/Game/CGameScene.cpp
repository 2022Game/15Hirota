#include "CGameScene.h"
#include "CSceneManager.h"
#include "CTaskManager.h"
#include "CGameOverScene.h"
#include "CClearScene.h"
#include "CField.h"
#include "CStageSelection.h"
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
#include "CBGMManager.h"
#include "CJumpingObject.h"
#include "CInventoryMenu.h"
#include "CStageTime.h"
#include "CScore.h"
#include "CVanguard.h"
#include "CBlueMedal.h"

//コンストラクタ
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
	, mpGameMenu(nullptr)
	, mpInventoryMenu(nullptr)
	, mTime(500)
	, mScore(0)
{
}

//デストラクタ
CGameScene::~CGameScene()
{
	mpTime->Kill();
	mpScore->Kill();
}

//シーン読み込み
void CGameScene::Load()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//ここでゲーム中に必要な
	//リソースの読み込みやクラスの生成を行う

	// フィールド関連
	//CResourceManager::Load<CModel>("FieldCylinder",			 "Field\\Object\\cylinder.obj");					// 初期の回転する四角モデル
	//CResourceManager::Load<CModel>("HatenaBlock",			 "Field\\Object\\hatena.obj");						// ハテナブロック(アイテム保有)
	//CResourceManager::Load<CModel>("HatenaBlockAfter",		 "Field\\Object\\UsedHatenaBlock.obj");				// ハテナブロック(アイテム不保有)
	//CResourceManager::Load<CModel>("RengaBlock",			 "Field\\Object\\RengaBlock.obj");					// レンガブロック


	// キャラクター関連
	CResourceManager::Load<CModelX>("Player",				"Character\\Monster1\\Monster_1.x");						// プレイヤー
	//CResourceManager::Load<CModelX>("Soldier",				"Character\\Gas mask soldier\\GasMask_Soldier_Model.x");	// ソルジャー
	////CResourceManager::Load<CModelX>("UnityChan",			"Character\\UnityChan\\unitychan.x");						// ユニティちゃん
	////CResourceManager::Load<CModelX>("Yukari",				"Character\\Yukari\\Yukari_Model.x");						// ゆかりさん


	// アイテム関連
	//CResourceManager::Load<CModel>("Bullet",				"Item\\Bullet1\\Bullet.obj");				// 弾
	//CResourceManager::Load<CModel>("Gun_M1G",				"Item\\Gun_M1Garand\\Gun_M1Garand.obj");	// M1ガーランド(銃)
	CResourceManager::Load<CModel>("MajicSword",			"Item\\MajicSword\\MajicSword.obj");		// 魔法剣
	CResourceManager::Load<CModel>("MajicSwordVan",			"Item\\MajicSword\\MajicSword(Van).obj");	// 魔法剣ヴァンガード
	//CResourceManager::Load<CModel>("Heart",					"Item\\StatusItem\\Heart.obj");				// 回復オブジェクト
	//CResourceManager::Load<CModel>("Star",					"Item\\StatusItem\\Star.obj");				// 無敵オブジェクト
	//CResourceManager::Load<CModel>("Medal",					"Item\\StatusItem\\Medal.obj");				// 得点オブジェクト
	//CResourceManager::Load<CModel>("Healing",				"Item\\StatusItem\\HealingItem.obj");		// 回復薬オブジェクト


	// UI関連
	CResourceManager::Load<CTexture>("PFrame",				"UI\\Image_Gauge_Frame.png");		// プレイヤーのフレーム
	CResourceManager::Load<CTexture>("PBarImage",			"UI\\WhiteUI.png");					// プレイヤーのバー
	CResourceManager::Load<CTexture>("PStamina",			"UI\\Sutamina.png");				// プレイヤーのスタミナ
	CResourceManager::Load<CTexture>("SFrame",				"UI\\Image_Gauge_Frame.png");		// ソルジャーのフレーム
	CResourceManager::Load<CTexture>("SBar",				"UI\\Gauge.png");					// ソルジャーのバー
	CResourceManager::Load<CTexture>("YFrame",				"UI\\Image_Gauge_Frame.png");		// ゆかりさんのフレーム
	CResourceManager::Load<CTexture>("YBar",				"UI\\Gauge.png");					// ゆかりさんのバー
	CResourceManager::Load<CTexture>("SignboardUI",			"UI\\Ukye_1.png");					// Uキーの画像
	CResourceManager::Load<CTexture>("ExclamationMark",		"UI\\bikkurimark.png");				// ビックリマーク画像
	CResourceManager::Load<CTexture>("Timer",				"UI\\StageUI\\Timer.png");			// タイマー画像

	// アイテムUI関連
	//CResourceManager::Load<CTexture>("InvincibleUI",		"UI\\Item\\Invincible Item.png");			// 無敵アイテム用のUI
	//CResourceManager::Load<CTexture>("AttackUpUI",			"UI\\Item\\Increase Attack Power.png");		// 攻撃力アップアイテム用のUI
	//CResourceManager::Load<CTexture>("HealthUI",			"UI\\Item\\Health Recovery Items.png");		// 防御力アップアイテム用のUI
	//CResourceManager::Load<CTexture>("No ItemUI",			"UI\\Item\\NoItemUI.png");					// アイテム無し用のUI



	// エフェクト関連
	CResourceManager::Load<CTexture>("Laser",				"Effect\\laser.png");				// 弾のエフェクト
	CResourceManager::Load<CModel>("Slash",					"Effect\\slash.obj");


	// BGM・SE関連
	CResourceManager::Load<CSound>("SlashSound",			"Sound\\SE\\slash.wav");				// 剣　スラッシュ
	CResourceManager::Load<CSound>("8bitKaifuku",			"Sound\\SE\\8bitkaifuku.wav");			// 8bitの回復音
	CResourceManager::Load<CSound>("8bitShot",				"Sound\\SE\\8bitshot.wav");				// 8bitの銃の音(ブロック用に使う)
	CResourceManager::Load<CSound>("8bitMutekiTime",		"Sound\\SE\\8bitMuteki.wav");			// 8bitの回復音(無敵用に使う)
	CResourceManager::Load<CSound>("CreatureGrowl1",		"Sound\\VOICE\\CreatureStereo5.wav");	// クリーチャーの唸り声1


	// ゲーム内のBGM
	CBGMManager::Instance()->Play(EBGMType::eGame);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//// フィールド
	//CStageSelection* field = new CStageSelection();

	// モンスター(プレイヤー)
	CPlayer* player = new CPlayer();

	new CGameCamera
	(
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);

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
	int currentStage = CGameManager::StageNo();
	mpTime = new CStageTime();
	mpScore = new CScore();
	if (currentStage == 0)
	{
		mpTime->SetShow(false);
		mpScore->SetShow(false);
	}
	else if (currentStage == 1)
	{
		mpTime->SetShow(true);
		mpScore->SetShow(true);

	}
	// インベントリを作成
	mpInventoryMenu = new CInventoryMenu();
	mpInventoryMenu->SetPlayer(player);

	

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

	// インベントリを開いていなければ、[I]キーでメニューを開く
	if (!mpInventoryMenu->IsOpened())
	{
		if (CInput::PushKey('I'))
		{
			mpInventoryMenu->Open();
		}
	}
	// インベントリを開いていたら、[I]キーでメニューを閉じる
	else
	{
		if (CInput::PushKey('I'))
		{
			mpInventoryMenu->Close();
		}
	}

	// [CStage1] の処理 /////////////////////////////////////////////////////////////

	//int enemyCount = CEnemyManager::GetVanguardCount();	// ヴァンガードの数
	//int enemyCount1 = CEnemyManager::GetSoldierCount();	// ソルジャーの数

	//static bool Rising = false;
	//static bool jumping = false;

	//if (enemyCount <= 0 && !Rising)
	//{
	//	int currentStage = CGameManager::StageNo();
	//	if (currentStage == 0)
	//	{
	//		// 上昇するオブジェクト
	//		CRisingObject* rising = new CRisingObject
	//		(
	//			CVector(20.0f, 1.0f, -550.0f),
	//			CVector(0.5f, 0.5f, 0.5f),
	//			ETag::ePlayer, ELayer::ePlayer
	//		);
	//		CVector risingPos = CVector(20.0f, 1.0f, -550.0f);
	//		if (rising != nullptr)
	//		{
	//			rising->SetStartPosition(risingPos);
	//		}
	//		AddTask(rising);

	//		// 二度目以降はオブジェクトが作成されないようにする
	//		Rising = true;
	//	}
	//}

	//if (enemyCount1 <= 0 && !jumping)
	//{
	//	int currentStage1 = CGameManager::StageNo();
	//	if (currentStage1 == 0)
	//	{
	//		// ジャンプする床-100.0f, 20.0f, -450.0f
	//		CJumpingObject* jump = new CJumpingObject
	//		(
	//			CVector(0.0f, -5.0f, -340.0f),
	//			CVector(0.5f, 0.5f, 0.5f),
	//			CVector(0.0f, 0.0f, 0.0f),
	//			ETag::ePlayer, ELayer::ePlayer
	//		);
	//		AddTask(jump);

	//		jumping = true;
	//	}
	//}

	int currentStage = CGameManager::StageNo();
	bool pose = CTaskManager::Instance()->IsPaused();

	// ステージ1,2中のみタイマーを動かす
	if (currentStage == 1 || currentStage == 2)
	{
		// ポーズ中でなければタイマーを動かす
		if (!pose)
		{
			// ゲーム時間の更新
			static float starttime = 1.0f;
			starttime -= Time::DeltaTime();
			if (starttime <= 0.0f)
			{
				if (mTime > 0) {
					static float time = 1.0f;
					time -= Time::DeltaTime();
					if (time <= 0)
					{
						mTime--;
						time = 1.0f;
					}

					// タイマーが0になったら終了
					if (mTime < 0)
					{
						//mTime = 500;
						CGameManager::GameOver();
					}
				}
			}
		}

		mpScore->Score(CVanguard::GetScore() + CBlueMedal::GetScore());
		mpTime->Time(mTime);
		mpTime->Render();
		mpScore->Render();
	}
	////////////////////////////////////////////////////////////////////////////////////

	//// ステージ番号の監視
	CDebugPrint::Print("StageNo:%d\n", CGameManager::StageNo());
	//// ソルジャーの数の監視
	//CDebugPrint::Print("count:%d\n", CEnemyManager::GetEnemyCount());
}