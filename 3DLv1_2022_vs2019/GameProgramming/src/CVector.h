#ifndef CVECTOR_H
#define CVECTOR_H // CVECTOR_H�̒�`
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
private:
	//3D�e���ł̒l��ݒ�
	float mX, mY, mZ;

};
#endif;