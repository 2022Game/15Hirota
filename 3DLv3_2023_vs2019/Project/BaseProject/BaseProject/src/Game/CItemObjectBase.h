#ifndef CITEMOBJECTBASE_H
#define CITEMOBJECTBASE_H
#include "CObjectBase.h"
class CCharaBase;

// �I�u�W�F�N�g�p��
// �񕜃A�C�e���I�u�W�F�̃N���X
class CItemObjectBase : public CObjectBase
{
public:
	CItemObjectBase();
	virtual ~CItemObjectBase();

	// �񕜊J�n
	virtual void RecoverStart();
	// �񕜏I��
	virtual void RecoverEnd();

	// �񕜖�ŉ񕜊J�n
	virtual void HealingStart();
	// �񕜖�ŉ񕜏I��
	virtual void HealingEnd();

protected:
	// �񕜂��q�b�g�����I�u�W�F�N�g��ǉ�
	void AddAttachHitObj(CObjectBase* obj);
	// ���łɉ񕜂��q�b�g���Ă���I�u�W�F�N�g���ǂ���
	bool IsAttachHitObj(CObjectBase* obj) const;

	// �񕜃A�C�e���q�b�g�ς݂̃I�u�W�F�N�g���X�g
	std::list<CObjectBase*> mRecoveryObjects;

	// �񕜖򂪃q�b�g�����I�u�W�F�N�g��ǉ�
	void AddAttachHitHealingObj(CObjectBase* obj);
	// ���łɉ񕜖���g�����I�u�W�F�N�g���ǂ���
	bool IsAttachHitHealingObj(CObjectBase* obj) const;

	// �񕜖�q�b�g�ς݂̃I�u�W�F�N�g���X�g
	std::list<CObjectBase*> mHealingObjects;
};
#endif