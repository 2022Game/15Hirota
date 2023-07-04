#include "CVector.h"
#include <math.h>

float CVector::Dot(const CVector& v) const
{
	return mX * v.mX + mY * v.mY + mZ * v.mZ;
}

float CVector::Length() const
{
	//sqrt�֐��ŕ�������Ԃ�
	return sqrtf(mX * mX + mY * mY + mZ * mZ);
}

CVector CVector::Normalize() const {
	//�x�N�g���̑傫���Ŋ������x�N�g����Ԃ��i����1�̃x�N�g���j
	return *this * (1.0f / Length());
}

CVector CVector::Cross(const CVector& v) const
{
	return CVector(mY * v.mZ - mZ * v.mY, mZ * v.mX - mX * v.mZ, mX * v.mY - mY * v.mX);
}

CVector CVector::operator*(const float& f) const
{
	return CVector(mX*f, mY*f, mZ*f);
}

//Set(X���W, Y���W, Z���W)
void CVector::Set(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

void CVector::SetY(float y)
{
	mY = y;
}

void CVector::SetX(float x)
{
	mX = x;
}

float CVector::X() const
{
	return mX;
}

float CVector::Y() const
{
	return mY;
}

float CVector::Z() const
{
	return mZ;
}

float CVector::GetY() const
{
	return mY;
}

float CVector::GetX() const
{
	return mX;
}

//void CVector::X(float x)
//{
//	mX = x;
//}
//
//void CVector::Y(float y)
//{
//	mY = y;
//}
//void CVector::Z(float z)
//{
//	mZ = z;
// }

CVector::CVector()
	: mX(0.0f), mY(0.0f), mZ(0.0f)
{
}

CVector::CVector(float x, float y, float z)
	: mX(x), mY(y), mZ(z)
{
}

CVector CVector::operator+(const CVector& v) const
{
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

CVector CVector::operator-(const CVector& v) const
{
	return CVector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

CVector CVector::operator*(const CMatrix& m)
{
	//�|���Z�̌��ʂ�CVector�^�̒l�ŕԂ�
	return CVector(
		mX * m.M(0, 0) + mY * m.M(1, 0) + mZ * m.M(2, 0) + m.M(3, 0),
		mX * m.M(0, 1) + mY * m.M(1, 1) + mZ * m.M(2, 1) + m.M(3, 1),
		mX * m.M(0, 2) + mY * m.M(1, 2) + mZ * m.M(2, 2) + m.M(3, 2)
	);
}

float CVector::DotProduct(const CVector& v1, const CVector& v2)
{
	return v1.X() * v2.X() + v1.Y() * v2.Y() + v1.Z() * v2.Z();
}

void CVector::operator+=(const CVector& v)
{
	mX += v.mX;
	mY += v.mY;
	mZ += v.mZ;
}

void CVector::operator-=(const CVector& v)
{
	mX -= v.mX;
	mY -= v.mY;
	mZ -= v.mZ;
}

void CVector::operator*=(const float& f)
{
	mX *= f;
	mY *= f;
	mZ *= f;
}