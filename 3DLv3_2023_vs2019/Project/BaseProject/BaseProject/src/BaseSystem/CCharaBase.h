#pragma once
#include "CObjectBase.h"
#include "CharaStatus.h"

/// <summary>
/// �L�����N�^�[�̃x�[�X�N���X
/// </summary>
class CCharaBase : public CObjectBase
{
public:
	CCharaBase(ETag tag, ETaskPriority prio, int sortOrder = 0,
		ETaskPauseType pause = ETaskPauseType::eGame);
	virtual ~CCharaBase();

	// ��_���[�W����
	// damage == �󂯂�_���[�W
	virtual void TakeDamage(int damage);

	// �񕜏���
	// recovery == ��
	virtual void TakeRecovery(int recovery);
	
	// ���G����
	virtual void TakeInvincible();

	// �U���̓A�b�v����
	virtual void TakeAttackPotion(int attack);


	// �ő�X�e�[�^�X���擾
	const CharaStatus& MaxStatus() const;
	// ���݂̃X�e�[�^�X���擾
	const CharaStatus& Status() const;

protected:
	CharaStatus mCharaMaxStatus;	// �ő�X�e�[�^�X
	CharaStatus mCharaStatus;		// ���݃X�e�[�^�X
};
