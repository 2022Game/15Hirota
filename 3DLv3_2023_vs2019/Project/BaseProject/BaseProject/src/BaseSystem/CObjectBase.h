#pragma once
#include "CTask.h"
#include "CTransform.h"
#include "ObjectTag.h"

class CCollider;

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
	CObjectBase(ETag tag = ETag::eNone, ETaskPriority prio = ETaskPriority::eDefault);

	// �f�X�g���N�^
	virtual ~CObjectBase();

	// �I�u�W�F�N�g�^�O���擾
	ETag Tag() const;

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	virtual void Collision(CCollider* self, CCollider* other, const CVector& adjust);

private:
	ETag mTag;	//�I�u�W�F�N�g���ʗp�̃^�O
};