#ifndef CNBFLUPDOWN2_H
#define CNBFLUPDOWN2_H

#include "CNbFlMove2.h"

// �㉺�ɓ�����(2��)
class CNbFlUpDown2 : public CNbFlMove2
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
	CNbFlUpDown2(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime);
	// �f�X�g���N�^
	~CNbFlUpDown2();
};
#endif