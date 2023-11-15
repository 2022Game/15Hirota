#ifndef CENEMYWEAPON_H
#define CENEMYWEAPON_H
#include "CObjectBase.h"
class CCharaBase;

// オブジェクト継承

class CEnemyWeapon : public CObjectBase
{
public:
	CEnemyWeapon();

	virtual ~CEnemyWeapon();

	virtual void AttackMtx(const CMatrix* mtx);

	//　攻撃開始
	virtual void AttackStart();

	// 攻撃終了
	virtual void AttackEnd();

	// 武器の所持キャラクターを設定
	void SetOwner(CCharaBase* owner);
	// 武器の所持キャラクターを取得
	CCharaBase* GetOwner() const;

protected:
	// 剛撃がヒットしたオブジェクトを追加
	void AddAttackHitObj(CObjectBase* obj);
	// すでに攻撃がヒットしているオブジェクトかどうか
	bool IsAttackHitObj(CObjectBase* obj) const;
	const CMatrix* mpAttachMtx;

	// 攻撃がヒット済みのオブジェクトリスト
	std::list<CObjectBase*> mAttackHitObjects;

	// アイテムの所持キャラクター
	CCharaBase* mOwner;

};
#endif