#include "CGameScene.h"
#include "CSceneManager.h"
#include "CField.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CCamera.h"
#include "CUnityChan.h"
#include "CFutao.h"

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
	//ここでゲーム中に必要な
	//リソースの読み込みやクラスの生成を行う

	new CField();

	// プレイヤー
	CPlayer* player = new CPlayer();
	player->Scale(1.0f, 1.0f, 1.0f);
	
	// ユニティちゃん
	CUnityChan* unity = new CUnityChan();
	unity->Scale(1.0f, 1.0f, 1.0f);
	unity->Position(0.0f, 20.0f, 0.0f);

	// 胡桃
	CFutao* futao = new CFutao();
	futao->Scale(1.0f, 1.0f, 1.0f);
	futao->Position(20.0f, 20.0f, 0.0f);

	CCamera* mainCamera = new CCamera
	(
		//CVector(5.0f, -15.0f, 180.0f),
		CVector(0.0f, 50.0f, 75.0f),
		player->Position()
	);
	mainCamera->SetFollowTargetTf(player);
}

//シーンの更新処理
void CGameScene::Update()
{
}
