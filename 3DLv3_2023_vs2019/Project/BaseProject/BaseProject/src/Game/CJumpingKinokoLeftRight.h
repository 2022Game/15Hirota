#ifndef CJUMPINGKINOKOLEFTRIGHT_H
#define CJUMPINGKINOKOLEFTRIGHT_H

#include "CJumpingKinokoMove.h"

// �v���C���[�𒵂˂�����L�m�R(���E)
class CJumpingKinokoLeftRight : public CJumpingKinokoMove
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
	CJumpingKinokoLeftRight(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime);
	// �f�X�g���N�^
	~CJumpingKinokoLeftRight();
};
#endif