#include "CEnemy3.h"

#define OBJ "res\\f16.obj"	//���f���̃t�@�C��
#define MTL "res\\f16.mtl"	//���f���̃}�e���A���t�@�C��

//�ړ����x
#define VELOCITY CVector(0.0f,0.0f,0.09f)


CModel CEnemy3::sModel;	//���f���̃f�[�^�쐬

//�f�t�H���g�R���X�g���N�^
CEnemy3::CEnemy3()
	:CCharacter3(1)
	, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4)
{
	//���f�����Ȃ��Ƃ��͓ǂݍ���
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &sModel;
}

//CEnemy3(�ʒu�A��]�A�g�k)
CEnemy3::CEnemy3(const CVector& position, const CVector& rotation,
	const CVector& scale)
	:CEnemy3()	//�f�t�H���g�R���X�g���N�^�����s����
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�
	CTransform::Update();	//�s��̍X�V
}

//�Փˏ���
//COllision(�R���C�_�P�A�R���C�_�Q)
void CEnemy3::Collision(CCollider* m, CCollider* o)
{
	//����̃R���C�_�^�C�v�̔���
	switch (o->Type())
	{
	case CCollider::ESPHERE:	//���R���C�_�̎�
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă���Ƃ��͖����ɂ���
			//mEnagled = false;
		}
		break;
	case CCollider::ETRIANGLE:	//���R���C�_�̎�
		CVector abjust;	//�����l
		//���R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &abjust))
		{
			//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + abjust;
		}
		break;
	}
}

void CEnemy3::Collision()
{
	mCollider.ChangePriority();

	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}

//�X�V����
void CEnemy3::Update()
{
	//�s����X�V
	CTransform::Update();
	////�ʒu���X�V
	//mPosition = mPosition + VELOCITY * mMatrixRotate;
}