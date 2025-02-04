#include "CSikaku.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#include "CColliderMesh.h"

#include <cstdlib>

void CSikaku::Collision(CCollider* m, CCollider* o)
{
	if (CCollider::Collision(m, o)) {
		mEnabled = false;
		// プレイヤーの位置も移動させる
		//CPlayer::Instance()->Position(CPlayer::Instance()->Position() + IDOU);
	}
}

void CSikaku::Collision()
{
	mColliderMesh1.ChangePriority();
	//コライダの優先度変更
}


CSikaku::CSikaku(CModel* model, const CVector& position, const CVector& rotation, const CVector& scale)

{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定

	//タスクの優先度を設定
	mPriority = (int)TaskPriority::eBackground;

	//背景のモデルデータ読み込み
	mpModel = new CModel;
	mpModel->Load("res\\aoiro sikaku1.obj", "res\\aoiro sikaku.mtl");

	//読み込んだ背景のモデルデータでコライダを作成
	mColliderMesh1.Set(this, &mMatrix, mpModel);
}

CSikaku::~CSikaku()
{
	delete mpModel;
	mpModel = nullptr;
}

void CSikaku::Update()
{
	//行列を更新
	CTransform::Update();
}

//bool CSikaku::IsPlayerOnTop() const
//{
//	return CPlayer::Instance();
//}
