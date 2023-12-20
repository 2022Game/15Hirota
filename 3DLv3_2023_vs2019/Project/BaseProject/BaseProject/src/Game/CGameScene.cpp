#include "CGameScene.h"
#include "CSceneManager.h"
#include "CGameOverScene.h"
#include "CClearScene.h"
#include "CField.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "Csoldier.h"
#include "CCamera.h"
#include "CUnityChan.h"
#include "CYukari.h"
#include "CUIBase.h"
#include "CImage.h"
#include "CInput.h"
#include "CStone1.h"

//コンストラクタ
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
	,image(nullptr)
	,Clear(false)
{
	//image = new CImage("UI\\Clear.jpeg"); // CLEAR_IMAGE_PATH はクリア画像のファイルパス
	//image->SetSize(700, 500);
	//image->SetPos(CVector2(300.0f, 200.0f)); // 画像の表示位置を設定
	//image->SetUV(0, 1, 1, 0);
}

//デストラクタ
CGameScene::~CGameScene()
{
	if (image != nullptr)
	{
		delete image;
		image = nullptr;
	}
}

//シーン読み込み
void CGameScene::Load()
{
	//ここでゲーム中に必要な
	//リソースの読み込みやクラスの生成を行う

	// フィールド関連
	CResourceManager::Load<CModel>("Field","Field\\GameStage(1).obj");					// 仮1面
	CResourceManager::Load<CModel>("FloorCol", "Field\\GameStageFloor(1).obj");
	CResourceManager::Load<CModel>("WallCol", "Field\\GameStageWall(1).obj");			// 仮1面の壁
	CResourceManager::Load<CModel>("FieldCube", "Field\\Object\\cube.obj");				// 初期の四角のモデル
	CResourceManager::Load<CModel>("FieldCylinder", "Field\\Object\\cylinder.obj");		// 初期の回転する四角モデル
	CResourceManager::Load<CModel>("GoalCube", "Field\\Object\\GoalCube.obj");			// ゴールの土台
	CResourceManager::Load<CModel>("GoalPost", "Field\\Object\\GoalPost.obj");			// ゴールのポスト
	CResourceManager::Load<CModel>("Stone1", "Field\\Object\\Stone1.obj");				// 石1

	// キャラクター関連
	CResourceManager::Load<CModelX>("Player", "Character\\Monster1\\Monster_1.x");
	CResourceManager::Load<CModelX>("Soldier", "Character\\Gas mask soldier\\GasMask_Soldier_Model.x");
	//CResourceManager::Load<CModelX>("UnityChan", "Character\\UnityChan\\unitychan.x");
	//CResourceManager::Load<CModelX>("Yukari", "Character\\Yukari\\Yukari_Model.x");


	// アイテム関連
	CResourceManager::Load<CModel>("Bullet", "Item\\Bullet1\\Bullet.obj");
	CResourceManager::Load<CModel>("Gun_M1G", "Item\\Gun_M1Garand\\Gun_M1Garand.obj");
	CResourceManager::Load<CModel>("MajicSword", "Item\\MajicSword\\MajicSword.obj");

	// 背景色設定
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	CField* field = new CField();

	// モンスター(プレイヤー)
	CPlayer* player = new CPlayer();
	player->Scale(1.0f, 1.0f, 1.0f);
	player->Position(0.0f, 60.0f, -30.0f);
	
	//// ユニティちゃん
	//CUnityChan* unity = new CUnityChan();
	//unity->Scale(1.0f, 1.0f, 1.0f);
	//unity->Position(0.0f, 20.0f, 0.0f);

	//// ゆかりさん
	//CYukari* yukari = new CYukari();
	//yukari->Scale(1.0f, 1.0f, 1.0f);
	//yukari->Position(-100.0f, 200.0f, -100.0f);

	// ガスマスク兵士
	CSoldier* sol = new CSoldier();
	sol->Scale(1.0f, 1.0f, 1.0f);
	sol->Position(-100.0f, 150.0f, -100.0f);

	CSoldier* sol2 = new CSoldier();
	sol2->Scale(1.0f, 1.0f, 1.0f);
	sol2->Position(-50.0f, 150.0f, -100.0f);


	CCamera* mainCamera = new CCamera
	(
		//CVector(5.0f, -15.0f, 180.0f),
		CVector(0.0f, 90.0f, 75.0f),
		player->Position() + CVector(0.0f, 10.0f, 0.0f)
	);
	mainCamera->SetFollowTargetTf(player);
	// スフィアかメッシュぐらい
	mainCamera->AddCollider(field->GetWallCol());


	//// クリア画像のリソースをロード
	//CImage* clearImage = new CImage("UI\\Clear.jpeg"); // CLEAR_IMAGE_PATH はクリア画像のファイルパス
	//clearImage->SetSize(800, 500);
	//clearImage->SetPos(CVector2(300.0f, 300.0f)); // 画像の表示位置を設定
	//clearImage->SetUV(0, 1, 1, 0);
	// クリア画像のリソースをロード
}

//シーンの更新処理
void CGameScene::Update()
{
	// hp取得
	int currentHP = CPlayer::Instance()->GetHp();
	// 最大hp取得
	int maxHP = CPlayer::Instance()->GetMaxHp();

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