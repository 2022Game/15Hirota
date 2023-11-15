#ifndef CENEMYWEAPON_H
#define CENEMYWEAPON_H
#include "CObjectBase.h"
class CCharaBase;

// �I�u�W�F�N�g�p��

class CEnemyWeapon : public CObjectBase
{
public:
	CEnemyWeapon();

	virtual ~CEnemyWeapon();

	virtual void AttackMtx(const CMatrix* mtx);

	//�@�U���J�n
	virtual void AttackStart();

	// �U���I��
	virtual void AttackEnd();

	// ����̏����L�����N�^�[��ݒ�
	void SetOwner(CCharaBase* owner);
	// ����̏����L�����N�^�[���擾
	CCharaBase* GetOwner() const;

protected:
	// �������q�b�g�����I�u�W�F�N�g��ǉ�
	void AddAttackHitObj(CObjectBase* obj);
	// ���łɍU�����q�b�g���Ă���I�u�W�F�N�g���ǂ���
	bool IsAttackHitObj(CObjectBase* obj) const;
	const CMatrix* mpAttachMtx;

	// �U�����q�b�g�ς݂̃I�u�W�F�N�g���X�g
	std::list<CObjectBase*> mAttackHitObjects;

	// �A�C�e���̏����L�����N�^�[
	CCharaBase* mOwner;

};
#endif