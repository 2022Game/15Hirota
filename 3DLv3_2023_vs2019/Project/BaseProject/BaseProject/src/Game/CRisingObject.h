#ifndef CRISINGOBJECT_H
#define CRISINGOBJECT_H

#include "CRideableObject.h"
#include "CModel.h"
#include "CColliderMesh.h"

// �㏸���鏰�N���X
class CRisingObject : public CRideableObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="scale">���̃X�P�[���l</param>
	/// <param name="reactionTag">�G���Ɣ�������I�u�W�F�N�g�̃^�O</param>
	/// <param name="reactionLayer">�G���Ɣ�������R���C�_�[�̃��C���[</param>
	CRisingObject(const CVector& pos, const CVector& scale,
		ETag reactionTag, ELayer reactionLayer);

	// �f�X�g���N�^
	~CRisingObject();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�e�[�W�J�n���̈ʒu��ݒ�
	void SetStartPosition(const CVector& pos);

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:

	// ���f���E�f�ފ֘A
	// �㏸���鏰�̃��f��
	CModel* mpModel;
	// �㏸���鏰�̃R���C�_�[
	CColliderMesh* mpColliderMesh;


	// ��Ԋ֘A
	// �㏸���鏰�̏��
	enum class EState
	{
		Idle,		// �ҋ@���
		Rising,		// �㏸���
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// �㏸��Ԃ̍X�V����
	void UpdateRising();
	// ���݂̏��
	EState mState;


	// �x�N�g���֘A
	// �ړ����x
	CVector mMoveSpeed;
	// �ʒu��ݒ�
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
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;
};
#endif