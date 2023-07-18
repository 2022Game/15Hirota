#include "CEnemy.h"
#include "CEnemyManager.h"

//コンストラクタ
CEnemy::CEnemy()
	: CCharacter3(1)
{
	//CEnemy生成時にCEnemyManagerのリストに自身を追加
	CEnemyManager::Instance()->Add(this);
}

//デストラクタ
CEnemy::~CEnemy()
{
	//CEnemy破棄時にCEnemyManagerのリストから自身を取り除く
	CEnemyManager::Instance()->Remove(this);
}

////更新処理
//void CEnemy::Update() {
//
//	//プレイヤーのポインタが0以外の時
//	CPlayer* player = CPlayer::Instance();
//	if (player != nullptr)
//	{
//		//プレイヤーまでのベクトルを求める
//		CVector vp = player->Position() - mPosition;
//		//左ベクトルとの内積を求める
//		float dx = vp.Dot(mMatrixRotate.VectorX());
//		//上ベクトルとの内積を求める
//		float dy = vp.Dot(mMatrixRotate.VectorY());
//		//前ベクトルとの内積を求める
//		float dz = vp.Dot(mMatrixRotate.VectorZ());
//		//X軸のズレが2.0以下
//		if (-2.0f < dx && dx < 2.0f && 0.0f < dz && dz <= 30.0f)
//		{
//			//Y軸のズレが2.0以下
//			if (-2.0f < dy && dy < 2.0f)
//			{
//				//弾を発射します
//				CBullet* bullet = new CBullet();
//				bullet->Set(0.1f, 1.5f);
//				bullet->Position(
//					CVector(0.0f, 0.0f, 10.0f) * mMatrix);
//				bullet->Rotation(mRotation);
//				bullet->Update();
//			}
//		}
//	}
//	//HPが0以下の時　撃破
//	if (mHp <= 0)
//	{
//		mHp--;
//		//15フレーム毎にエフェクト
//		if (mHp % 15 == 0)
//		{
//			//エフェクト生成
//			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
//		}
//		//下降させる
//		mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
//		CTransform::Update();
//		return;
//	}
//
//	//目標地点までのベクトルを求める
//	CVector vp = mPoint - mPosition;
//	//課題
//	float dx = vp.Dot(mMatrixRotate.VectorX());	//左ベクトルとの内積を求める
//	float dy = vp.Dot(mMatrixRotate.VectorY());	//上ベクトルとの内積を求める
//	const float margin = 0.1f;
//	//左右方向へ回転
//	if (dx > margin)
//	{
//		mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f); //左へ回転
//	}
//	else if (dx < -margin)
//	{
//		//課題
//		mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f); //右へ回転
//	}
//	//上下方向へ回転
//	if (dy > margin)
//	{
//		mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f); //上へ回転
//	}
//	else if (dy < -margin)
//	{
//		//課題
//		mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f); //下へ回転
//	}
//	//機体前方へ移動する						//*
//	Position(Position() + MatrixRotate().VectorZ() * VELOCITY);
//	CTransform::Update();	//行列更新
//
//	//およそ3秒毎に目標地点を更新
//	int r = rand() % 180;	//rand()は整数の乱数を返す
//	//% 180 は180で割った余りを求める
//	if (r == 0)
//	{
//		if (player != nullptr)
//		{
//			mPoint = player->Position();
//		}
//		else
//		{
//			mPoint = mPoint * CMatrix().RotateY(45);
//		}
//	}
//}