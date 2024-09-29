#ifndef CCIRCLENBFL1_H
#define CCIRCLENBFL1_H

#include "CNumberFloor1.h"

// �~��]����񐔂ŗ����鏰(1��)�x�[�X
class CCircleNbFl1 : public CNumberFloor1
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="angle">�p�x</param>
	/// <param name="dist">����</param>
	/// <param name="speed">��]�̑���</param>
	/// <param name="rotateangle">��]�����̐ݒ�</param>
	/// <param name="modelPath">���f���p�X</param>
	CCircleNbFl1(const CVector& pos, const CVector& scale, const CVector& rot,
		float angle, float dist, float speed, bool rotateangle,
		std::string modelPath);
	// �f�X�g���N�^
	virtual ~CCircleNbFl1();

	void Update() override;

protected:
	// ���̈ʒu
	CVector mDefaultPos;

	// �o�ߎ���
	float mElapsedRotateTime;
	// �p�x
	float mAngle;
	// ����
	float mDistance;
	// ��]�X�s�[�h
	float mSpeed;
};
#endif