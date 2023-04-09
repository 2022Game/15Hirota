#include "CEnemy.h"

//�ړ����x
#define VELOCITY CVector(0.0f,0.0f,0.09f)

//�R���X�g���N�^
//CEnemy(���f���A�ʒu�A��]�A�g�k)
CEnemy::CEnemy(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 0.8f)
	, mCollider2(this, &mMatrix, CVector(0.0f,5.0f,20.0f), 0.8f)
	, mCollider3(this, &mMatrix, CVector(0.0f,5.0f,-20.f), 0.8f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;		//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�

}

//�Փˏ���
//Collision(�R���C�_�P�A�R���C�_�Q)
void CEnemy::Collision(CCollider* m, CCollider* o) {
	//����̃R���C�_�^�C�v�̔���
	switch (o->Type())
	{
	case CCollider::ESPHERE://���R���C�_�̎�
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă���Ƃ��͖����ɂ���
			//mEnabled = false;
		}
		break;
	case CCollider::ETRIANGLE://���R���C�_�̎�
		CVector abjust;//�����l
		//���R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &abjust))
		{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + abjust;
		}
		break;
	}
}

void CEnemy::Collision()
{
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();

	CCollisionManager::Instance()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mCollider2, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mCollider3, COLLISIONRANGE);
}

//�X�V����
void CEnemy::Update() {
	//�s����X�V
	CTransform::Update();
	//�ʒu���X�V
	mPosition = mPosition + VELOCITY * mMatrixRotate;
}