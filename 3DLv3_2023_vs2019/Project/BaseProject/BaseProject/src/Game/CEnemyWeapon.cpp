#include "CEnemyWeapon.h"

CEnemyWeapon::CEnemyWeapon()
	:CObjectBase(ETag::eWeapon, ETaskPriority::eWeapon)
	, mpAttachMtx(nullptr)
{

}

CEnemyWeapon::~CEnemyWeapon()
{

}

// �U���J�n
void CEnemyWeapon::AttackStart()
{
	mAttackHitObjects.clear();
}

// �U���I��
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

// �U�����q�b�g�����I�u�W�F�N�g��ǉ�
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