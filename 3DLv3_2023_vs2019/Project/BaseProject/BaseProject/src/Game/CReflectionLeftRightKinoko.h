#ifndef CREFLECTIONLEFTRIGHTKINOKO_H
#define CREFLECTIONLEFTRIGHTKINOKO_H

#include "CReflectionMove.h"

// �v���C���[�𒵂˕Ԃ�����L�m�R(���E)
class CReflectionLeftRightKinoko : public CReflectionMove
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
	CReflectionLeftRightKinoko(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime);
	// �f�X�g���N�^
	~CReflectionLeftRightKinoko();
};
#endif