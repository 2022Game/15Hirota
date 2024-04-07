#include "CColliderCapsule.h"
#include <glut.h>
#include "Maths.h"
#include "CColor.h"

// �R���X�g���N�^
CColliderCapsule::CColliderCapsule(CObjectBase* owner, ELayer layer,
	const CVector& v0, const CVector& v1, float radius,
	bool isKinematic, float weight)
	: CCollider(owner, layer, EColliderType::eCapsule, isKinematic, weight)
	, mRadius(radius)
{
	// �J�v�Z�����\����������̒��_��ݒ�
	mV[0] = v0;
	mV[1] = v1;
}

// �J�v�Z���R���C�_�[�̐ݒ�
void CColliderCapsule::Set(CObjectBase* owner, ELayer layer,
	const CVector& v0, const CVector& v1, float radius)
{
	CCollider::Set(owner, layer);

	// �J�v�Z�����\����������̒��_��ݒ�
	mV[0] = v0;
	mV[1] = v1;

	// ���a��ݒ�
	mRadius = radius;
}

// �J�v�Z�����\����������̎��_�ƏI�_���擾
void CColliderCapsule::Get(CVector* v0, CVector* v1) const
{
	*v0 = mWV[0];
	*v1 = mWV[1];
}

// �J�v�Z���̔��a���擾
float CColliderCapsule::Radius() const
{
	return mRadius;
}

// �R���C�_�[�`��
void CColliderCapsule::Render()
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
	CColor col = CColor::red;
	if (!IsEnable()) col = CColor::gray;
	float* c = (float*)&col;
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

// �R���C�_�[�̏����X�V
void CColliderCapsule::UpdateCol()
{
	// ���_�̃��[���h���W���Z�o
	CMatrix m = Matrix();
	mWV[0] = mV[0] * m;
	mWV[1] = mV[1] * m;

	// �o�E���f�B���O�{�b�N�X���X�V
	mBounds = CBounds::GetCapsuleBounds(mWV[0], mWV[1], mRadius);
}