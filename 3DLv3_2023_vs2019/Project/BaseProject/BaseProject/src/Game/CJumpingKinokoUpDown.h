#ifndef CJUMPINGKINOKOUPDOWN_H
#define CJUMPINGKINOKOUPDOWN_H

#include "CModel.h"
#include "CColliderMesh.h"
#include "CObjectBase.h"

// �v���C���[�𒵂˂�����L�m�R(�㉺)
class CJumpingKinokoUpDown : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�傫��</param>
	/// <param name="move">�ړ�����</param>
	/// <param name="moveTime">�ړ�����</param>
	CJumpingKinokoUpDown(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime, ETag reactionTag, ELayer reactionLayer);
	// �f�X�g���N�^
	~CJumpingKinokoUpDown();

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
	// �ړ�����
	CVector mMoveVec;
	// ���̈ʒu
	CVector mDefaultPos;

	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// �ړ����Ԍv���p
	float mMoveElapsedTime;
	// �ړ�����
	float mMoveTime;
	// �Փ˂��Ă��邩
	bool mIsCollisionPlayer;

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;
};
#endif