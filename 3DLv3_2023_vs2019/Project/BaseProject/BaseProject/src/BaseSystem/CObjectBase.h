#pragma once
#include "CTask.h"
#include "CTransform.h"
#include "ObjectTag.h"
#include "CCollider.h"

/// <summary>
/// 3D��Ԃɔz�u����I�u�W�F�N�g�̃x�[�X�N���X
/// </summary>
class CObjectBase : public CTask, public CTransform
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="tag">�I�u�W�F�N�g�̃^�O</param>
	/// <param name="prio">�^�X�N�̗D��x</param>
	CObjectBase(ETag tag = ETag::eNone,
		ETaskPriority prio = ETaskPriority::eDefault,
		int sortOrder = 0,
		ETaskPauseType pause = ETaskPauseType::eDefault);

	// �f�X�g���N�^
	virtual ~CObjectBase();

	// �I�u�W�F�N�g�^�O���擾
	ETag Tag() const;

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂������̏��</param>
	virtual void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

private:
	ETag mTag;	//�I�u�W�F�N�g���ʗp�̃^�O
};
