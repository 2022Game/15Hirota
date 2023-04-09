#include "CEnemy.h"

//移動速度
#define VELOCITY CVector(0.0f,0.0f,0.09f)

//コンストラクタ
//CEnemy(モデル、位置、回転、拡縮)
CEnemy::CEnemy(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 0.8f)
	, mCollider2(this, &mMatrix, CVector(0.0f,5.0f,20.0f), 0.8f)
	, mCollider3(this, &mMatrix, CVector(0.0f,5.0f,-20.f), 0.8f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model;		//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;			//拡縮の設定

}

//衝突処理
//Collision(コライダ１、コライダ２)
void CEnemy::Collision(CCollider* m, CCollider* o) {
	//相手のコライダタイプの判定
	switch (o->Type())
	{
	case CCollider::ESPHERE://球コライダの時
		//コライダのmとyが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			//エフェクト生成
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//衝突しているときは無効にする
			//mEnabled = false;
		}
		break;
	case CCollider::ETRIANGLE://△コライダの時
		CVector abjust;//調整値
		//△コライダと球コライダの衝突判定
		if (CCollider::CollisionTriangleSphere(o, m, &abjust))
		{	//衝突しない位置まで戻す
			mPosition = mPosition + abjust;
		}
		break;
	}
}

void CEnemy::Collision()
{
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();

	CCollisionManager::Instance()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mCollider2, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mCollider3, COLLISIONRANGE);
}

//更新処理
void CEnemy::Update() {
	//行列を更新
	CTransform::Update();
	//位置を更新
	mPosition = mPosition + VELOCITY * mMatrixRotate;
}