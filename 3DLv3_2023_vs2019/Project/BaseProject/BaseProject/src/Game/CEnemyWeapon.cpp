#include "CEnemyWeapon.h"

CEnemyWeapon::CEnemyWeapon()
	:CObjectBase(ETag::eWeapon, ETaskPriority::eWeapon)
	, mpAttachMtx(nullptr)
{

}

CEnemyWeapon::~CEnemyWeapon()
{

}

// 攻撃開始
void CEnemyWeapon::AttackStart()
{
	mAttackHitObjects.clear();
}

// 攻撃終了
void CEnemyWeapon::AttackEnd()
{
}


void CEnemyWeapon::SetOwner(CCharaBase* owner)
{
	mOwner = owner;
}

CCharaBase* CEnemyWeapon::GetOwner() const
{
	return mOwner;
}

void CEnemyWeapon::AttachMtx(const CMatrix* mtx)
{
	mpAttachMtx = mtx;
}

// 攻撃がヒットしたオブジェクトを追加
void CEnemyWeapon::AddAttackHitObj(CObjectBase* obj)
{
	mAttackHitObjects.push_back(obj);
}

bool CEnemyWeapon::IsAttackHitObj(CObjectBase* obj) const
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