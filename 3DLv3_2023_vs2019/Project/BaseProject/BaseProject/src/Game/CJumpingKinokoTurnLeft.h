#ifndef CJUMPINGKINOKOTURNLEFT_H
#define CJUMPINGKINOKOTURNLEFT_H

#include "CJumpingKinokoRotate.h"

// �v���C���[�𒵂˂�����L�m�R(���~��])
class CJumpingKinokoTurnLeft : public CJumpingKinokoRotate
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
	CJumpingKinokoTurnLeft(const CVector& pos, const CVector& scale, const CVector& rot,
		float angle, float dist, float speed, bool rotateangle);
	// �f�X�g���N�^
	~CJumpingKinokoTurnLeft();
};
#endif