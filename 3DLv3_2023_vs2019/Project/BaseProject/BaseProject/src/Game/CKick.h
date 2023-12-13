#ifndef CKICK_H
#define CKICK_H
#include "CObjectBase.h"
#include "CWeaponEnemy.h"
#include "CColliderSphere.h"
#include "CModel.h"
#include "CXCharacter.h"

class CKick :public CWeaponEnemy
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
	//CMatrix Matrix() const override;

	void Update();
	void Render();

private:
	CModelX* mpModel;				//モデルデータ
	// 攻撃判定用のコライダー
	CColliderSphere* mpAttackCol;

	const CMatrix* mpAttachMtx;	// くっつける行列のポインター
	CMatrix mAttachMtx;			// くっつける行列の本体
};
#endif