//�v���C���[�N���X�̃C���N���[�h
#include "CItem1.h"
#include "CApplication.h"
#include "CCollisionManager.h"
#include "CRectangle.h"

#define HP 100	//hp

#define GRAVITY CVector(0.0f,-0.2f,0.0f)	//�d�͉����x

#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //��]���x
#define VELOCITY CVector(0.0f, 0.0f, 0.3f) //�ړ����x
#define ROTATION_XV	CVector(2.0f, 0.0f, 0.0f) //��]���x

CItem1* CItem1::spInstance = nullptr;

int CItem1::sHp = 0;	//Hp


CItem1::CItem1()
	//: mLine(this, &mMatrix, CVector(0.0f, 3.5f, 2.5f), CVector(0.0f, 3.5f, -2.5f))		//�O��
	//, mLine2(this, &mMatrix, CVector(0.0f, 6.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f))		//�㉺
	//, mLine3(this, &mMatrix, CVector(2.5f, 3.5f, 0.0f), CVector(-2.5f, 3.5f, 0.0f))	//���E
{
	//�C���X�^���X�̐ݒ�
	spInstance = this;
	sHp = HP;
}

//CPlayer(�ʒu, ��], �X�P�[��)
CItem1::CItem1(const CVector& pos, const CVector& rot, const CVector& scale)
{
	CTransform::Update(pos, rot, scale); //�s��̍X�V
}

int CItem1::Hp()
{
	return sHp;
}

//�X�V����
void CItem1::Update() {

	//�ϊ��s��̍X�V
	CTransform::Update();
	//UI�ݒ�
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());



	////�d�͏���
	//mVelocity = mVelocity + GRAVITY;
	//mPosition = mPosition + mVelocity;

	////�ړ�����
	//if (mPosition.Y() > 0.0f) {	//�n�ʂɐڐG���Ă��Ȃ�
	//	mPosition = mPosition + mVelocity;
	//	mVelocity = mVelocity + GRAVITY;
	//}
	////�n�ʂɐڐG���Ă���ꍇ�́A�ʒu��n�ʂ̏�ɌŒ肷��
	//if (mPosition.Y() <= 0.0f) {
	//	mPosition = CVector(mPosition.X(), 0.0f, mPosition.Z());
	//	mVelocity = CVector(mVelocity.X(), 0.0f, mVelocity.Z());
	//}

	//���������Ɏg����

	////�ʒu����ʊO�ɏo���ꍇ�͏����ʒu�ɖ߂�
	//if (mPosition.Y() < -10.0f)
	//{
	//	mPosition = CVector(0.0f, 0.0f, 0.0f);
	//	mVelocity = CVector(0.0f, 0.0f, 0.0f);
	//}
}

CItem1* CItem1::Instance()
{
	return spInstance;
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
			2;
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition + adjust;
				/*mVelocity = CVector(0.0f, 0.0f, 0.0f);*/
				//�s��̍X�V
				CTransform::Update();
			}
			//else
			//{
			//	//�d�͏���
			//	mVelocity = GRAVITY;
			//}
		}
		break;
	}
}