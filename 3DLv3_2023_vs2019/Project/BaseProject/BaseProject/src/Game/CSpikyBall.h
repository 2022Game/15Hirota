#ifndef CSPIKYBALL_H
#define CSPIKYBALL_H
#include "CObjectBase.h"
#include "CWeapon.h"
#include "CColliderSphere.h"
#include "CTrailEffect.h"
#include "CModel.h"

// �Ƃ��Ƃ��{�[���N���X
class CSpikyBall : public CWeapon
{
public:
	CSpikyBall(const CVector& pos, const CVector& dir,
		float speed, float distance);
	~CSpikyBall();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// �U���J�n
	void AttackStart() override;

	// �U���I��
	void AttackEnd() override;

	// ����̍s����擾
	CMatrix Matrix() const override;

	// ���݂̃X�s�[�h�ݒ�
	void SetSpeed(float newSpeed);
	//�@���݂̔򋗗��ݒ�
	void SetDistance(float newDistance);

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// �Ƃ��Ƃ��{�[���̃��f��
	CModel* mpSpikyBallModel;
	// �U������p�̃R���C�_�[
	CColliderSphere* mpAttackCol;

	const CMatrix* mpRightHandMtx;

	// �d�͂ɂ��Y���̈ړ����x
	float mMoveSpeedY;
	// �Ƃ��Ƃ��{�[���̋O�Ղ̃G�t�F�N�g
	CTrailEffect* mpTrailEffect;
	// �Ƃ��Ƃ��{�[���̃R���C�_�[
	CColliderSphere* mpSpherer;
	CVector mMoveSpeedXZ;
	// �ړ����x
	float mMoveSpeed;
	// �򋗗�
	float mFlyingDistance;
	// ���݂̔򋗗�
	float mCurrentFlyingDistance;

	bool mHasLaunched;
};
#endif