//�G�C���A���N���X�̃C���N���[�h
#include "CItem1.h"
#include "CApplication.h"
#include "CCollisionManager.h"

#define OBJ "res\\12190_Heart_v1_L3.obj"	//���f���̃t�@�C��
#define MTL "res\\12190_Heart_v1_L3.mtl"	//���f���̃}�e���A���t�@�C��
#define VELOCITY CVector(0.0f, 0.0f, 0.5f)	//�ړ����x
#define ROTATION_YV	CVector(0.0f, 0.0f, 0.5f) //��]���x

#define HP 3 //HP�̏����l��3

CItem1::CItem1()
	:CItem1(CVector(0.0f,0.0f,0.0f),CVector(0.0f,0.0f,0.0f),CVector(0.0f,1.0f,1.0f))
{
}

//CItem1(�ʒu, ��], �X�P�[��)
CItem1::CItem1(const CVector& pos, const CVector& rot, const CVector& scale)
	//���s��
	: mLine(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f))
	//�c
	, mLine2(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f))
	//��
	, mLine3(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f))
{
	CTransform::Update(pos, rot, scale);

	mpModel = new CModel();
	mpModel->Load(OBJ, MTL);

	//�A�C�e����HP��ݒ肷��
	mHp = HP;
}

//�X�V����
void CItem1::Update() {
	//�ϊ��s��̍X�V
	CTransform::Update();
	//�ʒu�̍X�V
	mRotation = mRotation + VELOCITY * mMatrixRotate;
	//UI�ݒ�
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());
}

void CItem1::Collision()
{
	//�R���C�_�̗D��x�ύX
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Instance()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mLine3, COLLISIONRANGE);
}

void CItem1::Collision(CCollider* m, CCollider* o) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::ELINE://�����R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition + adjust;
				//�s��̍X�V
				CTransform::Update();
			}
		}
		break;
	}
}

//#include "CItem1.h"
//#include "CEffect.h"
//#include "CCollisionManager.h"
//
////��]���x
//#define VELOCITY CVector(0.0f, 0.0f, 0.5f)
//
//#define VELOCITY_I CVector(0.0f,0.0f,0.5f);
//
//void CItem1::Collision()
//{
//	//�R���C�_�̗D��x�ύX
//	mCollider1.ChangePriority();
//	mCollider2.ChangePriority();
//	mCollider3.ChangePriority();
//	//�Փˏ��������s
//	CCollisionManager::Instance()->Collision(&mCollider1, COLLISIONRANGE);
//	CCollisionManager::Instance()->Collision(&mCollider2, COLLISIONRANGE);
//	CCollisionManager::Instance()->Collision(&mCollider3, COLLISIONRANGE);
//}
//
//void CItem1::Collision(CCollider* m, CCollider* o)
//{
//	//����̃R���C�_�^�C�v�̔���
//	switch (o->Type())
//	{
//	case CCollider::ESPHERE: //���R���C�_�̎�
//		//�R���C�_��m��y���Փ˂��Ă��邩����
//		if (CCollider::Collision(m, o)) {
//			//�G�t�F�N�g����
//			//new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
//			//�Փ˂��Ă��鎞�͖����ɂ���
//			//mEnabled = false;
//		}
//		break;
//	case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
//		CVector adjust; //�����l
//		//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
//		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
//		{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
//			mPosition = mPosition + adjust;
//		}
//		break;
//	}
//
//}
//
////�R���X�g���N�^
////CEnemy(���f��, �ʒu, ��], �g�k)
//CItem1::CItem1(CModel* model, const CVector& position,
//	const CVector& rotation, const CVector& scale)
//	: mCollider1(this, &mMatrix, CVector(0.0f, 0.0f, 10.0f), 0.7f)
//{
//
//	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
//	mpModel = model;	//���f���̐ݒ�
//	mPosition = position;	//�ʒu�̐ݒ�
//	mRotation = rotation;	//��]�̐ݒ�
//	mScale = scale;	//�g�k�̐ݒ�
//}
//
////�X�V����
//void CItem1::Update() {
//	//�s����X�V
//	CTransform::Update();
//	mRotation = mRotation + VELOCITY * mMatrixRotate;
//
//	//�ʒu���ړ�
//	//mPosition = mPosition + VELOCITY * mMatrixRotate;
//}