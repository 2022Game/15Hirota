#include "CEnemy.h"
#include "CEffect.h"
#include "CCollisionManager.h"
#include "CPlayer.h"
#define _USE_MATH_DEFINES
#include <math.h>
//#define M_PI        3.14159265358979323846264338327950288

//移動速度
#define VELOCITY CVector(0.0f, 0.0f, 0.09f)
#define FOV_ANGLE 45.0f //視野の角度(ー角度+角度も出)
#define FOV_LENGTH 5.0f//視野の角度

void CEnemy::Collision()
{
	//コライダの優先度変更
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mCollider2, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mCollider3, COLLISIONRANGE);
}

void CEnemy::Collision(CCollider* m, CCollider* o)
{
	//相手のコライダタイプの判定
	switch (o->Type())
	{
	case CCollider::ESPHERE: //球コライダの時
		//コライダのmとyが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			//エフェクト生成
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//衝突している時は無効にする
			//mEnabled = false;
		}
		break;
	case CCollider::ETRIANGLE: //三角コライダの時
		CVector adjust; //調整値
		//三角コライダと球コライダの衝突判定
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{	//衝突しない位置まで戻す
			mPosition = mPosition + adjust;
		}
		break;
	}

}

//コンストラクタ
//CEnemy(モデル, 位置, 回転, 拡縮)
CEnemy::CEnemy(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 0.8f)
	, mCollider2(this, &mMatrix, CVector(0.0f, 5.0f, 20.0f), 0.8f)
	, mCollider3(this, &mMatrix, CVector(0.0f, 5.0f, -20.0f), 0.8f)
{

	//モデル、位置、回転、拡縮を設定する
	mpModel = model;	//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
}

//プレイヤーを見つけたかどうか
bool CEnemy::IsFoundPlayer() const
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

	//求めた距離菓子や距離より遠いならば,falseを返す
	if (distance > FOV_LENGTH) return false;

	//視野角度都市や距離の判定を通ったのでtrueを返す
	return true;
}

//更新処理
void CEnemy::Update() {

	//

	//視野角の実装
	//実装するときはエネミーに実装
	//浪指先生のコード
	CVector a,bVector;
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
		if (distance <= 5.0f) //調整可能
		{
			//敵からプレイヤーまでの距離が範囲内

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
		printf("FoundPlayer:%s\n",IsFoundPlayer()?"true":"false");
	}

	//行列を更新
	CTransform::Update();
	//位置を移動
	mPosition = mPosition + VELOCITY * mMatrixRotate;
}