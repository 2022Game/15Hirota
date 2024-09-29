#ifndef CCIRCLENBFLRIGHT3_H
#define CCIRCLENBFLRIGHT3_H

#include "CCircleNbFl3.h"

// �~��]����񐔂ŗ����鏰(3��)
class CCircleNbFlRight3 : public CCircleNbFl3
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
	CCircleNbFlRight3(const CVector& pos, const CVector& scale, const CVector& rot,
		float angle, float dist, float speed, bool rotateangle);
	// �f�X�g���N�^
	~CCircleNbFlRight3();
};
#endif