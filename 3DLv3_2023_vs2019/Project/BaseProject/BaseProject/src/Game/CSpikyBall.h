#ifndef CSPIKYBALL_H
#define CSPIKYBALL_H
#include "CObjectBase.h"
#include "CWeapon.h"
#include "CColliderSphere.h"
#include "CTrailEffect.h"
#include "CModel.h"

class CPlayer;

// �Ƃ��Ƃ��{�[���N���X
class CSpikyBall : public CWeapon
{
public:
	// �R���X�g���N�^
	CSpikyBall(const CVector& pos, const CVector& dir,
		float speed, float distance, float initialVelocityY);
	// �f�X�g���N�^
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
	// ���݂̔򋗗��ݒ�
	void SetDistance(float newDistance);
	// ���݂̈ʒu�ݒ�
	void SetPosition(CVector pos);
	// ���݂̈ʒu��Ԃ�
	CVector GetPosition() const;

	/// <summary>
	/// �\�����̃p�X��ݒ�
	/// </summary>
	/// <param name="startPosition">�e�̏����ʒu</param>
	/// <param name="initialVelocityXZ">XX���ʂł̏����x</param>
	/// <param name="initialVelocityY">���������̏����x</param>
	/// <param name="gravity">�d�͂̒l</param>
	/// <param name="timeStep">�|�C���g�Ԃ̎��ԃX�e�b�v</param>
	/// <param name="numPoints">�`�悷��|�C���g�̐�</param>
	/// <param name="color">�p�X�̐F</param>
	/// <param name="lineWidth">���C���̑���</param>
	void DrawProjectilePath(const CVector& startPosition, const CVector& initialVelocityXZ, float initialVelocityY, float gravity, float timeStep, int numPoints, const CColor& color, float lineWidth);

	// �e���̗\�����C����`�悷��֐�
	void RenderPredictionLine();

	// �v���C���[�̌�����ۑ�����֐�
	void PlayerVectorZ(const CPlayer& player);

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:

	// �Ƃ��Ƃ��{�[���̃��f��
	CModel* mpSpikyBallModel;
	// �U������p�̃R���C�_�[
	CColliderSphere* mpAttackCol;

	// �Ƃ��Ƃ��{�[���̋O�Ղ̃G�t�F�N�g
	CTrailEffect* mpTrailEffect;
	// �Ƃ��Ƃ��{�[���̃R���C�_�[
	CColliderSphere* mpSpherer;

	// XZ���ʂł̈ړ����x
	CVector mMoveSpeedXZ;
	// �e�̌��݂̈ʒu
	CVector mPosition;
	// �e�̏����ʒu
	CVector mInitialPos;
	// �v���C���[�̑O�����̌���
	CVector ForwardVectorZ;

	// �ړ����x
	float mMoveSpeed;
	// �򋗗�
	float mFlyingDistance;
	// ���݂̔򋗗�
	float mCurrentFlyingDistance;
	// �d�͂ɂ��Y���̈ړ����x
	float mMoveSpeedY;
};
#endif