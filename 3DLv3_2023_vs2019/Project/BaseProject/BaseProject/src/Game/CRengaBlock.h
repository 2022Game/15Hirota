#ifndef CRENGABLOCK_H
#define CRENGABLOCK_H


#include "CRideableObject.h"
#include "CModel.h"
#include "CColliderSphere.h"

// �����K�u���b�N
class CRengaBlock : public CRideableObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�X�P�[��</param>
	/// <param name="reactionTag">��������I�u�W�F�N�g�^�O</param>
	/// <param name="reactionLayer">��������I�u�W�F�N�g���C���[</param>
	CRengaBlock(const CVector& pos, const CVector& scale,
		ETag reactionTag, ELayer reactionLayer);

	// �f�X�g���N�^
	~CRengaBlock();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	void SetStartPosition(const CVector& pos);

	// �X�V
	void Update() override;

	// �`��
	void Render();

private:
	// �����K�u���b�N�̏��
	enum class EState
	{
		Idle,	// �ҋ@���
		Hit,	// �v���C���[���G�ꂽ���
		After,	// ����������
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// �����������̍X�V����
	void UpdateHit();
	// ����������̍X�V����
	void UpdateAfter();

	CModel* mpModel;		// �����K�u���b�N�̃��f��
	CColliderSphere* mpColliderSphere;	// �����K�u���b�N�̃R���C�_�[

	EState mState;	// ���݂̏��
	int mStateStep;	// ��ԓ��̃X�e�b�v

	ETag mReactionTag;		// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ELayer mReactionLayer;	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃��C���[

	float mFadeTime;	// �t�F�[�h����
	float mWaitTime;	// �҂�����
	bool mIsCollision;	// �Փ˂��Ă��邩

	CVector mMoveSpeed;
	CVector mStartPos;
};
#endif