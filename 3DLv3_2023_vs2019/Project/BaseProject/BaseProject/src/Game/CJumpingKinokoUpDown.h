#ifndef CJUMPINGKINOKOUPDOWN_H
#define CJUMPINGKINOKOUPDOWN_H

#include "CJumpingKinokoMove.h"

// �v���C���[�𒵂˂�����L�m�R(�㉺)
class CJumpingKinokoUpDown : public CJumpingKinokoMove
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="move">�ړ�����</param>
	/// <param name="moveTime">�ړ�����</param>
	CJumpingKinokoUpDown(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime);
	// �f�X�g���N�^
	~CJumpingKinokoUpDown();
};
#endif