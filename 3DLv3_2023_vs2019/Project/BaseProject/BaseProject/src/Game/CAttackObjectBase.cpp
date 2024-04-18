#include "CAttackObjectBase.h"

CAttackObjectBase::CAttackObjectBase()
	:CObjectBase(ETag::eAttackObject,ETaskPriority::eItem)
{

}

CAttackObjectBase::~CAttackObjectBase()
{

}

void CAttackObjectBase::AttackStart()
{
	mAttackObjects.clear();
}

void CAttackObjectBase::AttackEnd()
{
}

void CAttackObjectBase::AddAttachHitAttackObj(CObjectBase* obj)
{
	mAttackObjects.push_back(obj);
}

bool CAttackObjectBase::IsAttachHitAttackObj(CObjectBase* obj) const
{
	// ���łɃ��X�g�ɒǉ�����Ă��邩�m�F������
	auto find = std::find
	(
		mAttackObjects.begin(),
		mAttackObjects.end(),
		obj
	);
	return find != mAttackObjects.end();
}