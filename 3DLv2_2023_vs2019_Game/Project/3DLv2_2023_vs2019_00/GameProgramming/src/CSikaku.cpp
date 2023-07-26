#include "CSikaku.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#include "CColliderMesh.h"

#include <cstdlib>

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

{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�

	//�^�X�N�̗D��x��ݒ�
	mPriority = (int)TaskPriority::eBackground;

	//�w�i�̃��f���f�[�^�ǂݍ���
	mpModel = new CModel;
	mpModel->Load("res\\aoiro sikaku1.obj", "res\\aoiro sikaku.mtl");

	//�ǂݍ��񂾔w�i�̃��f���f�[�^�ŃR���C�_���쐬
	mColliderMesh1.Set(this, &mMatrix, mpModel);
}

CSikaku::~CSikaku()
{
	delete mpModel;
	mpModel = nullptr;
}

void CSikaku::Update()
{
	//�s����X�V
	CTransform::Update();
}

//bool CSikaku::IsPlayerOnTop() const
//{
//	return CPlayer::Instance();
//}
