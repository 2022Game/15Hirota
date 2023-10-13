#include "CColliderTriangle.h"
#include "glut.h"
#include "Maths.h"

// �R���X�g���N�^
CColliderTriangle::CColliderTriangle(CObjectBase* owner, ELayer layer,
	const CVector& v0, const CVector& v1, const CVector& v2)
	: CCollider(owner, layer, EColliderType::eTriangle)
{
	// �O�p�`�̒��_��ݒ�
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

// �R���X�g���N�^�i�����Ȃ��Łj
CColliderTriangle::CColliderTriangle()
	: CCollider(nullptr, ELayer::eNone, EColliderType::eTriangle)
{
}

// �O�p�`�R���C�_�[�̐ݒ�
void CColliderTriangle::Set(CObjectBase* owner, ELayer layer,
	const CVector& v0, const CVector& v1, const CVector& v2)
{
	CCollider::Set(owner, layer);

	// �O�p�`�̒��_��ݒ�
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

// �O�p�`�̒��_���擾
void CColliderTriangle::Get(CVector* v0, CVector* v1, CVector* v2) const
{
	CMatrix m = Matrix();
	*v0 = mV[0] * m;
	*v1 = mV[1] * m;
	*v2 = mV[2] * m;
}

// �R���C�_�[�`��
void CColliderTriangle::Render()
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

	// �O�p�`��`��
	glBegin(GL_TRIANGLES);
	glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	glVertex3f(mV[2].X(), mV[2].Y(), mV[2].Z());
	glEnd();

	// ���C�g�I��
	glEnable(GL_LIGHTING);
	// �A���t�@�u�����h����
	glDisable(GL_ALPHA);

	// �`��O�̍s��ɖ߂�
	glPopMatrix();
}