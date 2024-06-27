#ifndef CJUMPINGKINOKO_H
#define CJUMPINGKINOKO_H

#include "CJumpingObject.h"

// �v���C���[�𒵂˂�����L�m�R
class CJumpingKinoko : public CJumpingObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="modelPath">���f���p�X</param>
	CJumpingKinoko(const CVector& pos, const CVector& scale, const CVector& rot,
		std::string modelPath = "JumpingKinoko");

	// �f�X�g���N�^
	virtual ~CJumpingKinoko();
protected:
	// ��]����
	bool mRotateAngle;
};
#endif