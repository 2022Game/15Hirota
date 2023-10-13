#include "CColliderSphere.h"
#include <glut.h>

// �R���X�g���N�^
CColliderSphere::CColliderSphere(CObjectBase* owner, ELayer layer, float radius)
	: CCollider(owner, layer, EColliderType::eSphere)
	, mRadius(radius)
{
}

// ���R���C�_�[�̐ݒ�
void CColliderSphere::Set(CObjectBase* owner, ELayer layer, float radius)
{
	CCollider::Set(owner, layer);

	// ���a��ݒ�
	mRadius = radius;
}

// ���̍��W�Ɣ��a���擾
void CColliderSphere::Get(CVector* pos, float* rad) const
{
	*pos = Position();
	*rad = mRadius;
}

void CColliderSphere::Render()
{
	// ���݂̍s���ޔ����Ă���
	glPushMatrix();

	// ���g�̍s���K�p
	glMultMatrixf(Matrix().M());
	// �A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	// �u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// ���C�g�I�t
	glDisable(GL_LIGHTING);

	// DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f, 0.0f, 0.0f, 0.2f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	// ����`��
	glutWireSphere(mRadius, 32, 32);

	// ���C�g�I��
	glEnable(GL_LIGHTING);
	// �A���t�@�u�����h����
	glDisable(GL_ALPHA);

	// �`��O�̍s��ɖ߂�
	glPopMatrix();
}
