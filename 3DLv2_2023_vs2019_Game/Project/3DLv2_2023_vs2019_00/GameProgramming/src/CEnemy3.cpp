#include "CEnemy3.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#include "CPlayer.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define OBJ "res\\Alien Animal.obj"	//モデルのファイル
#define MTL "res\\Alien Animal.mtl"	//モデルのマテリアルファイル

#define HP 3	//耐久値
#define VELOCITY 0.11f	//速度
//移動速度
#define FOV_ANGLE 45.0f //視野の角度(ー角度+角度も出)
#define FOV_LENGTH 5.0f//視野の角度

CModel CEnemy3::sModel;	//モデルデータ作成

//デフォルトコンストラクタ
CEnemy3::CEnemy3()
	: CCharacter3(1)
	, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
	, mHp(HP)
	,mState(EState::EIDLE)
{
	//モデルが無いときは読み込む
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &sModel;
}


//CEnemy(位置, 回転, 拡縮)
CEnemy3::CEnemy3(CModel* model, const CVector& position, const CVector& rotation,const CVector& scale)
	: CEnemy3()	//デフォルトコンストラクタを実行する
{
	//位置、回転、拡縮を設定する
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
	CTransform::Update();	//行列の更新
	//目標地点の設定
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
}

void CEnemy3::UpdateIdle()
{
	//プレイヤーを見つけたら、追跡状態へ移行
	if (IsFoundPlayer())
	{
		mState = EState::ECHASE;
	}
}

void CEnemy3::UpdateChase()
{
	//プレイヤーを見失ったら、待機状態へ移行
	if (!IsFoundPlayer())
	{
		mState = EState::EIDLE;
	}
	else
	{
		/*CVector playerPos = CPlayer::Instance()->Position();
		float distance = (playerPos - Position().Length());*/
		// プレイヤーのポインタが0以外の時
		CPlayer* player = CPlayer::Instance();
		//目標地点までのベクトルを求める
		CVector vp = mPoint - mPosition;
		//課題
		float dx = vp.Dot(mMatrixRotate.VectorX());	//左ベクトルとの内積を求める
		float dy = vp.Dot(mMatrixRotate.VectorY());	//上ベクトルとの内積を求める

		CVector forwrd = mMatrixRotate.VectorX().Normalize();
		CVector forwed1 = mMatrixRotate.VectorY().Normalize();

		const float margin = 0.1f;
		//左右方向へ回転
		if (dx > margin)
		{
			mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f); //左へ回転
		}
		else if (dx < -margin)
		{
			//課題
			mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f); //右へ回転
		}
		//上下方向へ回転
		if (dy > margin)
		{
			mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f); //上へ回転
		}
		else if (dy < -margin)
		{
			//課題
			mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f); //下へ回転
		}
		//機体前方へ移動する
		mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
		CTransform::Update();	//行列更新

		//およそ3秒毎に目標地点を更新
		int r = rand() % 180;	//rand()は整数の乱数を返す
		//% 180 は180で割った余りを求める
		if (r == 0)
		{
			if (player != nullptr)
			{
				mPoint = player->Position();
			}
			else
			{
				mPoint = mPoint * CMatrix().RotateY(45);
			}
		}
	}
}

void CEnemy3::UpdateAttack()
{
	//プレイヤーのポインタが0以外の時
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		//プレイヤーまでのベクトルを求める
		CVector vp = player->Position() - mPosition;
		//左ベクトルとの内積を求める
		float dx = vp.Dot(mMatrixRotate.VectorX());
		//上ベクトルとの内積を求める
		float dy = vp.Dot(mMatrixRotate.VectorY());
		//前ベクトルとの内積を求める
		float dz = vp.Dot(mMatrixRotate.VectorZ());
		//X軸のズレが2.0以下
		if (-2.0f < dx && dx < 2.0f && 0.0f < dz && dz <= 30.0f)
		{
			//Y軸のズレが2.0以下
			if (-2.0f < dy && dy < 2.0f)
			{
				//弾を発射します
				CBullet* bullet = new CBullet();
				bullet->Set(0.1f, 1.5f);
				bullet->Position(
					CVector(0.0f, 0.0f, 10.0f) * mMatrix);
				bullet->Rotation(mRotation);
				bullet->Update();
			}
			else
			{
				mState = EState::ECHASE;
			}
		}
	}
}

