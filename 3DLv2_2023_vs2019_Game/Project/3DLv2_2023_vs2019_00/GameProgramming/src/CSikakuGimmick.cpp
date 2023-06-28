#include "CSikakuGimmick.h"
#include "CTaskManager.h"
#include "CPlayer.h"
#include "CTransform.h"
#include "CVector.h"

#define MODEL_SIKAKU "res\\aoiro sikaku1.obj","res\\aoiro sikaku.mtl"

const CVector& CSikakuGimmick::Position()
{
	return mPosition;
}

void CSikakuGimmick::Velocity(const CVector& v)
{
	mVelocity = v;
}

void CSikakuGimmick::Init()
{
	//モデル読み込み
	mpSikakuModel = new CModel();
	mpSikakuModel->Load(MODEL_SIKAKU);

	CreateSikaku(CVector(-100.0f, 4.0f, 20.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	CreateSikaku(CVector(-120.0f, 8.0f, 20.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	CreateSikaku(CVector(-150.0f, 12.0f, 40.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	CreateSikaku(CVector(-190.0f, 17.0f, 60.0f), CVector(), CVector(5.0f, 3.0f, 3.0f));
	CreateSikaku(CVector(-150.0f, 20.0f, 40.0f), CVector(), CVector(5.0f, 3.0f, 3.0f));

}

void CSikakuGimmick::CreateSikaku(CVector& pos, CVector& rot, CVector& scale)
{
	if (mpSikakuModel == nullptr) return;

	// 四角を生成してリストに追加
	CSikaku* sikaku = new CSikaku(mpSikakuModel, pos, rot, scale);
	mSikakus.push_back(sikaku);
}

CSikakuGimmick::CSikakuGimmick()
{
	// 初期処理
	Init();

	// タスクマネージャーに自身を追加
	CTaskManager::Instance()->Add(this);
}

CSikakuGimmick::~CSikakuGimmick()
{
	// 四角のモデルデータを破棄
	if (mpSikakuModel != nullptr)
	{
		delete mpSikakuModel;
	}

	// 四角を破棄
	for (int i = 0; i < mSikakus.size(); i++)
	{
		delete mSikakus[i];
	}
	// 一応リストもクリアしておく
	mSikakus.clear();

	// タスクマネージャーから自身を取り除く
	CTaskManager::Instance()->Remove(this);
}

void CSikakuGimmick::Update()
{
	// プレイヤーが四角に接地したかどうかの判定
	for (int i = 0; i < mSikakus.size(); i++) {
		CSikaku* sikaku = mSikakus[i];
		if (sikaku != nullptr) {
			break;
		}
	}
}

	//// プレイヤーが四角に接地している場合の処理
	//if (playerGrounded) {
	//	// プレイヤーが四角に接地している場合の処理を実行
	//	CSikaku* sikaku;
	//	if (mPosition.Y() <= sikaku->EPLAYER) {
	//		mPosition = CVector(mPosition.X(), sikaku->EPLAYER, mPosition.Z());
	//		mVelocity = CVector(mVelocity.X(), 0.0f, mVelocity.Z());
	//	}
	//}
	//else {
	//	// プレイヤーが四角に接地していない場合の処理を実行
	//	false;
	//}