#include "CCollider.h"
#include "CCollisionManager.h"

CCollider::CCollider(CCharacter3* parent, CMatrix* matrix,
	const CVector& position, float radius) {
	//�e�ݒ�
	mpParent = parent;
	//�e�s��ݒ�
	mpMatrix = matrix;
	//CTransform�ݒ�
	mPosition = position;	//�ʒu
	//���a
	mRadius = radius;
	//�R���W�����}�l�[�W���ɒǉ�
	CCollisionManager::Instance()->Add(this);
}

//�f�X�g���N�^
CCollider::~CCollider() {
	//�q���W�������X�g����폜
	CCollisionManager::Instance()->Remove(this);
}

CCharacter3* CCollider::parent()
{
	return mpParent;
}

void CCollider::Render() {
	glPushMatrix();
	//�R���C�_�̒��S���W���v�Z
	//�����̒��S���W���v�Z
	CVector pos = mPosition * *mpMatrix;
	//���S���W�ֈړ�
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());
	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//���`��
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}