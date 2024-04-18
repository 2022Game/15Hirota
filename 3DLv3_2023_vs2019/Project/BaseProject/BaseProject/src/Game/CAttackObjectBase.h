#ifndef CATTACKOBJECTBASE_H
#define CATTACKOBJECTBASE_H
#include "CObjectBase.h"
class CCharaBase;

// �I�u�W�F�N�g�p��
// �U���̓A�b�v�I�u�W�F�̃N���X
class CAttackObjectBase : public CObjectBase
{
public:
	CAttackObjectBase();
	~CAttackObjectBase();

	// �U���͏㏸�J�n
	virtual void AttackStart();
	// �U���͏㏸�I��
	virtual void AttackEnd();
protected:
	// �U���̓A�b�v�A�C�e�����q�b�g�����I�u�W�F�N�g��ǉ�
	void AddAttachHitAttackObj(CObjectBase* obj);
	// ���łɍU���̓A�b�v�A�C�e�����q�b�g���Ă���I�u�W�F�N�g��
	bool IsAttachHitAttackObj(CObjectBase* obj) const;

	// �U���̓A�b�v�ς݂̃I�u�W�F�N�g���X�g
	std::list<CObjectBase*> mAttackObjects;
};
#endif