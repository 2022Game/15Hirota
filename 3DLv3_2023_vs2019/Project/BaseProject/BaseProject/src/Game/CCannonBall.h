#ifndef CCANNONBALL_H
#define CCANNONBALL_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderSphere.h"

// ��C�̒e�N���X
class CCannonBall : public CObjectBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pos">�ʒu</param>
    /// <param name="dir">����</param>
    /// <param name="speed">�ړ����x</param>
    /// <param name="distance">�򋗗�</param>
    /// <param name="verticalSpeed">Y�������x</param>
    CCannonBall(const CVector& pos, const CVector& dir,
        float speed, float distance, float verticalSpeed);
    // �f�X�g���N�^
    ~CCannonBall();

    // �����x��ݒ�
    void SetVerticalSpeed(float speed);

    // �X�V����
    void Update() override;
    // �`�揈��
    void Render() override;

private:
    // ��C�̒e���f��
    CModel* mpCannonBall;
    // �C�e�̃R���C�_�[
    CColliderSphere* mpSpherer;

    // �C�e�̌���
    CVector mDirection;

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