//更新処理
void CEnemy3::Update()
{

	switch (mState)
	{
	case EState::EIDLE:
		UpdateIdle();
			break;
	case EState::ECHASE:
		UpdateChase();
		break;
	case EState::EATTACK:
		UpdateAttack();
		break;
	}

	
	//HPが0以下の時　撃破
	if (mHp <= 0)
	{
		mHp--;
		//15フレーム毎にエフェクト
		if (mHp % 15 == 0)
		{
			//エフェクト生成
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		//下降させる
		mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
		CTransform::Update();
		return;
	}


	//

	//視野角の実装
	//実装するときはエネミーに実装
	//浪指先生のコード
	CVector a, bVector;
	float b = a.Dot(bVector);

	CVector playerPos = CPlayer::Instance()->Position();	//プレイヤー座標
	CVector enemyPos = Position();	//エネミー座標

	//エネミーからプレイヤーまでのベクトルを求める
	//目的地までのベクトル = 目的地 - 開始位置
	CVector EP = (playerPos - enemyPos).Normalize();

	//エネミーの正面方向のベクトル
	CVector forward = MatrixRotate().VectorZ().Normalize();

	//正面方向のベクトルとプレイヤーまでのベクトルの
	//内積を取り、角度を求める
	float dot = forward.Dot(EP);
	if (dot >= cosf(45.0f * (M_PI / 180.0f)))	//45度は調整可能
	{
		M_PI;
		//プレイヤー -45度～45度の範囲にいる
		//ディグリー　　　　ラジアン
		//180度 　　　= 　　3.14ラジアン(π)
		//360度	　　　= 　　6.28ラジアン(2π)
		//1度		  =     0.0174ラジアン

		//大きかったらその範囲に居る

		//敵からプレイヤーまでの距離
		float distance = (playerPos - enemyPos).Length();
		if (distance <= 100.0f) //調整可能
		{
			//敵からプレイヤーまでの距離が範囲内
			printf("範囲内に入りました");
		}
		else
		{
			printf("範囲外");
		}
	}

	//角度をディグリーからラジアンに変換
	//radian = degree * (M_PI / 180.0f)

	//角度をラジアンからディグリーに変換
	//degree = radian * (180.0f / M_PI)
	//[180 / M_PI]は
	//1ラジアンの時のディグリーの角度を求めている

	//

	if (IsFoundPlayer())
	{
		printf("FoundPlayer:%s\n", IsFoundPlayer() ? "true" : "false");
	}

	////行列を更新
	//CTransform::Update();
	////位置を移動
	//mPosition = mPosition + VELOCITY * mMatrixRotate;

}

//衝突処理
//Collision(コライダ1, コライダ2)
void CEnemy3::Collision(CCollider* m, CCollider* o)
{
	//相手のコライダタイプの判定
	switch (o->Type())
	{
	case CCollider::ESPHERE: //球コライダの時
		//コライダのmとoが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			//エフェクト生成
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//衝突している時は無効にする
			//mEnabled = false;
			mHp--;	//ヒットポイントの減算
		}
		break;
	case CCollider::ETRIANGLE: //三角コライダの時
		CVector ad;
		//コライダのmとoが衝突しているか判定
		if (CCollider::CollisionTriangleSphere(o, m, &ad)) {
			//撃破で地面に衝突すると無効
			if (mHp <= 0)
			{
				mEnabled = false;
			}
		}
		break;
	}
}

void CEnemy3::Collision()
{
	//コライダの優先度変更
	mCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}

//プレイヤーを見つけたかどうか
bool CEnemy3::IsFoundPlayer() const
{
	CVector playerPos = CPlayer::Instance()->Position();
	CVector enemyPos = Position();

	//視野の角度の判定
	//自身からプレイヤーまでのベクトルを取得(要正規化)
	CVector EP = (playerPos - enemyPos).Normalize();

	//敵自身の正面方向のベクトルを取得(要正規化)
	CVector forwrd = MatrixRotate().VectorZ().Normalize();

	//正面方向のベクトルとプレイヤーまでのベクトルの
	//内積空角度を求める
	float dot = forwrd.Dot(EP);
	//求めた角度が視野角度外であれば、falseを返す
	if (dot < cosf(FOV_ANGLE * M_PI / 180.0f)) return false;

	//視野の距離の判定
	//自身からプレイヤーまでの距離を求める
	float distance = (playerPos - enemyPos).Length();

	//変更した//
	const float chaseRenge = 100.0f;

	//求めた距離菓子や距離より遠いならば,falseを返す
	if (distance > FOV_LENGTH) return false;

	//視野角度都市や距離の判定を通ったのでtrueを返す
	return true;
}