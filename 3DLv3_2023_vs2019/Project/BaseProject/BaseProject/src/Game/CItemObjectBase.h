#ifndef CITEMOBJECTBASE_H
#define CITEMOBJECTBASE_H
#include "CObjectBase.h"
class CCharaBase;

// �I�u�W�F�N�g�p��

class CItemObjectBase : public CObjectBase
{
public:
	CItemObjectBase();
	virtual ~CItemObjectBase();

	// �񕜊J�n
	virtual void RecoverStart();
	// �񕜏I��
	virtual void RecoverEnd();

protected:
	// �񕜂��q�b�g�����I�u�W�F�N�g��ǉ�
	void AddAttachHitObj(CObjectBase* obj);
	// ���łɉ񕜂��q�b�g���Ă���I�u�W�F�N�g���ǂ���
	bool IsAttachHitObj(CObjectBase* obj) const;

	// �񕜃A�C�e���q�b�g�ς݂̃I�u�W�F�N�g���X�g
	std::list<CObjectBase*> mRecoveryObjects;
	
};
#endif