#ifndef CCIRCLENBFLLEFT1_H
#define CCIRCLENBFLLEFT1_H

#include "CCircleNbFl1.h"

// �~��]����񐔂ŗ����鏰(1��)
class CCircleNbFlLeft1 : public CCircleNbFl1
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
	/// <param name="speed">���x</param>
	/// <param name="rotateangle">��]���������߂�</param>
	CCircleNbFlLeft1(const CVector& pos, const CVector& scale, const CVector& rot,
		float angle, float dist, float speed, bool rotateangle);
	// �f�X�g���N�^
	~CCircleNbFlLeft1();
};
#endif