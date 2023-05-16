//プレイヤークラスのインクルード
#include "CItem1.h"
#include "CApplication.h"
#include "CCollisionManager.h"
#include "CRectangle.h"

#define HP 100	//hp

#define GRAVITY CVector(0.0f,-0.2f,0.0f)	//重力加速度

#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //回転速度
#define VELOCITY CVector(0.0f, 0.0f, 0.3f) //移動速度
#define ROTATION_XV	CVector(2.0f, 0.0f, 0.0f) //回転速度

CItem1* CItem1::spInstance = nullptr;

int CItem1::sHp = 0;	//Hp


CItem1::CItem1()
	//: mLine(this, &mMatrix, CVector(0.0f, 3.5f, 2.5f), CVector(0.0f, 3.5f, -2.5f))		//前後
	//, mLine2(this, &mMatrix, CVector(0.0f, 6.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f))		//上下
	//, mLine3(this, &mMatrix, CVector(2.5f, 3.5f, 0.0f), CVector(-2.5f, 3.5f, 0.0f))	//左右
{
	//インスタンスの設定
	spInstance = this;
	sHp = HP;
}

//CPlayer(位置, 回転, スケール)
CItem1::CItem1(const CVector& pos, const CVector& rot, const CVector& scale)
{
	CTransform::Update(pos, rot, scale); //行列の更新
}

int CItem1::Hp()
{
	return sHp;
}

//更新処理
void CItem1::Update() {

	//変換行列の更新
	CTransform::Update();
	//UI設定
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());



	////重力処理
	//mVelocity = mVelocity + GRAVITY;
	//mPosition = mPosition + mVelocity;

	////移動処理
	//if (mPosition.Y() > 0.0f) {	//地面に接触していない
	//	mPosition = mPosition + mVelocity;
	//	mVelocity = mVelocity + GRAVITY;
	//}
	////地面に接触している場合は、位置を地面の上に固定する
	//if (mPosition.Y() <= 0.0f) {
	//	mPosition = CVector(mPosition.X(), 0.0f, mPosition.Z());
	//	mVelocity = CVector(mVelocity.X(), 0.0f, mVelocity.Z());
	//}

	//復活処理に使える

	////位置が画面外に出た場合は初期位置に戻す
	//if (mPosition.Y() < -10.0f)
	//{
	//	mPosition = CVector(0.0f, 0.0f, 0.0f);
	//	mVelocity = CVector(0.0f, 0.0f, 0.0f);
	//}
}

CItem1* CItem1::Instance()
{
	return spInstance;
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
			2;
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//位置の更新(mPosition + adjust)
				mPosition = mPosition + adjust;
				/*mVelocity = CVector(0.0f, 0.0f, 0.0f);*/
				//行列の更新
				CTransform::Update();
			}
			//else
			//{
			//	//重力処理
			//	mVelocity = GRAVITY;
			//}
		}
		break;
	}
}