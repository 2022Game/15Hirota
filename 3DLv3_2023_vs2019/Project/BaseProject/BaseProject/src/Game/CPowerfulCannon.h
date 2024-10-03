#ifndef CPOWERFULCANNON_H
#define CPOWERFULCANNON_H

#include "CCannonBase.h"

class CPlayer;

// �΍�������C�N���X
class CPowerfulCannon : public CCannonBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="modelPath">���f���̃p�X</param>
	CPowerfulCannon(const CVector& pos, const CVector& scale, const CVector& rot,
		std::string modelPath = "Cannon");
	// �f�X�g���N�^
	~CPowerfulCannon();

	// �X�V����
	void Update() override;
	
private:

	// ���ɑł܂ł̎��Ԍv��
	float mFireTime;
	// �łĂ邩�ǂ���
	bool mFire;
	
};
#endif