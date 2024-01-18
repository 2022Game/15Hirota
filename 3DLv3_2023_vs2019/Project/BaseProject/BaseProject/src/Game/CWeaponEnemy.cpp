#include "CWeaponEnemy.h"

CWeaponEnemy::CWeaponEnemy()
	:CObjectBase(ETag::eEnemyWeapon, ETaskPriority::eEnemyWeapon)
	, mpAttachMtx(nullptr)
{

}

CWeaponEnemy::~CWeaponEnemy()
{

}

// �Ǐ]����s��̐ݒ�
void CWeaponEnemy::AttachMtx(const CMatrix* mtx)
{
	mpAttachMtx = mtx;
}

// �Ǐ]����s����擾
const CMatrix* CWeaponEnemy::GetAttachMtx() const
{
	if (mpAttachMtx == nullptr) return nullptr;
	return &mAttachCurrentMtx;
}

// �Ǐ]����s��̒l���X�V
void CWeaponEnemy::UpdateAttachMtx()
{
	if (mpAttachMtx == nullptr) return;
	// ���݂̍s��̏�Ԃ������o�ϐ��̍s��փR�s�[
	mAttachCurrentMtx = *mpAttachMtx;
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

// ����̏����L�����N�^�[��ݒ�
void CWeaponEnemy::SetOwner(CCharaBase* owner)
{
	mOwner = owner;
}

// ����̏����L�����N�^�[���擾
CCharaBase* CWeaponEnemy::GetOwner() const
{
	return mOwner;
}

// �U�����q�b�g�����I�u�W�F�N�g��ǉ�
void CWeaponEnemy::AddAttackHitObj(CObjectBase* obj)
{
	mAttackHitObjects.push_back(obj);
}

// ���łɍU�����q�b�g���Ă���I�u�W�F�N�g���ǂ���
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