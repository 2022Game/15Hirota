#ifndef CSPIKYBALL_H
#define CSPIKYBALL_H
#include "CObjectBase.h"
#include "CWeapon.h"
#include "CColliderSphere.h"
#include "CTrailEffect.h"
#include "CModel.h"

// とげとげボールクラス
class CSpikyBall : public CWeapon
{
public:
	CSpikyBall(const CVector& pos, const CVector& dir,
		float speed, float distance);
	~CSpikyBall();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した自身のコライダー</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// 攻撃開始
	void AttackStart() override;

	// 攻撃終了
	void AttackEnd() override;

	// 武器の行列を取得
	CMatrix Matrix() const override;

	// 現在のスピード設定
	void SetSpeed(float newSpeed);
	//　現在の飛距離設定
	void SetDistance(float newDistance);

	// 更新処理
	void Update();
	// 描画処理
	void Render();

private:
	// とげとげボールのモデル
	CModel* mpSpikyBallModel;
	// 攻撃判定用のコライダー
	CColliderSphere* mpAttackCol;

	const CMatrix* mpRightHandMtx;

	// 重力によるY軸の移動速度
	float mMoveSpeedY;
	// とげとげボールの軌跡のエフェクト
	CTrailEffect* mpTrailEffect;
	// とげとげボールのコライダー
	CColliderSphere* mpSpherer;
	CVector mMoveSpeedXZ;
	// 移動速度
	float mMoveSpeed;
	// 飛距離
	float mFlyingDistance;
	// 現在の飛距離
	float mCurrentFlyingDistance;

	bool mHasLaunched;
};
#endif