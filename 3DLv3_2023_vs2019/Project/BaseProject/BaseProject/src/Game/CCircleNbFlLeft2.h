#ifndef CCIRCLENBFLLEFT2_H
#define CCIRCLENBFLLEFT2_H

#include "CCircleNbFl2.h"

// �~��]����񐔂ŗ����鏰(2��)
class CCircleNbFlLeft2 : public CCircleNbFl2
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
	CCircleNbFlLeft2(const CVector& pos, const CVector& scale, const CVector& rot,
		float angle, float dist, float speed, bool rotateangle);
	// �f�X�g���N�^
	~CCircleNbFlLeft2();
};
#endif