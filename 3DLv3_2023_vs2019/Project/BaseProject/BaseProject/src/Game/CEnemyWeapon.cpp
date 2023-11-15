#include "CEnemyWeapon.h"

CEnemyWeapon::CEnemyWeapon()
	:CObjectBase(ETag::eEnemyWeapon, ETaskPriority::eWeapon)
	, mpAttachMtx(nullptr)
{
}

CEnemyWeapon::~CEnemyWeapon()
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

void CEnemyWeapon::AttackMtx(const CMatrix* mtx)
{
	mpAttachMtx = mtx;
}

void CEnemyWeapon::AttackStart()
{
	mAttackHitObjects.clear();
}

void CEnemyWeapon::AttackEnd()
{
}

void CEnemyWeapon::AddAttackHitObj(CObjectBase* obj)
{
	mAttackHitObjects.push_back(obj);
}

bool CEnemyWeapon::IsAttackHitObj(CObjectBase* obj) const
{
	// ���Ƀ��X�g�ɒǉ�����Ă��邩���m�F����
	auto find = std::find
	(
		mAttackHitObjects.begin(),
		mAttackHitObjects.end(),
		obj
	);
	return find != mAttackHitObjects.end();
}