#ifndef CDISAPPEARFLOOR_H
#define CDISAPPEARFLOOR_H

#include "CRideableObject.h"
#include "CModel.h"
#include "CColliderMesh.h"

// �����鏰�N���X
class CDisappearFloor : public CRideableObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="scale">���̃X�P�[���l</param>
	/// <param name="reactionTag">�G���Ɣ�������I�u�W�F�N�g�̃^�O</param>
	/// <param name="reactionLayer">�G���Ɣ�������R���C�_�[�̃��C���[</param>
	CDisappearFloor(const CVector& pos, const CVector& scale,
		ETag reactionTag, ELayer reactionLayer);

	// �f�X�g���N�^
	~CDisappearFloor();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:

	// ���f���E�f�ފ֘A
	// �����鏰�̃��f��
	CModel* mpModel;
	// �����鏰�̃R���C�_�[
	CColliderMesh* mpColliderMesh;


	// ��Ԋ֘A
	// �����鏰�̏��
	enum class EState
	{
		Idle,	// �ҋ@���
		Fade,	// �t�F�[�h��
		Wait,	// �t�F�[�h��̑҂�
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// �t�F�[�h���̍X�V����
	void UpdateFade();
	// �t�F�[�h��̑҂�����
	void UpdateWait();
	// ���݂̏��
	EState mState;


	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �t�F�[�h����
	float mFadeTime;
	// �҂�����
	float mWaitTime;
	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;
};
#endif