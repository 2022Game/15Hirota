#include "CColliderLine.h"
#include <glut.h>
#include "Maths.h"

// �R���X�g���N�^
CColliderLine::CColliderLine(CObjectBase* owner, ELayer layer,
	const CVector& v0, const CVector& v1,
	bool isKinematic, float weight)
	: CCollider(owner, layer, EColliderType::eLine, isKinematic, weight)
	, mRadius(0.1f)
{
	// �����̒��_��ݒ�
	mV[0] = v0;
	mV[1] = v1;
}

// �����R���C�_�[�̐ݒ�
void CColliderLine::Set(CObjectBase* owner, ELayer layer,
	const CVector& v0, const CVector& v1)
{
	CCollider::Set(owner, layer);

	// �����̒��_��ݒ�
	mV[0] = v0;
	mV[1] = v1;
}

// �����̎n�_�ƏI�_���擾
void CColliderLine::Get(CVector* v0, CVector* v1) const
{
	CMatrix m = Matrix();
	*v0 = mV[0] * m;
	*v1 = mV[1] * m;
}

float CColliderLine::Radius() const
{
	return mRadius;
}

void CColliderLine::Render()
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
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	glLineWidth(3.0f);
	// ������`��
	glBegin(GL_LINES);
	glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	glEnd();
	glLineWidth(1.0f);

	// ���C�g�I��
	glEnable(GL_LIGHTING);
	// �A���t�@�u�����h����
	glDisable(GL_ALPHA);

	// �`��O�̍s��ɖ߂�
	glPopMatrix();
}
