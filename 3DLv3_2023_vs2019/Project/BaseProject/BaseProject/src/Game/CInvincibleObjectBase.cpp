#include "CInvincibleObjectBase.h"

CInvincibleObjectBase::CInvincibleObjectBase()
	: CObjectBase(ETag::eItemInvincible, ETaskPriority::eItem)
{
}

CInvincibleObjectBase::~CInvincibleObjectBase()
{

}

// ���G�A�C�e�����q�b�g�����I�u�W�F�N�g��ǉ�
void CInvincibleObjectBase::AddAttachHitObjInvincible(CObjectBase* obj)
{
	mInvincible.push_back(obj);
}


// ���G�J�n
void CInvincibleObjectBase::InvincibleStart()
{
	mInvincible.clear();
}

// ���G�I��
void CInvincibleObjectBase::InvincibleEnd()
{

}


bool CInvincibleObjectBase::IsAttachHitObjInvincible(CObjectBase* obj) const
{
	// ���łɃ��X�g�ɒǉ�����Ă��邩�m�F������
	auto find = std::find(
		mInvincible.begin(),
		mInvincible.end(),
		obj
	);
	return find != mInvincible.end();
}