#ifndef CSEESAW_H
#define CSEESAW_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

class CModel;

// �V�[�\�[
class CSeesaw : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="reactionTag">�G���Ɣ�������I�u�W�F�N�g</param>
	/// <param name="reactionLayer">�G���Ɣ������郌�C���[</param>
	CSeesaw(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);

	// �f�X�g���N�^
	~CSeesaw();

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
	// �V�[�\�[���f��
	CModel* mpSeesawModel;
	// �V�[�\�[�Z���^�[�R���C�_�[
	CColliderMesh* mpCenterCol;
	// �V�[�\�[���C�g�R���C�_�[
	CColliderMesh* mpRightCol;
	// �V�[�\�[���t�g�R���C�_�[
	CColliderMesh* mpLeftCol;

	// ��Ԋ֘A
	// �V�[�\�[�̏��
	enum class EState
	{
		eIdle,	// �ҋ@���
		eRight,	// �E�ɌX�����
		eLeft,	// ���ɌX�����
		eReturn,// ���ɖ߂����
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// �E�ɌX���X�V����
	void UpdateRight();
	// ���ɌX���X�V����
	void UpdateLeft();
	// ���ɖ߂��X�V����
	void UpdateReturn();
	// ���݂̏��
	EState mState;

	// �x�N�g���֘A
	// �ړ����x
	CVector mMoveSpeed;
	// �ʒu��ݒ肷��
	CVector mStartPos;
	// ������]�l
	CQuaternion mDeafaultRot;

	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// ��]�����p�x��ێ�����ϐ�
	float mRotationAngle;
	// ��]�J�n���̊p�x
	float mRotateStartAngle;
	// ��]�I�����̊p�x
	float mRotateEndAngle;
	// �o�ߎ��Ԍv���p
	float mElpasedTime;

	// �Z���^�[�R���C�_�[�ɏՓ˂��Ă��邩
	bool mIsCenterCol;
	// ���C�g�R���C�_�[�ɏՓ˂��Ă��邩
	bool mIsRightCol;
	// ���t�g�R���C�_�[�ɏՓ˂��Ă��邩
	bool mIsLeftCol;

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;
};
#endif