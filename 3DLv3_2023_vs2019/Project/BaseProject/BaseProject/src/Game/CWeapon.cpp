#include "CWeapon.h"

CWeapon::CWeapon()
	: CObjectBase(ETag::eWeapon, ETaskPriority::eWeapon)
	, mpAttachMtx(nullptr)
{
}

CWeapon::~CWeapon()
{

}

// �Ǐ]����s��̐ݒ�
void CWeapon::AttachMtx(const CMatrix* mtx)
{
	mpAttachMtx = mtx;
}

// �Ǐ]����s����擾
const CMatrix* CWeapon::GetAttachMtx() const
{
	if (mpAttachMtx == nullptr) return nullptr;
	return &mAttachCurrentMtx;
}

// �Ǐ]����s��̒l���X�V
void CWeapon::UpdateAttachMtx()
{
	if (mpAttachMtx == nullptr) return;
	// ���݂̍s��̏�Ԃ������o�ϐ��̍s��փR�s�[
	mAttachCurrentMtx = *mpAttachMtx;
}

// �Ǐ]������
void CWeapon::DetachMtx()
{
	if (mpAttachMtx != nullptr)
	{
		mpAttachMtx = nullptr; // �������nullptr�ɐݒ�
	}
}

// �U���J�n
void CWeapon::AttackStart()
{
	// ���łɍU�����ł���΁A�T�C�h�J�n�����͎��s���Ȃ�
	if (mIsAttack) return;

	mIsAttack = true;
	mAttackHitObjects.clear();
}

// �U���I��
void CWeapon::AttackEnd()
{
	mIsAttack = false;
}

// �U�������ǂ���
bool CWeapon::IsAttack()
{
	return mIsAttack;
}

// ����̏����L�����N�^�[��ݒ�
void CWeapon::SetOwner(CCharaBase* owner)
{
	mOwner = owner;
}

// ����̏����L�����N�^�[���擾
CCharaBase* CWeapon::GetOwner() const
{
	return mOwner;
}

// �U�����q�b�g�����I�u�W�F�N�g��ǉ�
void CWeapon::AddAttackHitObj(CObjectBase* obj)
{
	mAttackHitObjects.push_back(obj);
}

// ���łɍU�����q�b�g���Ă���I�u�W�F�N�g���ǂ���
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