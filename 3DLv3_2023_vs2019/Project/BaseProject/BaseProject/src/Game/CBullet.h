#ifndef CBULLET_H
#define CBULLET_H
#include "CObjectBase.h"
#include "CWeaponEnemy.h"
#include "CColliderSphere.h"
#include "CModel.h"
#include "CEffect.h"

class CBullet :public CWeaponEnemy
{
public:
	CBullet();
	~CBullet();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した自身のコライダー</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// 武器の行列を取得
	CMatrix Matrix() const override;

	//// 攻撃開始
	//void AttackStart() override;

	//// 攻撃終了
	//void AttackEnd() override;

	void Update();
	void Render();
private:
	static CModel* mpBullet;
	// 攻撃判定用のコライダー
	CColliderSphere* mpAttackCol;

	// 弾丸の移動距離
	float mMoveDistance;

	CVector mPos;
};
#endif