#ifndef CKICK_H
#define CKICK_H
#include "CObjectBase.h"
#include "CEnemyWeapon.h"
#include "CColliderSphere.h"
#include "CModel.h"

class CKick :public CEnemyWeapon
{
public:
	CKick();
	~CKick();

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

	void Update();
	void Render();

private:
	// 攻撃判定用のコライダー
	CColliderSphere* mpAttackCol;
};
#endif