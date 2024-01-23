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
#include "CBGMManager.h"

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
	CResourceManager::Load<CModel>("Field",					"Field\\GameStage(1).obj");					// 仮1面
	CResourceManager::Load<CModel>("FloorCol",				"Field\\GameStageFloor(1).obj");			// 仮1面の床
	CResourceManager::Load<CModel>("WallCol",				"Field\\GameStageWall(1).obj");				// 仮1面の壁
	CResourceManager::Load<CModel>("EnemyWallCol",			"Field\\GameStageEnemyWall(1).obj");		// 仮1面の敵の壁
	CResourceManager::Load<CModel>("FieldCube",				"Field\\Object\\cube.obj");					// 初期の四角のモデル
	CResourceManager::Load<CModel>("FieldCylinder",			"Field\\Object\\cylinder.obj");				// 初期の回転する四角モデル
	CResourceManager::Load<CModel>("GoalCube",				"Field\\Object\\GoalCube.obj");				// ゴールの土台
	CResourceManager::Load<CModel>("GoalPost",				"Field\\Object\\GoalPost.obj");				// ゴールのポスト
	CResourceManager::Load<CModel>("Stone1",				"Field\\Object\\Stone1.obj");				// 石1
	CResourceManager::Load<CModel>("Signboard",				"Field\\Object\\signboard.obj");			// 看板オブジェクト(ジャンプヒント)
	CResourceManager::Load<CModel>("HatenaBlock",			"Field\\Object\\hatena.obj");				// ハテナブロック(アイテム保有)
	CResourceManager::Load<CModel>("HatenaBlockAfter",		"Field\\Object\\UsedHatenaBlock.obj");		// ハテナブロック(アイテム不保有)
	CResourceManager::Load<CModel>("RengaBlock",			"Field\\Object\\RengaBlock.obj");			// レンガブロック
	CResourceManager::Load<CModel>("Number3",				"Field\\Object\\number3.obj");				// 三番目の床ブロック
	CResourceManager::Load<CModel>("Number2",				"Field\\Object\\number2.obj");				// 二番目の床ブロック
	CResourceManager::Load<CModel>("Number1",				"Field\\Object\\number1.obj");				// 一番目の床ブロック
	CResourceManager::Load<CModel>("Number0",				"Field\\Object\\number0.obj");				// 零番目の床


	// キャラクター関連
	CResourceManager::Load<CModelX>("Player",				"Character\\Monster1\\Monster_1.x");						// プレイヤー
	CResourceManager::Load<CModelX>("Soldier",				"Character\\Gas mask soldier\\GasMask_Soldier_Model.x");	// ソルジャー
	//CResourceManager::Load<CModelX>("UnityChan",			"Character\\UnityChan\\unitychan.x");						// ユニティちゃん
	CResourceManager::Load<CModelX>("Yukari",				"Character\\Yukari\\Yukari_Model.x");						// ゆかりさん
	CResourceManager::Load<CModelX>("Vanguard",				"Character\\Vanguard\\VanguardModel.x");						// ヴァンガード


	// アイテム関連
	CResourceManager::Load<CModel>("Bullet",				"Item\\Bullet1\\Bullet.obj");				// 弾
	CResourceManager::Load<CModel>("Gun_M1G",				"Item\\Gun_M1Garand\\Gun_M1Garand.obj");	// M1ガーランド(銃)
	CResourceManager::Load<CModel>("MajicSword",			"Item\\MajicSword\\MajicSword.obj");		// 魔法剣
	CResourceManager::Load<CModel>("Heart",					"Item\\StatusItem\\Heart.obj");				// 回復オブジェクト
	CResourceManager::Load<CModel>("Star",					"Item\\StatusItem\\Star.obj");				// 無敵オブジェクト
	CResourceManager::Load<CModel>("Medal",					"Item\\StatusItem\\Medal.obj");				// 得点オブジェクト


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


	// エフェクト関連
	CResourceManager::Load<CTexture>("Laser",				"Effect\\laser.png");				// 弾のエフェクト


	// BGM・SE関連
	CResourceManager::Load<CSound>("SlashSound",			"Sound\\SE\\slash.wav");				// 剣　スラッシュ
	CResourceManager::Load<CSound>("8bitKaifuku",			"Sound\\SE\\8bitkaifuku.wav");			// 8bitの回復音
	CResourceManager::Load<CSound>("8bitShot",				"Sound\\SE\\8bitshot.wav");				// 8bitの銃の音(ブロック用に使う)
	CResourceManager::Load<CSound>("8bitMutekiTime",		"Sound\\SE\\8bitMuteki.wav");			// 8bitの回復音(無敵用に使う)
	CResourceManager::Load<CSound>("CreatureGrowl1",		"Sound\\VOICE\\CreatureStereo5.wav");	// クリーチャーの唸り声1


	// ゲーム内のBGM
	CBGMManager::Instance()->Play(EBGMType::eGame);

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

	int enemyCount = CEnemyManager::GetSoldierCount();	// ソルジャーの数

	static bool Rising = false;

	if (enemyCount <= 0 && !Rising)	// ステージ番号
	{
		int currentStage = CGameManager::StageNo();
		if (currentStage == 0)
		{
			// 上昇するオブジェクト
			CRisingObject* rising = new CRisingObject
			(
				CVector(20.0f, 1.0f, -550.0f),
				CVector(0.5f, 0.5f, 0.5f),
				ETag::ePlayer, ELayer::ePlayer
			);
			CVector risingPos = CVector(20.0f, 1.0f, -550.0f);
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

	//// ステージ番号の監視
	//CDebugPrint::Print("StageNo:%d\n", CGameManager::StageNo());
	//// ソルジャーの数の監視
	//CDebugPrint::Print("count:%d\n", CEnemyManager::GetEnemyCount());
}