#include "CSikaku.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#include "CColliderMesh.h"

#define IDOU CVector(0.08f,0.0f,0.0f)

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
	:mReversed(false)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定
	mColliderMesh1.Set(this, &mMatrix, mpModel);
}

void CSikaku::Update()
{
	Position(Position() + IDOU); // 通常の移動

	//行列を更新
	CTransform::Update();
}

//bool CSikaku::IsPlayerOnTop() const
//{
//	return CPlayer::Instance();
//}
