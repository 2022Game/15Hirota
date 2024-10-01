#ifndef CHORIZONTALCANNONBALL_H
#define CHORIZONTALCANNONBALL_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderSphere.h"

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

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:
	// ��C�̒e���f��
	CModel* mpCannonBall;
	// �e�̃R���C�_�[
	CColliderSphere* mpSpherer;
	// �ړ����x
	float mMoveSpeed;
	// �򋗗�
	float mFlyingDistance;
	// ���݂̔򋗗�
	float mCurrentFlyingDistance;
	// Y�������̏����x��ݒ肷��ϐ�
	float mVerticalSpeed;
};
#endif