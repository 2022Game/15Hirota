#ifndef CREFLECTIONACTIONKINOKO_H
#define CREFLECTIONACTIONKINOKO_H

#include "CReflectionKinoko.h"

// �v���C���[�𒵂˕Ԃ�����L�m�R
class CReflectionActionKinoko : public CReflectionKinoko
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CReflectionActionKinoko(const CVector& pos, const CVector& scale, const CVector& rot);

	// �f�X�g���N�^
	~CReflectionActionKinoko();
};
#endif