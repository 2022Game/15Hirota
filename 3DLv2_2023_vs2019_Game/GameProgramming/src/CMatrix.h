#ifndef CMATRIX_H
#define CMATRIX_H

class CVector;
/*
�}�g���N�X�N���X
4�s4��̍s��f�[�^�������܂�
*/
class CMatrix {
public:
	//�\���m�F�p
	//4*�̍s�����ʏo��
	void Print();
	CVector VectorZ() const;	//Z���x�N�g���̎擾
	CVector VectorY() const;	//Y���x�N�g���̎擾
	CVector VectorX() const;	//X���x�N�g���̎擾
	//�f�t�H���g�R���X�g���N�^
	CMatrix();
	//�P�ʍs��̍쐬
	CMatrix Identity();
	//�g��k���̍쐬
	//Scale(�{��X,�{��Y,�{��Z)
	CMatrix Scale(float sx, float sy, float sz);
	//�s��l�̎擾
	//M(�s�A��)
	//mM[�s][��]���擾
	float M(int r, int c)const;
	//��]�s��(Y��)�̍쐬
	//RotateY(�p�x)
	CMatrix RotateY(float degree);
	//��]�s��(Z��)�̍쐬
	//RotateZ(�p�x)
	CMatrix RotateZ(float degree);
	//��]�s��(X��)�̍쐬
	//RotateX(�p�x)
	CMatrix RotateX(float degree);
	//�ړ��s��̍쐬
	//Translate(�ړ���X,�ړ���Y,�ړ���Z)
	CMatrix Translate(float mx, float my, float mz);
	//�s��l�̑��
	//M(�s���A�񐔁A�l)
	void M(int row, int col, float value);
	//*���Z�q�̃I�[�o�[���[�h
	//CMatrix *CMatrix�̉��Z���ʂ�Ԃ�
	const CMatrix operator*(const CMatrix& m)const;
	//�s��̎擾
	float* M()const;
	//�t�s��擾
	CMatrix Transpose() const;
	CMatrix Copy() const;
private:
	//4*4�̍s��f�[�^��ݒ�
	float mM[4][4];
};
#endif