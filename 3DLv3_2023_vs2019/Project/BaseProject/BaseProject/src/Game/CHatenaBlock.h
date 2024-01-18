#ifndef CHATENABLOCK_H
#define CHATENABLOCK_H

#include "CRideableObject.h"
#include "CModel.h"
#include "CColliderSphere.h"

class CRecoveryObject;
class CInvincible;
class CSound;

// �n�e�i�u���b�N
class CHatenaBlock : public CRideableObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�X�P�[��</param>
	/// <param name="reactionTag">��������I�u�W�F�N�g�^�O</param>
	/// <param name="reactionLayer">��������I�u�W�F�N�g���C���[</param>
	CHatenaBlock(const CVector& pos, const CVector& scale,
		ETag reactionTag, ELayer reactionLayer);

	// �f�X�g���N�^
	~CHatenaBlock();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�e�[�W�J�n���̈ʒu��ݒ�
	void SetStartPosition(const CVector& pos);

	// �X�V
	void Update() override;

	// �`��
	void Render();

private:

	// ���f���E�f�ފ֘A
	// �n�e�i�u���b�N�̃��f��
	CModel* mpModel;
	// �n�e�i�u���b�N�̃R���C�_�[
	CColliderSphere* mpColliderSphere;

	// �񕜃A�C�e���̃|�C���^�[
	CRecoveryObject* mpHeart;
	// ���G�A�C�e���̃|�C���^�[
	CInvincible* mpStar;
	// �u���b�N��@��������SE
	CSound* mpHitBlockSE;
	

	// ��Ԋ֘A
	// �n�e�i�u���b�N�̏��
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

	// ���݂̏��
	EState mState;

	
	// �x�N�g���֘A
	// �ړ����x
	CVector mMoveSpeed;
	// �n�e�i�u���b�N�̏����ʒu�̕ۑ�
	CVector mStartPos;

	
	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �t�F�[�h����
	float mFadeTime;
	// �҂�����
	float mWaitTime;
	// �Փ˂��Ă��邩
	bool mIsCollision;
	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃��C���[
	ELayer mReactionLayer;
};
#endif