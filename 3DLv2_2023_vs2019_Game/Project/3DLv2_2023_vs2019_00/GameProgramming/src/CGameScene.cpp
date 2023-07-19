#include "CGameScene.h"
#include "CPlayer.h"
#include "CAlien.h"
#include "CSikakuGimmick.h"
#include "CItem1.h"
#include "CColliderMesh.h"
#include "CField.h"
#include "CSceneManager.h"

//コンストラクタ
CGameScene::CGameScene()
	:CSceneBase(EScene::eGame)
{
}

//デストラクタ
CGameScene::~CGameScene()
{
}

//シーン読み込み
void CGameScene::Load()
{
	//ここでタイトル画面に必要な
	//リソースの読み込みやクラスの生成を行う

	//背景作成
	AddTask(new CField());

	//四角ギミックはCSikakuGimmick内にまとめる
	//AddTask(new CSikakuGimmick());

	//プレイヤー作成
	CPlayer* player = new CPlayer();
	player->Scale(CVector(0.25f, 0.25f, 0.25f));
	player->Position(CVector(0.0f, 2.0f, 0.0f));
	player->Rotation(CVector(0.0f, 180.0f, 0.0f));

	//アイテム作成
	AddTask(new CAlien(CVector(10.0f,0.0f,0.0f),CVector(),CVector(1.0f,1.0f,1.0f)));

	//プレイヤー作成
	AddTask(new CPlayer(CVector(0.0f,5.0f,0.0f), CVector(), CVector(1.0f,1.0f,1.0f)));

	//アイテム作成
	AddTask(new CItem1(CVector(20.0f,0.0f,0.0f), CVector(), CVector(1.0f,1.0f,1.0f)));

	//ビルボードの生成
	//new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);

	////三角コライダの確認
	//mColliderTriangle.Set(nullptr, nullptr
	//	, CVector(-50.0f, 0.0f, -50.0f)
	//	, CVector(-50.0f, 0.0f, 50.0f)
	//	, CVector(50.0f, 0.0f, -50.0f));
	//mColliderTriangle2.Set(nullptr, nullptr
	//	, CVector(-50.0f, 0.0f, 50.0f)
	//	, CVector(50.0f, 0.0f, 50.0f)
	//	, CVector(50.0f, 0.0f, -50.0f));

	//背景モデルから三角コライダを生成
	//親インスタンスと親行列はなし
	//mColliderMesh1.Set(nullptr, nullptr, &mModel_Item);
}

//シーンの更新処理
void CGameScene::Update()
{
	CPlayer* player = CPlayer::Instance();
	if (player == nullptr)return;

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = player->Position() + CVector(0.2f, 1.5f, -3.5f) * player->MatrixRotate();
	//注視点を求める
	c = player->Position();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f) * player->MatrixRotate();
	//カメラの設定
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());

	if (player->IsDeath())
	{
		CSceneManager::Instance()->LoadScene(EScene::eTitle);
	}
}