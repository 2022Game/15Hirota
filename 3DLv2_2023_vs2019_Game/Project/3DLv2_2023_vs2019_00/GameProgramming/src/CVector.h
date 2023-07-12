#ifndef CVECTOR_H
#define CVECTOR_H
#include "CMatrix.h"

/*
 �x�N�g���N���X
 �x�N�g���f�[�^�������܂�
*/
class CVector {
public:
	//���K��
	//�傫��1�̃x�N�g����Ԃ�
	CVector Normalize() const;
	//�O��
	//Cross(�x�N�g��)
	CVector Cross(const CVector& v) const;
	//*���Z�q�̃I�[�o�[���[�h
	//CVector * float �̉��Z���ʂ�Ԃ�
	CVector operator*(const float& f) const;

	//����
	//Dot(�x�N�g��)
	float Dot(const CVector& v) const;

	//�x�N�g���̒�����Ԃ�
	float Length() const;
	//�e���ł̒l�̐ݒ�
	//Set(X���W, Y���W, Z���W)
	void Set(float x, float y, float z);

	void SetY(float y);
	void SetX(float x);

	float GetY() const;
	float GetX() const;

	/*void X(float x);
	void Y(float y);
	void Z(float z);*/

	//X�̒l�𓾂�
	float X() const;
	//Y�̒l�𓾂�
	float Y() const;
	//Z�̒l�𓾂�
	float Z() const;

	//�f�t�H���g�R���X�g���N�^
	CVector();
	//�R���X�g���N�^
	//CVector(X���W, Y���W, Z���W)
	CVector(float x, float y, float z);

	float DotProduct(const CVector& v1, const CVector& v2);

	//��r���Z�q
	//CVector == CVector �̌��ʂ�Ԃ�
	bool operator==(const CVector& v) const;
	//CVector != CVector �̌��ʂ�Ԃ�
	bool operator!=(const CVector& v) const;

	//+���Z�q�̃I�[�o�[���[�h
	//CVector + CVector �̉��Z���ʂ�Ԃ�
	CVector operator+(const CVector& v) const;
	//CVector += CVector �ŉ��Z���ʂ����g�ɑ��
	void operator+=(const CVector& v);

	//-���Z�q�̃I�[�o�[���[�h
	//CVector - CVector �̉��Z���ʂ�Ԃ�
	CVector operator-(const CVector& v) const;
	//CVector -= CVector �ŉ��Z���ʂ����g�ɑ��
	void operator-=(const CVector& v);

	//*���Z�q�̃I�[�o�[���[�h
	//CVector * float �̉��Z���ʂ�Ԃ�
	CVector operator*(const float& f) const;
	//CVector *= float �ŉ��Z���ʂ����g�ɑ��
	void operator*=(const float& f);
	//CVector * CMatrix�̌��ʂ�CVector�ŕԂ�
	CVector operator*(const CMatrix& m);


private:
	//3D�e���ł̒l��ݒ�
	float mX, mY, mZ;
};

//�x�N�g���N���X�i2�����j
class CVector2
{
public:
	//���K��
	//�傫��1�̃x�N�g����Ԃ�
	CVector2 Normalize() const;

	//�O��
	//Cross(�x�N�g��)
	float Cross(const CVector2& v) const;

	//����
	//Dot(�x�N�g��)
	float Dot(const CVector2& v) const;

	//�x�N�g���̒�����Ԃ�
	float Length() const;
	//�e���ł̒l�̐ݒ�
	//Set(X���W, Y���W)
	void Set(float x, float y);
	//X�̒l�𓾂�
	float X() const;
	//X�̒l��ݒ�
	void X(float x);
	//Y�̒l�𓾂�
	float Y() const;
	//Y�̒l��ݒ�
	void Y(float y);
	//�f�t�H���g�R���X�g���N�^
	CVector2();
	//�R���X�g���N�^
	//CVector2(X���W, Y���W)
	CVector2(float x, float y);

	//��r���Z�q
	//CVector2 == CVector2 �̌��ʂ�Ԃ�
	bool operator==(const CVector2& v) const;
	//CVector2 != CVector2 �̌��ʂ�Ԃ�
	bool operator!=(const CVector2& v) const;

	//+���Z�q�̃I�[�o�[���[�h
	//CVector2 + CVector2 �̉��Z���ʂ�Ԃ�
	CVector2 operator+(const CVector2& v) const;
	//CVector2 += CVector2 �ŉ��Z���ʂ����g�ɑ��
	void operator+=(const CVector2& v);

	//-���Z�q�̃I�[�o�[���[�h
	//CVector2 - CVector2 �̉��Z���ʂ�Ԃ�
	CVector2 operator-(const CVector2& v) const;
	//CVector2 -= CVector2 �ŉ��Z���ʂ����g�ɑ��
	void operator-=(const CVector2& v);

	//*���Z�q�̃I�[�o�[���[�h
	//CVector2 * float �̉��Z���ʂ�Ԃ�
	CVector2 operator*(const float& f) const;
	//CVector2 *= float �ŉ��Z���ʂ����g�ɑ��
	void operator*=(const float& f);

private:
	//2D�e���ł̒l��ݒ�
	float mX, mY;
};

//�x�N�g���N���X�i4�����j
class CVector4
{
public:
	//�e���ł̒l�̐ݒ�
	//Set(X���W, Y���W, Z���W, W)
	void Set(float x, float y, float z, float w);
	//Set(X���W, Y���W, Z���W)
	void Set(float x, float y, float z);
	//X�̒l�𓾂�
	float X() const;
	//X�̒l��ݒ�
	void X(float x);
	//Y�̒l�𓾂�
	float Y() const;
	//Y�̒l��ݒ�
	void Y(float y);
	//Z�̒l�𓾂�
	float Z() const;
	//Z�̒l��ݒ�
	void Z(float z);
	//W�̒l�𓾂�
	float W() const;
	//W�̒l��ݒ�
	void W(float w);

	//�f�t�H���g�R���X�g���N�^
	CVector4();
	//�R���X�g���N�^
	//CVector(X���W, Y���W, Z���W, W)
	CVector4(float x, float y, float z, float w);
	CVector4(float x, float y, float z);
	CVector4(const CVector& v);

	//������Z�q
	//CVector4 = CVector ��CVector�̓��e�����g�ɑ��
	void operator=(const CVector& v);

	//��r���Z�q
	//CVector4 == CVector4 �̌��ʂ�Ԃ�
	bool operator==(const CVector4& v) const;
	//CVector4 != CVector4 �̌��ʂ�Ԃ�
	bool operator!=(const CVector4& v) const;

	//+���Z�q�̃I�[�o�[���[�h
	//CVector4 + CVector4 �̉��Z���ʂ�Ԃ�
	CVector4 operator+(const CVector4& v) const;
	//CVector4 += CVector4 �ŉ��Z���ʂ����g�ɑ��
	void operator+=(const CVector4& v);


	//-���Z�q�̃I�[�o�[���[�h
	//CVector4 - CVector4 �̉��Z���ʂ�Ԃ�
	CVector4 operator-(const CVector4& v) const;
	//CVector4 -= CVector4 �ŉ��Z���ʂ����g�ɑ��
	void operator-=(const CVector4& v);

	//*���Z�q�̃I�[�o�[���[�h
	//CVector4 * float �̉��Z���ʂ�Ԃ�
	CVector4 operator*(const float& f) const;
	//CVector4 *= float �ŉ��Z���ʂ����g�ɑ��
	void operator*=(const float& f);

private:
	//4D�ł̒l��ݒ�
	float mX, mY, mZ, mW;
};
#endif
