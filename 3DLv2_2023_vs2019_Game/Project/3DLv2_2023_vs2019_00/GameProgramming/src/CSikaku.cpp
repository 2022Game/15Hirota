#include "CSikaku.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#include "CColliderMesh.h"

#define IDOU CVector(0.08f,0.0f,0.0f)

void CSikaku::Collision(CCollider* m, CCollider* o)
{
	if (CCollider::Collision(m, o)) {
		mEnabled = false;
		// �v���C���[�̈ʒu���ړ�������
		//CPlayer::Instance()->Position(CPlayer::Instance()->Position() + IDOU);
	}
}

void CSikaku::Collision()
{
	mColliderMesh1.ChangePriority();
	//�R���C�_�̗D��x�ύX
}


CSikaku::CSikaku(CModel* model, const CVector& position, const CVector& rotation, const CVector& scale)
	:mReversed(false)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
	mColliderMesh1.Set(this, &mMatrix, mpModel);
}

void CSikaku::Update()
{
	Position(Position() + IDOU); // �ʏ�̈ړ�

	//�s����X�V
	CTransform::Update();
}

//bool CSikaku::IsPlayerOnTop() const
//{
//	return CPlayer::Instance();
//}
