//エイリアンクラスのインクルード
#include "CItem1.h"
#include "CApplication.h"
#include "CCollisionManager.h"

#define OBJ "res\\12190_Heart_v1_L3.obj"	//モデルのファイル
#define MTL "res\\12190_Heart_v1_L3.mtl"	//モデルのマテリアルファイル
#define VELOCITY CVector(0.0f, 0.0f, 0.5f)	//移動速度
#define ROTATION_YV	CVector(0.0f, 0.0f, 0.5f) //回転速度

#define HP 3 //HPの初期値は3

CItem1::CItem1()
	:CItem1(CVector(0.0f,0.0f,0.0f),CVector(0.0f,0.0f,0.0f),CVector(0.0f,1.0f,1.0f))
{
}

//CItem1(位置, 回転, スケール)
CItem1::CItem1(const CVector& pos, const CVector& rot, const CVector& scale)
	//奥行き
	: mLine(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f))
	//縦
	, mLine2(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f))
	//横
	, mLine3(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f))
{
	CTransform::Update(pos, rot, scale);

	mpModel = new CModel();
	mpModel->Load(OBJ, MTL);

	//アイテムのHPを設定する
	mHp = HP;
}

//更新処理
void CItem1::Update() {
	//変換行列の更新
	CTransform::Update();
	//位置の更新
	mRotation = mRotation + VELOCITY * mMatrixRotate;
	//UI設定
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());
}

void CItem1::Collision()
{
	//コライダの優先度変更
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mLine3, COLLISIONRANGE);
}

void CItem1::Collision(CCollider* m, CCollider* o) {
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::ELINE://線分コライダ
		//相手のコライダが三角コライダの時
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//位置の更新(mPosition + adjust)
				mPosition = mPosition + adjust;
				//行列の更新
				CTransform::Update();
			}
		}
		break;
	}
}

//#include "CItem1.h"
//#include "CEffect.h"
//#include "CCollisionManager.h"
//
////回転速度
//#define VELOCITY CVector(0.0f, 0.0f, 0.5f)
//
//#define VELOCITY_I CVector(0.0f,0.0f,0.5f);
//
//void CItem1::Collision()
//{
//	//コライダの優先度変更
//	mCollider1.ChangePriority();
//	mCollider2.ChangePriority();
//	mCollider3.ChangePriority();
//	//衝突処理を実行
//	CCollisionManager::Instance()->Collision(&mCollider1, COLLISIONRANGE);
//	CCollisionManager::Instance()->Collision(&mCollider2, COLLISIONRANGE);
//	CCollisionManager::Instance()->Collision(&mCollider3, COLLISIONRANGE);
//}
//
//void CItem1::Collision(CCollider* m, CCollider* o)
//{
//	//相手のコライダタイプの判定
//	switch (o->Type())
//	{
//	case CCollider::ESPHERE: //球コライダの時
//		//コライダのmとyが衝突しているか判定
//		if (CCollider::Collision(m, o)) {
//			//エフェクト生成
//			//new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
//			//衝突している時は無効にする
//			//mEnabled = false;
//		}
//		break;
//	case CCollider::ETRIANGLE: //三角コライダの時
//		CVector adjust; //調整値
//		//三角コライダと球コライダの衝突判定
//		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
//		{	//衝突しない位置まで戻す
//			mPosition = mPosition + adjust;
//		}
//		break;
//	}
//
//}
//
////コンストラクタ
////CEnemy(モデル, 位置, 回転, 拡縮)
//CItem1::CItem1(CModel* model, const CVector& position,
//	const CVector& rotation, const CVector& scale)
//	: mCollider1(this, &mMatrix, CVector(0.0f, 0.0f, 10.0f), 0.7f)
//{
//
//	//モデル、位置、回転、拡縮を設定する
//	mpModel = model;	//モデルの設定
//	mPosition = position;	//位置の設定
//	mRotation = rotation;	//回転の設定
//	mScale = scale;	//拡縮の設定
//}
//
////更新処理
//void CItem1::Update() {
//	//行列を更新
//	CTransform::Update();
//	mRotation = mRotation + VELOCITY * mMatrixRotate;
//
//	//位置を移動
//	//mPosition = mPosition + VELOCITY * mMatrixRotate;
//}