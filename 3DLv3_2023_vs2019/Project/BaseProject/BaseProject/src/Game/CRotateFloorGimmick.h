#ifndef CROTATEFLOORGIMMICK_H
#define CROTATEFLOORGIMMICK_H

#include "CRideableObject.h"
#include "CColliderMesh.h"
class CPlayer;
class CModel;

// �}���I���̉�]�M�~�b�N(�v���C���[����)
class CRotateFloorGimmick : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="reactionTag">�G���Ɣ�������I�u�W�F�N�g�̃^�O</param>
	/// <param name="reactionLayer">�G���Ɣ�������I�u�W�F�N�g�̃��C���[</param>
	CRotateFloorGimmick(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);

	// �f�X�g���N�^
	~CRotateFloorGimmick();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit)override;

	// ��Ԃ�؂�ւ���
	void ChangeRotationState();

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:

	// ���f���E�f�ފ֘A
	// ��]���鏰�̃��f��
	CModel* mpRotateFloor;
	// ��]���鏰�̕\���̃R���C�_�[
	CColliderMesh* mpFrontFloorCol;
	// ��]���鏰�̗����̃R���C�_�[
	CColliderMesh* mpBackFloorCol;


	// ��Ԋ֘A
	// ��]���鏰�̏��
	enum class EState
	{
		Idle,		// �ҋ@���
		Rotate,
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// ��]��Ԃ̍X�V����
	void UpdateRotate();
	// ���݂̏��
	EState mState;


	// �x�N�g���֘A
	// �ړ����x
	CVector mMoveSpeed;
	// �ʒu��ݒ肷��
	CVector mStartPos;
	// ������]�l
	CQuaternion mDefaultRot;


	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �Փ˂��Ă��邩
	bool mIsCollision;
	// �v���C���[���W�����v���������ǂ���
	bool mIsJumping;
	// ���̏��
	bool mNextRotateIsRotate2;
	// ��]�����p�x��ێ�����ϐ�
	float mRotationAngle;
	// ��]�J�n���̊p�x
	float mRotateStartAngle;
	// ��]�I�����̊p�x
	float mRotateEndAngle;
	// �o�ߎ��Ԃ��v������悤
	float mElapsedTime;
	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;

	//�v���C���[����������
	bool IsFoundPlayer() const;
};
#endif