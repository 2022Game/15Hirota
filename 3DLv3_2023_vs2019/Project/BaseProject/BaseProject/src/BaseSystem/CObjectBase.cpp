#include "CObjectBase.h"
#include "CCollider.h"

// �R���X�g���N�^
CObjectBase::CObjectBase(ETag tag, ETaskPriority prio, int sortOrder, ETaskPauseType pause)
	: CTask(prio, sortOrder, pause)
	, mTag(tag)
	, mIsEnableCol(true)
{
}

// �f�X�g���N�^
CObjectBase::~CObjectBase()
{
}

// �I�u�W�F�N�g�^�O���擾
ETag CObjectBase::Tag() const
{
	return mTag;
}

// �Փ˔�����s�����ݒ�
void CObjectBase::SetEnableCol(bool isEnable)
{
	mIsEnableCol = isEnable;
}

// �Փ˔�����s�����ǂ���
bool CObjectBase::IsEnableCol() const
{
	return mIsEnableCol;
}

// �Փˏ���
void CObjectBase::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}