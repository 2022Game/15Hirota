#include "CWeaponEnemy.h"

CWeaponEnemy::CWeaponEnemy()
	:CObjectBase(ETag::eEnemyWeapon, ETaskPriority::eEnemyWeapon)
	, mpAttachMtx(nullptr)
{

}

CWeaponEnemy::~CWeaponEnemy()
{

}

// �U���J�n
void CWeaponEnemy::AttackStart()
{
	mAttackHitObjects.clear();
}

// �U���I��
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

// �U�����q�b�g�����I�u�W�F�N�g��ǉ�
void CWeaponEnemy::AddAttackHitObj(CObjectBase* obj)
{
	mAttackHitObjects.push_back(obj);
}

bool CWeaponEnemy::IsAttackHitObj(CObjectBase* obj) const
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