#include "CCharaBase.h"

CCharaBase::CCharaBase(ETag tag, ETaskPriority prio)
	: CObjectBase(tag, prio)
{
}

CCharaBase::~CCharaBase()
{
}

// ��_���[�W����
void CCharaBase::TakeDamage(int damage)
{
	
}

// �ő�X�e�[�^�X���擾
const CharaStatus& CCharaBase::MaxStatus() const
{
	return mCharaMaxStatus;
}

// ���݃X�e�[�^�X���擾
const CharaStatus& CCharaBase::Status() const
{
	return mCharaStatus;
}
