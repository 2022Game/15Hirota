#ifndef CNBFLUPDOWN3_H
#define CNBFLUPDOWN3_H

#include "CNbFlMove3.h"

// �㉺�ɓ�����(3��)
class CNbFlUpDown3 : public CNbFlMove3
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
	CNbFlUpDown3(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime);
	// �f�X�g���N�^
	~CNbFlUpDown3();
};
#endif