#include "CWeapon.h"

CWeapon::CWeapon()
	:CObjectBase(ETag::eWeapon, ETaskPriority::eWeapon)
	, mpAttachMtx(nullptr)
{
}

CWeapon::~CWeapon()
{

}

void CWeapon::SetOwner(CCharaBase* owner)
{
	mOwner = owner;
}

CCharaBase* CWeapon::GetOwner() const
{
	return mOwner;
}

void CWeapon::AttachMtx(const CMatrix* mtx)
{
	mpAttachMtx = mtx;
}

// �U���J�n
void CWeapon::AttackStart()
{
	mAttackHitObjects.clear();
}

// �U���I��
void CWeapon::AttackEnd()
{
}

// �U�����q�b�g�����I�u�W�F�N�g��ǉ�
void CWeapon::AddAttackHitObj(CObjectBase* obj)
{
	mAttackHitObjects.push_back(obj);
}

bool CWeapon::IsAttackHitObj(CObjectBase* obj) const
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