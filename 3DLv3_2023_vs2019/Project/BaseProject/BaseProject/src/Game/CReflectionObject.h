#ifndef CREFLECTIONOBJECT_H
#define CREFLECTIONOBJECT_H

#include "CModel.h"
#include "CCollider.h"
#include "CObjectBase.h"

// �v���C���[�𒵂˕Ԃ�����I�u�W�F�N�g�x�[�X
class CReflectionObject : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CReflectionObject(const CVector& pos, const CVector& scale, const CVector& rot);
	// �f�X�g���N�^
	~CReflectionObject();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փˏ��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;
protected:
	// ���f���f�ފ֘A
	// ���˕Ԃ�����I�u�W�F�N�g���f���f�[�^
	CModel* mpModel;
	// ���˕Ԃ�����I�u�W�F���Ƃ̃R���C�_�[
	CCollider* mpCollider1;
	CCollider* mpCollider2;

	// ��Ԋ֘A
	// ���˕Ԃ�����̏��
	enum class EState
	{
		eIdle,			// �ҋ@���
		eBounce,		// ���˂�������
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);

	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();

	// ���˂������Ԃ̊J�n����
	void BounceStart();
	// ���˂������Ԃ̍X�V����
	void UpdateBounce();
	// ���݂̏��
	EState mState;

	// �x�N�g���֘A
	// �����̑傫��
	CVector mStartScale;
	// �k�ޑ傫��
	CVector mShrinkScale;

	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// �Փ˂��Ă��邩
	bool mIsCollisionPlayer;
};
#endif