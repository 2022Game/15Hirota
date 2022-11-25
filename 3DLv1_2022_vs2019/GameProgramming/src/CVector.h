#ifndef CVECTOR_H
#define CVECTOR_H // CVECTOR_H�̒�`
#include "CMatrix.h"

/*
�x�N�g���N���X
�x�N�g���N���X�������܂�
*/
class CVector {
public:
	//�e���ł̒l�̐ݒ�
	//Set(X���W,Y���W,Z���W)
	void Set(float x, float y, float z);
	//X�̒l��m��
	float X() const;
	//Y�̒l��m��
	float Y() const;
	//Z�̒l��m��
	float Z() const;

	//�f�t�H���g�R���X�g���N�^
	CVector();
	//�R���X�g���N�^
	//CVector(X���W,Y���W,Z���W)
	CVector(float x, float y, float z);

	//+���Z�q�̃I�[�o�[���[�h
	//CVector +CVector �̉��Z���ʂ�Ԃ�
	CVector operator+(const CVector& v)const;

	//-���Z�q�̃I�[�o�[���[�h
	//CVector - CVector �̉��Z���ʂ�Ԃ�
	CVector operator-(const CVector& v)const;

	//CVector * CMatrix�̌��ʂ�CVector�ŕԂ�
	CVector operator*(const CMatrix & m);

private:
	//3D�e���ł̒l��ݒ�
	float mX, mY, mZ;

};
#endif;