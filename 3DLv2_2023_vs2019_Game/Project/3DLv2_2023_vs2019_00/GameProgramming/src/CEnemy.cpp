#include "CEnemy.h"
#include "CEnemyManager.h"

//�R���X�g���N�^
CEnemy::CEnemy()
	: CCharacter3(1)
{
	//CEnemy��������CEnemyManager�̃��X�g�Ɏ��g��ǉ�
	CEnemyManager::Instance()->Add(this);
}

//�f�X�g���N�^
CEnemy::~CEnemy()
{
	//CEnemy�j������CEnemyManager�̃��X�g���玩�g����菜��
	CEnemyManager::Instance()->Remove(this);
}

////�X�V����
//void CEnemy::Update() {
//
//	//�v���C���[�̃|�C���^��0�ȊO�̎�
//	CPlayer* player = CPlayer::Instance();
//	if (player != nullptr)
//	{
//		//�v���C���[�܂ł̃x�N�g�������߂�
//		CVector vp = player->Position() - mPosition;
//		//���x�N�g���Ƃ̓��ς����߂�
//		float dx = vp.Dot(mMatrixRotate.VectorX());
//		//��x�N�g���Ƃ̓��ς����߂�
//		float dy = vp.Dot(mMatrixRotate.VectorY());
//		//�O�x�N�g���Ƃ̓��ς����߂�
//		float dz = vp.Dot(mMatrixRotate.VectorZ());
//		//X���̃Y����2.0�ȉ�
//		if (-2.0f < dx && dx < 2.0f && 0.0f < dz && dz <= 30.0f)
//		{
//			//Y���̃Y����2.0�ȉ�
//			if (-2.0f < dy && dy < 2.0f)
//			{
//				//�e�𔭎˂��܂�
//				CBullet* bullet = new CBullet();
//				bullet->Set(0.1f, 1.5f);
//				bullet->Position(
//					CVector(0.0f, 0.0f, 10.0f) * mMatrix);
//				bullet->Rotation(mRotation);
//				bullet->Update();
//			}
//		}
//	}
//	//HP��0�ȉ��̎��@���j
//	if (mHp <= 0)
//	{
//		mHp--;
//		//15�t���[�����ɃG�t�F�N�g
//		if (mHp % 15 == 0)
//		{
//			//�G�t�F�N�g����
//			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
//		}
//		//���~������
//		mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
//		CTransform::Update();
//		return;
//	}
//
//	//�ڕW�n�_�܂ł̃x�N�g�������߂�
//	CVector vp = mPoint - mPosition;
//	//�ۑ�
//	float dx = vp.Dot(mMatrixRotate.VectorX());	//���x�N�g���Ƃ̓��ς����߂�
//	float dy = vp.Dot(mMatrixRotate.VectorY());	//��x�N�g���Ƃ̓��ς����߂�
//	const float margin = 0.1f;
//	//���E�����։�]
//	if (dx > margin)
//	{
//		mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f); //���։�]
//	}
//	else if (dx < -margin)
//	{
//		//�ۑ�
//		mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f); //�E�։�]
//	}
//	//�㉺�����։�]
//	if (dy > margin)
//	{
//		mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f); //��։�]
//	}
//	else if (dy < -margin)
//	{
//		//�ۑ�
//		mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f); //���։�]
//	}
//	//�@�̑O���ֈړ�����						//*
//	Position(Position() + MatrixRotate().VectorZ() * VELOCITY);
//	CTransform::Update();	//�s��X�V
//
//	//���悻3�b���ɖڕW�n�_���X�V
//	int r = rand() % 180;	//rand()�͐����̗�����Ԃ�
//	//% 180 ��180�Ŋ������]������߂�
//	if (r == 0)
//	{
//		if (player != nullptr)
//		{
//			mPoint = player->Position();
//		}
//		else
//		{
//			mPoint = mPoint * CMatrix().RotateY(45);
//		}
//	}
//}