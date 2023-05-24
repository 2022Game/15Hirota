#include "CItem1.h"
#include "CEffect.h"
#include "CCollisionManager.h"

//��]���x
#define VELOCITY CVector(0.0f, 0.0f, 0.5f)

#define VELOCITY_I CVector(0.0f,0.0f,0.5f);

void CItem1::Collision()
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

void CItem1::Collision(CCollider* m, CCollider* o)
{
	//����̃R���C�_�^�C�v�̔���
	switch (o->Type())
	{
	case CCollider::ESPHERE: //���R���C�_�̎�
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			//new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
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
CItem1::CItem1(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 0.0f, 10.0f), 0.7f)
{

	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
}

//�X�V����
void CItem1::Update() {
	//�s����X�V
	CTransform::Update();
	mRotation = mRotation + VELOCITY * mMatrixRotate;

	//�ʒu���ړ�
	//mPosition = mPosition + VELOCITY * mMatrixRotate;
}