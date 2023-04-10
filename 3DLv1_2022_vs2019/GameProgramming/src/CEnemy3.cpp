#include "CEnemy3.h"

#define OBJ "res\\f16.obj"	//モデルのファイル
#define MTL "res\\f16.mtl"	//モデルのマテリアルファイル

//移動速度
#define VELOCITY CVector(0.0f,0.0f,0.09f)


CModel CEnemy3::sModel;	//モデルのデータ作成

//デフォルトコンストラクタ
CEnemy3::CEnemy3()
	:CCharacter3(1)
	, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4)
{
	//モデルがないときは読み込む
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &sModel;
}

//CEnemy3(位置、回転、拡縮)
CEnemy3::CEnemy3(const CVector& position, const CVector& rotation,
	const CVector& scale)
	:CEnemy3()	//デフォルトコンストラクタを実行する
{
	//位置、回転、拡縮を設定する
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;			//拡縮の設定
	CTransform::Update();	//行列の更新
}

//衝突処理
//COllision(コライダ１、コライダ２)
void CEnemy3::Collision(CCollider* m, CCollider* o)
{
	//相手のコライダタイプの判定
	switch (o->Type())
	{
	case CCollider::ESPHERE:	//球コライダの時
		//コライダのmとyが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			//エフェクト生成
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//衝突しているときは無効にする
			//mEnagled = false;
		}
		break;
	case CCollider::ETRIANGLE:	//△コライダの時
		CVector abjust;	//調整値
		//△コライダと球コライダの衝突判定
		if (CCollider::CollisionTriangleSphere(o, m, &abjust))
		{
			//衝突しない位置まで戻す
			mPosition = mPosition + abjust;
		}
		break;
	}
}

void CEnemy3::Collision()
{
	mCollider.ChangePriority();

	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}

//更新処理
void CEnemy3::Update()
{
	//行列を更新
	CTransform::Update();
	////位置を更新
	//mPosition = mPosition + VELOCITY * mMatrixRotate;
}