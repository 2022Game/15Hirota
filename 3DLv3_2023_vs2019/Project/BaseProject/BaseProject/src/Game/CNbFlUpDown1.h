#ifndef CNBFLUPDOWN1_H
#define CNBFLUPDOWN1_H

#include "CNbFlMove1.h"

// �㉺�ɓ�����(1��)
class CNbFlUpDown1 : public CNbFlMove1
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
	CNbFlUpDown1(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime);
	// �f�X�g���N�^
	~CNbFlUpDown1();
};
#endif