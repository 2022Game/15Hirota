#ifndef CNBFLMOVE2_H
#define CNBFLMOVE2_H

#include "CNumberFloor2.h"

// ������(2��)
class CNbFlMove2 : public CNumberFloor2
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
	CNbFlMove2(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime,
		std::string modelPath);
	// �f�X�g���N�^
	virtual ~CNbFlMove2();

	// �X�V����
	void Update() override;

private:
	// �ړ�����
	CVector mMoveVec;
	// ���̈ʒu
	CVector mDefaultPos;

	// �ړ����Ԍv���p
	float mMoveElapsedTime;
	// �ړ�����
	float mMoveTime;
};
#endif