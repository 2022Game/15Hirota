#ifndef CJUMPINGKINOKO_H
#define CJUMPINGKINOKO_H

#include "CModel.h"
#include "CColliderMesh.h"
#include "CObjectBase.h"

// �v���C���[�𒵂˂�����L�m�R
class CJumpingKinoko : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="reactionTag">���A�N�V�����^�O</param>
	/// <param name="reactionLayer">���A�N�V�������C���[</param>
	CJumpingKinoko(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);

	// �f�X�g���N�^
	~CJumpingKinoko();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂����Ƃ��̎��g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// ���f���E�f�ފ֘A
	// ���˂�L�m�R���f��
	CModel* mpKinoko;
	// ���˂�L�m�R���f���̃R���C�_�[
	CColliderMesh* mpColliderMesh;

	// ��Ԋ֘A
	// ���˂�L�m�R�̏��
	enum class EState
	{
		eIdle,	// �ҋ@���
		eBounce,// ���˂�������
	};
	// �ҋ@��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// ���˂������Ԃ̌ΐS����
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

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;
};
#endif