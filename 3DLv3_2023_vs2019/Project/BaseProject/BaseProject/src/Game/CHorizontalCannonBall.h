#ifndef CHORIZONTALCANNONBALL_H
#define CHORIZONTALCANNONBALL_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"

// ���������̑�C�̒e�N���X
class CHorizontalCannonBall : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="dir">�e�̌���</param>
	/// <param name="speed">�e�̑��x</param>
	/// <param name="distance">�e�̔򋗗�</param>
	CHorizontalCannonBall(const CVector& pos, const CVector& dir,
		float speed, float distance);
	// �f�X�g���N�^
	~CHorizontalCannonBall();

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
	// ��C�̒e���f��
	CModel* mpCannonBall;
	// �e�̃R���C�_�[
	CColliderSphere* mpSpherer;
	// �e�̏�R���C�_�[
	CColliderMesh* mpCannonCol;

	// ���
	// �e�̏��
	enum class EState
	{
		eIdle,	// �ʏ���
		eFall,	// �������
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);

	// �ʏ��Ԃ̍X�V����
	void UpdateIdle();
	// ������Ԃ̍X�V����
	void UpdateFall();
	// ���݂̏��
	EState mState;

	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// SPACE���������Ƃ��̌o�ߎ���
	float mJumpedElapsedTime;
	// �Փ˂��Ă��邩
	bool mIsCollisionPlayer;
	// �������Ă��邩�ǂ���
	bool mIsFall;
	// �ړ����x
	float mMoveSpeed;
	// �򋗗�
	float mFlyingDistance;
	// ���݂̔򋗗�
	float mCurrentFlyingDistance;
	// Y�������̏����x��ݒ肷��ϐ�
	float mVerticalSpeed;
	// ������̌o�ߎ���
	float mFallTime;

	float mBounceTime;
};
#endif