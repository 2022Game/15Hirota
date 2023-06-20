#include "CEnemy.h"
#include "CEffect.h"
#include "CCollisionManager.h"
#include "CPlayer.h"
#define _USE_MATH_DEFINES
#include <math.h>
//#define M_PI        3.14159265358979323846264338327950288

//�ړ����x
#define VELOCITY CVector(0.0f, 0.0f, 0.09f)
#define FOV_ANGLE 45.0f //����̊p�x(�[�p�x+�p�x���o)
#define FOV_LENGTH 5.0f//����̊p�x

void CEnemy::Collision()
{
	//�R���C�_�̗D��x�ύX
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Instance()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mCollider2, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mCollider3, COLLISIONRANGE);
}

void CEnemy::Collision(CCollider* m, CCollider* o)
{
	//����̃R���C�_�^�C�v�̔���
	switch (o->Type())
	{
	case CCollider::ESPHERE: //���R���C�_�̎�
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă��鎞�͖����ɂ���
			//mEnabled = false;
		}
		break;
	case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
		CVector adjust; //�����l
		//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + adjust;
		}
		break;
	}

}

//�R���X�g���N�^
//CEnemy(���f��, �ʒu, ��], �g�k)
CEnemy::CEnemy(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 0.8f)
	, mCollider2(this, &mMatrix, CVector(0.0f, 5.0f, 20.0f), 0.8f)
	, mCollider3(this, &mMatrix, CVector(0.0f, 5.0f, -20.0f), 0.8f)
{

	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
}

//�v���C���[�����������ǂ���
bool CEnemy::IsFoundPlayer() const
{
	CVector playerPos = CPlayer::Instance()->Position();
	CVector enemyPos = Position();

	//����̊p�x�̔���
	//���g����v���C���[�܂ł̃x�N�g�����擾(�v���K��)
	CVector EP = (playerPos - enemyPos).Normalize();

	//�G���g�̐��ʕ����̃x�N�g�����擾(�v���K��)
	CVector forwrd = MatrixRotate().VectorZ().Normalize();

	//���ʕ����̃x�N�g���ƃv���C���[�܂ł̃x�N�g����
	//���ϋ�p�x�����߂�
	float dot = forwrd.Dot(EP);
	//���߂��p�x������p�x�O�ł���΁Afalse��Ԃ�
	if (dot < cosf(FOV_ANGLE * M_PI / 180.0f)) return false;

	//����̋����̔���
	//���g����v���C���[�܂ł̋��������߂�
	float distance = (playerPos - enemyPos).Length();

	//���߂������َq�⋗����艓���Ȃ��,false��Ԃ�
	if (distance > FOV_LENGTH) return false;

	//����p�x�s�s�⋗���̔����ʂ����̂�true��Ԃ�
	return true;
}

//�X�V����
void CEnemy::Update() {

	//

	//����p�̎���
	//��������Ƃ��̓G�l�~�[�Ɏ���
	//�Q�w�搶�̃R�[�h
	CVector a,bVector;
	float b = a.Dot(bVector);

	CVector playerPos = CPlayer::Instance()->Position();	//�v���C���[���W
	CVector enemyPos = Position();	//�G�l�~�[���W

	//�G�l�~�[����v���C���[�܂ł̃x�N�g�������߂�
	//�ړI�n�܂ł̃x�N�g�� = �ړI�n - �J�n�ʒu
	CVector EP = (playerPos - enemyPos).Normalize();

	//�G�l�~�[�̐��ʕ����̃x�N�g��
	CVector forward = MatrixRotate().VectorZ().Normalize();

	//���ʕ����̃x�N�g���ƃv���C���[�܂ł̃x�N�g����
	//���ς����A�p�x�����߂�
	float dot = forward.Dot(EP);
	if (dot >= cosf(45.0f * (M_PI / 180.0f)))	//45�x�͒����\
	{
		M_PI;
		//�v���C���[ -45�x�`45�x�͈̔͂ɂ���
		//�f�B�O���[�@�@�@�@���W�A��
		//180�x �@�@�@= �@�@3.14���W�A��(��)
		//360�x	�@�@�@= �@�@6.28���W�A��(2��)
		//1�x		  =     0.0174���W�A��

		//�傫�������炻�͈̔͂ɋ���

		//�G����v���C���[�܂ł̋���
		float distance = (playerPos - enemyPos).Length();
		if (distance <= 5.0f) //�����\
		{
			//�G����v���C���[�܂ł̋������͈͓�

		}
	}

	//�p�x���f�B�O���[���烉�W�A���ɕϊ�
	//radian = degree * (M_PI / 180.0f)

	//�p�x�����W�A������f�B�O���[�ɕϊ�
	//degree = radian * (180.0f / M_PI)
	//[180 / M_PI]��
	//1���W�A���̎��̃f�B�O���[�̊p�x�����߂Ă���

	//

	if (IsFoundPlayer())
	{
		printf("FoundPlayer:%s\n",IsFoundPlayer()?"true":"false");
	}

	//�s����X�V
	CTransform::Update();
	//�ʒu���ړ�
	mPosition = mPosition + VELOCITY * mMatrixRotate;
}