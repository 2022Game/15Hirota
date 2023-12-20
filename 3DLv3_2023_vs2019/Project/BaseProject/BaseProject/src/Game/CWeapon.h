#ifndef CWEAPON_H
#define CWEAPON_H
#include "CObjectBase.h"
class CCharaBase;

// �I�u�W�F�N�g�p��

class CWeapon :public CObjectBase
{
public:
	CWeapon();
	virtual ~CWeapon();

	// �Ǐ]����s��̐ݒ�
	virtual void AttachMtx(const CMatrix* mtx);
	// �Ǐ]����s����擾
	const CMatrix* GetAttachMtx() const;
	// �Ǐ]����s��̒l���X�V
	void UpdateAttachMtx();

	//�@�U���J�n
	virtual void AttackStart();

	// �U���I��
	virtual void AttackEnd();

	// ����̏����L�����N�^�[��ݒ�
	void SetOwner(CCharaBase* owner);
	// ����̏����L�����N�^�[���擾
	CCharaBase* GetOwner() const;

protected:
	// �U�����q�b�g�����I�u�W�F�N�g��ǉ�
	void AddAttackHitObj(CObjectBase* obj);
	// ���łɍU�����q�b�g���Ă���I�u�W�F�N�g���ǂ���
	bool IsAttackHitObj(CObjectBase* obj) const;

	// �U�����q�b�g�ς݂̃I�u�W�F�N�g���X�g
	std::list<CObjectBase*> mAttackHitObjects;

	// �A�C�e���̏����L�����N�^�[
	CCharaBase* mOwner;
private:
	// �Ǐ]����s��̃|�C���^�[
	const CMatrix* mpAttachMtx;
	// �Ǐ]����s��̌��ݒn
	CMatrix mAttachCurrentMtx;

};
#endif