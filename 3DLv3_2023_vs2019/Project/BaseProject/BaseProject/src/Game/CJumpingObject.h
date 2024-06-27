#ifndef CJUMPINGOBJECT_H
#define CJUMPINGOBJECT_H

#include "CModel.h"
#include "CCollider.h"
#include "CObjectBase.h"

// �v���C���[�𒵂˂�����I�u�W�F�N�gBase
class CJumpingObject : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot);
	// �f�X�g���N�^
	virtual ~CJumpingObject();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

protected:
	// ���f���E�f�ފ֘A
	// ���˂�I�u�W�F�N�g���f���f�[�^
	CModel* mpModel;
	// ���˂�I�u�W�F�N�g�̃R���C�_�[
	CCollider* mpCollider;

	// ��Ԋ֘A
	// ���˂����鏰�̏��
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
	// SPACE���������Ƃ��̌o�ߎ���
	float mJumpedElapsedTime;
	// �Փ˂��Ă��邩
	bool mIsCollisionPlayer;
};
#endif