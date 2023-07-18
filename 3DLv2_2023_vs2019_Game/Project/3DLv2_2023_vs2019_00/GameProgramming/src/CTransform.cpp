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

//親のTransformを設定
void CTransform::SetParent(CTransform* parent)
{
	mpParent = parent;
}

//行列更新処理
void CTransform::Update() {
	//拡大縮小行列の設定
	mLocalMatrixScale.Scale(mScale.X(), mScale.Y(), mScale.Z());
	//回転行列の設定
	mLocalMatrixRotate =
		CMatrix().RotateZ(mRotation.Z()) *
		CMatrix().RotateX(mRotation.X()) *
		CMatrix().RotateY(mRotation.Y());
	//平行移動行列の設定
	mLocalMatrixTranslate.Translate(mPosition.X(), mPosition.Y(), mPosition.Z());
	//合成行列の設定
	mLocalMatrix = mLocalMatrixScale * mLocalMatrixRotate * mLocalMatrixTranslate;

	//親がいる場合
	if (mpParent != nullptr)
	{
		//ワールド行列 = 親のワールド行列 × ローカル行列
		const CMatrix& parentMtx = mpParent->Matrix();
		mMatrixTranslate = mLocalMatrixTranslate * parentMtx;
		mMatrixRotate = mLocalMatrixRotate * parentMtx;
		mMatrixScale = mLocalMatrixScale * parentMtx;
		mMatrix = mLocalMatrix * parentMtx;
	}
	//親がいない場合
	else
	{
		//ローカル行列をそのままグローバル行列に設定
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