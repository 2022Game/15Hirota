#include "CSikakuGimmick.h"
#include "CTaskManager.h"
#include "CPlayer.h"
#include "CTransform.h"
#include "CVector.h"

#define MODEL_SIKAKU "res\\aoiro sikaku1.obj","res\\aoiro sikaku.mtl"

#define MOVE CVector(0.1f,0.0f,0.0f)

const CVector& CSikakuGimmick::Position() const
{
	return mPosition;
}

void CSikakuGimmick::Position(const CVector& v)
{
	mPosition = v;
}

CSikakuGimmick::CSikakuGimmick()
	:mMoveCounter(0)
	, mMoveDirection(1)
	, mReverseMove(false)
{
	// 初期処理
	Init();

	// タスクマネージャーに自身を追加
	CTaskManager::Instance()->Add(this);
}

void CSikakuGimmick::Init()
{
	//モデル読み込み
	mpSikakuModel = new CModel();
	mpSikakuModel->Load(MODEL_SIKAKU);

	//別の四角
	CreateSikaku(CVector(-100.0f, 4.0f, 20.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	CreateSikaku(CVector(-120.0f, 8.0f, 20.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	CreateSikaku(CVector(-150.0f, 12.0f, 40.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	CreateSikaku(CVector(-190.0f, 17.0f, 60.0f), CVector(), CVector(5.0f, 3.0f, 3.0f));
	CreateSikaku(CVector(-150.0f, 20.0f, 40.0f), CVector(), CVector(5.0f, 3.0f, 3.0f));
	CreateSikaku(CVector(-60.0f, 2.0f, 20.0f), CVector(0.0f, 0.0f, -15.0f), CVector(6.0f, 4.0f, 6.0f));

	//ベクターを空にする
	mMovingSikakus.clear();
	//リストに追加
	mMovingSikakus.push_back(mSikakus[0]);

	//初期位置の四角
	CreateSikaku(CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(6.0f, 3.0f, 6.0f));
	CreateSikaku(CVector(0.0f, 0.0f, 52.75f), CVector(), CVector(6.0f, 3.0f, 6.0f));
	CreateSikaku(CVector(0.0f, 0.0f, 52.75f * 2), CVector(), CVector(6.0f, 3.0f, 6.0f));

	// すべての四角を移動対象に設定
	for (int i = 0; i < mSikakus.size(); i++) {
		if (i != 5 && i != 6 && i != 7 && i != 8) { // 一部の四角形を除外 例(&& != 1)
			mMovingSikakus.push_back(mSikakus[i]);
		}
	}
}

void CSikakuGimmick::CreateSikaku(CVector& pos, CVector& rot, CVector& scale)
{
	if (mpSikakuModel == nullptr) return;

	// 四角を生成してリストに追加
	CSikaku* sikaku = new CSikaku(mpSikakuModel, pos, rot, scale);
	mSikakus.push_back(sikaku);
}

CSikakuGimmick::~CSikakuGimmick()
{
	// 四角のモデルデータを破棄		後で削除
	if (mpSikakuModel != nullptr)
	{
		delete mpSikakuModel;
	}

	//移動する四角の破棄
	for (int i = 0; i < mMovingSikakus.size(); i++)
	{
		delete mMovingSikakus[i];
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
	// 追加: カウンターのチェック
	if (mMoveCounter < 100) {
		for (int i = 0; i < mMovingSikakus.size(); i++) {
			CSikaku* sikaku = mMovingSikakus[i];
			if (sikaku != nullptr) {
				sikaku->Position(sikaku->Position() + (MOVE * mMoveDirection)); // 位置を直接変更する
			}
		}
		mMoveCounter++;
	}
	else {
		mMoveDirection *= -1; // 移動方向を反転させる
		mMoveCounter = 0; // カウンターをリセット
	}

	// プレイヤーが四角に接地したかどうかの判定
	for (int i = 0; i < mSikakus.size(); i++) {
		CSikaku* sikaku = mSikakus[i];
		if (sikaku != nullptr) {
			break;
		}
	}
}