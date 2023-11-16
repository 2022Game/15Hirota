#pragma once
#include "CObjectBase.h"
#include "CharaStatus.h"

/// <summary>
/// �L�����N�^�[�̃x�[�X�N���X
/// </summary>
class CCharaBase : public CObjectBase
{
public:
	CCharaBase(ETag tag, ETaskPriority prio);
	virtual ~CCharaBase();

	// ��_���[�W����
	// damage == �󂯂�_���[�W
	virtual void TakeDamage(int damage);

	// �ő�X�e�[�^�X���擾
	const CharaStatus& MaxStatus() const;		// �v���C���[�ő�X�e�[�^�X
	// ���݂̃X�e�[�^�X���擾
	const CharaStatus& Status() const;			// �v���C���[���݃X�e�[�^�X

	// �G�l�~�[�ő�X�e�[�^�X���擾
	const CharaStatus& MaxEnemyStatus() const;	// �G�l�~�[�ő�X�e�[�^�X
	// �G�l�~�[���݃X�e�[�^�X���擾
	const CharaStatus& EnemeyStatus() const;	// �G�l�~�[���݃X�e�[�^�X

protected:
	CharaStatus mCharaMaxStatus;	// �v���C���[�ő�X�e�[�^�X
	CharaStatus mCharaStatus;		// �v���C���[���݃X�e�[�^�X

	CharaStatus mCharaMaxStatus_Enemy;	// �G�̍ő�X�e�[�^�X
	CharaStatus mCharaStatus_Enemy;		// �G�̃X�e�[�^�X
};
