#include "CObjectBase.h"
#include "CCollider.h"

// �R���X�g���N�^
CObjectBase::CObjectBase(ETag tag, ETaskPriority prio)
	: CTask(prio)
	, mTag(tag)
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

// �Փˏ���
void CObjectBase::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}