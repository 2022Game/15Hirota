#include "CGameScene.h"
#include "CPlayer.h"
#include "CAlien.h"
#include "CSikakuGimmick.h"
#include "CItem1.h"
#include "CEnemy3.h"
#include "CColliderMesh.h"
#include "CField.h"

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

	//プレイヤー作成
	CPlayer* player = new CPlayer();
	player->Scale(CVector(0.25f, 0.25f, 0.25f));
	player->Position(CVector(0.0f, 2.0f, 0.0f));
	player->Rotation(CVector(0.0f, 180.0f, 0.0f));

	//アイテム作成
	AddTask(new CAlien(CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f)));





	//モデルファイルの入力
	mModel.Load(MODEL_OBJ);		//プレイヤー
	mModel1.Load(MODEL_ITEM1);	//アイテム1
	mBackGround.Load(MODEL_BACKGROUND);
	//CMatrix matrix;
	//matrix.Print();	//表示確認用

	//mEye = CVector(1.0f, 2.0f, 3.0f);

	mPlayer.Model(&mModel);
	

	//ITEM1のモデルの読み込み
	/*mModel_Item.Load(MODEL_ITEM1);
	new CItem1(&mModel_Item, CVector(-50.0f, 0.0f, -10.0f),
		CVector(270.0f, 0.0f, -90.0f), CVector(0.09f, 0.09f, 0.09f));*/


	//C5モデルの読み込み
	mModelC5.Load(MODEL_C5);
	//敵機のインスタンス作成
	/*new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -100.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy(&mModelC5, CVector(20.0f, 10.0f, -130.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));*/


	mModelAlien.Load(MODEL_ALIEN);
	new CEnemy3(&mModelAlien, CVector(-50.0f, 0.0f, 2.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));

	new CEnemy3(&mModelAlien, CVector(-100.0f, 0.0f, -50.0f),
		CVector(), CVector(0.1f, 0.1f, 0.1f));
	//エイリアンモデルの読み込み
	/*mModelAlien.Load(MODEL_ALIEN);
	new CEnemy3(&mModelAlien, CVector(100.0f, 0.0f, 0.0f),
		CVector(0.0f,0.0f,0.0f), CVector(0.1f, 0.1f, 0.1f));*/

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
	mColliderMesh.Set(nullptr, nullptr, &mBackGround);
	//mColliderMesh1.Set(nullptr, nullptr, &mModel_Item);

	/*new CEnemy3(CVector(-5.0f, 1.0f, -10.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy3(CVector(5.0f, 1.0f, -10.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));*/

	//四角ギミックはCSikakuGimmick内にまとめる
	mpSikakuGimmick = new CSikakuGimmick();

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
}