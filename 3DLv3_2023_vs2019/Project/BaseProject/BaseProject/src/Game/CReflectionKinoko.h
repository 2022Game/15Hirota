#ifndef CREFLECTIONKINOKO_H
#define CREFLECTIONKINOKO_H

#include "CReflectionObject.h"

// �v���C���[�𒵂˕Ԃ�����L�m�R(�x�[�X)
class CReflectionKinoko : public CReflectionObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="modelPath">���f���p�X</param>
	CReflectionKinoko(const CVector& pos, const CVector& scale, const CVector& rot,
		std::string modelPath = "JumpingKinoko");

	// �f�X�g���N�^
	virtual ~CReflectionKinoko();
protected:
};
#endif