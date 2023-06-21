#include "CEnemy3.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#include "CPlayer.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define OBJ "res\\Alien Animal.obj"	//���f���̃t�@�C��
#define MTL "res\\Alien Animal.mtl"	//���f���̃}�e���A���t�@�C��

#define HP 3	//�ϋv�l
#define VELOCITY 0.11f	//���x
//�ړ����x
#define FOV_ANGLE 45.0f //����̊p�x(�[�p�x+�p�x���o)
#define FOV_LENGTH 5.0f//����̊p�x

CModel CEnemy3::sModel;	//���f���f�[�^�쐬

//�f�t�H���g�R���X�g���N�^
CEnemy3::CEnemy3()
	: CCharacter3(1)
	, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
	, mHp(HP)
	,mState(EState::EIDLE)
{
	//���f���������Ƃ��͓ǂݍ���
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &sModel;
}


//CEnemy(�ʒu, ��], �g�k)
CEnemy3::CEnemy3(CModel* model, const CVector& position, const CVector& rotation,const CVector& scale)
	: CEnemy3()	//�f�t�H���g�R���X�g���N�^�����s����
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	CTransform::Update();	//�s��̍X�V
	//�ڕW�n�_�̐ݒ�
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
}

void CEnemy3::UpdateIdle()
{
	//�v���C���[����������A�ǐՏ�Ԃֈڍs
	if (IsFoundPlayer())
	{
		mState = EState::ECHASE;
	}
}

void CEnemy3::UpdateChase()
{
	//�v���C���[������������A�ҋ@��Ԃֈڍs
	if (!IsFoundPlayer())
	{
		mState = EState::EIDLE;
	}
	else
	{
		/*CVector playerPos = CPlayer::Instance()->Position();
		float distance = (playerPos - Position().Length());*/
		// �v���C���[�̃|�C���^��0�ȊO�̎�
		CPlayer* player = CPlayer::Instance();
		//�ڕW�n�_�܂ł̃x�N�g�������߂�
		CVector vp = mPoint - mPosition;
		//�ۑ�
		float dx = vp.Dot(mMatrixRotate.VectorX());	//���x�N�g���Ƃ̓��ς����߂�
		float dy = vp.Dot(mMatrixRotate.VectorY());	//��x�N�g���Ƃ̓��ς����߂�

		CVector forwrd = mMatrixRotate.VectorX().Normalize();
		CVector forwed1 = mMatrixRotate.VectorY().Normalize();

		const float margin = 0.1f;
		//���E�����։�]
		if (dx > margin)
		{
			mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f); //���։�]
		}
		else if (dx < -margin)
		{
			//�ۑ�
			mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f); //�E�։�]
		}
		//�㉺�����։�]
		if (dy > margin)
		{
			mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f); //��։�]
		}
		else if (dy < -margin)
		{
			//�ۑ�
			mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f); //���։�]
		}
		//�@�̑O���ֈړ�����
		mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
		CTransform::Update();	//�s��X�V

		//���悻3�b���ɖڕW�n�_���X�V
		int r = rand() % 180;	//rand()�͐����̗�����Ԃ�
		//% 180 ��180�Ŋ������]������߂�
		if (r == 0)
		{
			if (player != nullptr)
			{
				mPoint = player->Position();
			}
			else
			{
				mPoint = mPoint * CMatrix().RotateY(45);
			}
		}
	}
}

void CEnemy3::UpdateAttack()
{
	//�v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		//�v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = player->Position() - mPosition;
		//���x�N�g���Ƃ̓��ς����߂�
		float dx = vp.Dot(mMatrixRotate.VectorX());
		//��x�N�g���Ƃ̓��ς����߂�
		float dy = vp.Dot(mMatrixRotate.VectorY());
		//�O�x�N�g���Ƃ̓��ς����߂�
		float dz = vp.Dot(mMatrixRotate.VectorZ());
		//X���̃Y����2.0�ȉ�
		if (-2.0f < dx && dx < 2.0f && 0.0f < dz && dz <= 30.0f)
		{
			//Y���̃Y����2.0�ȉ�
			if (-2.0f < dy && dy < 2.0f)
			{
				//�e�𔭎˂��܂�
				CBullet* bullet = new CBullet();
				bullet->Set(0.1f, 1.5f);
				bullet->Position(
					CVector(0.0f, 0.0f, 10.0f) * mMatrix);
				bullet->Rotation(mRotation);
				bullet->Update();
			}
			else
			{
				mState = EState::ECHASE;
			}
		}
	}
}

//�X�V����
void CEnemy3::Update()
{

	switch (mState)
	{
	case EState::EIDLE:
		UpdateIdle();
			break;
	case EState::ECHASE:
		UpdateChase();
		break;
	case EState::EATTACK:
		UpdateAttack();
		break;
	}

	
	//HP��0�ȉ��̎��@���j
	if (mHp <= 0)
	{
		mHp--;
		//15�t���[�����ɃG�t�F�N�g
		if (mHp % 15 == 0)
		{
			//�G�t�F�N�g����
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		//���~������
		mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
		CTransform::Update();
		return;
	}


	//

	//����p�̎���
	//��������Ƃ��̓G�l�~�[�Ɏ���
	//�Q�w�搶�̃R�[�h
	CVector a, bVector;
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
		if (distance <= 100.0f) //�����\
		{
			//�G����v���C���[�܂ł̋������͈͓�
			printf("�͈͓��ɓ���܂���");
		}
		else
		{
			printf("�͈͊O");
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
		printf("FoundPlayer:%s\n", IsFoundPlayer() ? "true" : "false");
	}

	////�s����X�V
	//CTransform::Update();
	////�ʒu���ړ�
	//mPosition = mPosition + VELOCITY * mMatrixRotate;

}

//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CEnemy3::Collision(CCollider* m, CCollider* o)
{
	//����̃R���C�_�^�C�v�̔���
	switch (o->Type())
	{
	case CCollider::ESPHERE: //���R���C�_�̎�
		//�R���C�_��m��o���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă��鎞�͖����ɂ���
			//mEnabled = false;
			mHp--;	//�q�b�g�|�C���g�̌��Z
		}
		break;
	case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
		CVector ad;
		//�R���C�_��m��o���Փ˂��Ă��邩����
		if (CCollider::CollisionTriangleSphere(o, m, &ad)) {
			//���j�Œn�ʂɏՓ˂���Ɩ���
			if (mHp <= 0)
			{
				mEnabled = false;
			}
		}
		break;
	}
}

void CEnemy3::Collision()
{
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}

//�v���C���[�����������ǂ���
bool CEnemy3::IsFoundPlayer() const
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

	//�ύX����//
	const float chaseRenge = 100.0f;

	//���߂������َq�⋗����艓���Ȃ��,false��Ԃ�
	if (distance > FOV_LENGTH) return false;

	//����p�x�s�s�⋗���̔����ʂ����̂�true��Ԃ�
	return true;
}