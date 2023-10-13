#include "CGameScene.h"
#include "CSceneManager.h"
#include "CField.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CCamera.h"
#include "CMaria.h"

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

	CPlayer* player = new CPlayer();
	player->Scale(1.0f, 1.0f, 1.0f);	//モデルの大きさを後で大きくしておく

	CMaria* maria = new CMaria();
	maria->Scale(1.0f, 1.0f, 1.0f);	//モデルの大きさを後で大きくしておく
	maria->Position(0.0f, 20.0f, 0.0f);

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
