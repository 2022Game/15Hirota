#ifndef CCANNON_H
#define CCANNON_H

#include "CCannonBase.h"

class CPlayer;

// �v���C���[�Ɍ������Ĕ��˂����C�N���X
class CCannon : public CCannonBase
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// /// <param name="modelPath">���f���̃p�X</param>
	CCannon(const CVector& pos, const CVector& scale, const CVector& rot,
		std::string modelPath = "Cannon");
	// �f�X�g���N�^
	~CCannon();

	// �X�V����
	void Update() override;

private:

	// ���ɑł܂ł̎��Ԍv��
	float mFireTime;
	// �łĂ邩�ǂ���
	bool mFire;

};
#endif