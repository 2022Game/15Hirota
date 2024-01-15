#include "CItemObjectBase.h"

CItemObjectBase::CItemObjectBase()
	: CObjectBase(ETag::eItem, ETaskPriority::eItem)
{
}

CItemObjectBase::~CItemObjectBase()
{

}

// �񕜂��q�b�g�����I�u�W�F�N�g��ǉ�
void CItemObjectBase::AddAttachHitObj(CObjectBase* obj)
{
	mRecoveryObjects.push_back(obj);
}

// �񕜊J�n
void CItemObjectBase::RecoverStart()
{
	mRecoveryObjects.clear();
}

// �񕜏I��
void CItemObjectBase::RecoverEnd()
{

}

bool CItemObjectBase::IsAttachHitObj(CObjectBase* obj) const
{
	// ���łɃ��X�g�ɒǉ�����Ă��邩�m�F������
	auto find = std::find
	(
		mRecoveryObjects.begin(),
		mRecoveryObjects.end(),
		obj
	);
	return find != mRecoveryObjects.end();
}