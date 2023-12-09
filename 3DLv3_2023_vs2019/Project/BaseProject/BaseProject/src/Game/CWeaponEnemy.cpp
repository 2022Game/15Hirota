#include "CWeaponEnemy.h"

CWeaponEnemy::CWeaponEnemy()
	:CObjectBase(ETag::eEnemyWeapon, ETaskPriority::eEnemyWeapon)
	, mpAttachMtx(nullptr)
{

}

CWeaponEnemy::~CWeaponEnemy()
{

}

// 攻撃開始
void CWeaponEnemy::AttackStart()
{
	mAttackHitObjects.clear();
}

// 攻撃終了
void CWeaponEnemy::AttackEnd()
{
}


void CWeaponEnemy::SetOwner(CCharaBase* owner)
{
	mOwner = owner;
}

CCharaBase* CWeaponEnemy::GetOwner() const
{
	return mOwner;
}

void CWeaponEnemy::AttachMtx(const CMatrix* mtx)
{
	mpAttachMtx = mtx;
}

// 攻撃がヒットしたオブジェクトを追加
void CWeaponEnemy::AddAttackHitObj(CObjectBase* obj)
{
	mAttackHitObjects.push_back(obj);
}

bool CWeaponEnemy::IsAttackHitObj(CObjectBase* obj) const
{
	// 既にリストに追加されているかを確認する
	auto find = std::find
	(
		mAttackHitObjects.begin(),
		mAttackHitObjects.end(),
		obj
	);
	return find != mAttackHitObjects.end();
}