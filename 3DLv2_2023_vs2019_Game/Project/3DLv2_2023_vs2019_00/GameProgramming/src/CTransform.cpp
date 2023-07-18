#include "CTransform.h"

CTransform::CTransform()
	: mpParent(nullptr)
{
}

const CVector& CTransform::Position() const
{
	return mPosition;
}

void CTransform::Position(const CVector& v)
{
	mPosition = v;
}

void CTransform::Velocity(const CVector& v)
{
	mVelocity = v;
}

const CVector& CTransform::Velocity() const
{
	return mVelocity;
}

void CTransform::Rotation(const CVector& v)
{
	mRotation = v;
}

void CTransform::Scale(const CVector& v)
{
	mScale = v;
}

const CMatrix& CTransform::Matrix() const
{
	return mMatrix;
}

const CMatrix& CTransform::MatrixTranslate() const
{
	return mMatrixTranslate;
}

const CMatrix& CTransform::MatrixRotate() const
{
	return mMatrixRotate;
}

const CMatrix& CTransform::MatrixScale() const
{
	return mMatrixScale;
}

//�e��Transform��ݒ�
void CTransform::SetParent(CTransform* parent)
{
	mpParent = parent;
}

//�s��X�V����
void CTransform::Update() {
	//�g��k���s��̐ݒ�
	mLocalMatrixScale.Scale(mScale.X(), mScale.Y(), mScale.Z());
	//��]�s��̐ݒ�
	mLocalMatrixRotate =
		CMatrix().RotateZ(mRotation.Z()) *
		CMatrix().RotateX(mRotation.X()) *
		CMatrix().RotateY(mRotation.Y());
	//���s�ړ��s��̐ݒ�
	mLocalMatrixTranslate.Translate(mPosition.X(), mPosition.Y(), mPosition.Z());
	//�����s��̐ݒ�
	mLocalMatrix = mLocalMatrixScale * mLocalMatrixRotate * mLocalMatrixTranslate;

	//�e������ꍇ
	if (mpParent != nullptr)
	{
		//���[���h�s�� = �e�̃��[���h�s�� �~ ���[�J���s��
		const CMatrix& parentMtx = mpParent->Matrix();
		mMatrixTranslate = mLocalMatrixTranslate * parentMtx;
		mMatrixRotate = mLocalMatrixRotate * parentMtx;
		mMatrixScale = mLocalMatrixScale * parentMtx;
		mMatrix = mLocalMatrix * parentMtx;
	}
	//�e�����Ȃ��ꍇ
	else
	{
		//���[�J���s������̂܂܃O���[�o���s��ɐݒ�
		mMatrixTranslate = mLocalMatrixTranslate;
		mMatrixRotate = mLocalMatrixRotate;
		mMatrixScale = mLocalMatrixScale;
		mMatrix = mLocalMatrix;
	}
}

void CTransform::Update(const CVector& pos, const CVector& rot, const CVector& scale, const CVector& velocity)
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
	mVelocity = velocity;
	Update();
}