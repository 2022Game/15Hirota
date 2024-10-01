#ifndef CNBFLMOVE1_H
#define CNBFLMOVE1_H

#include "CNumberFloor1.h"

// ������(1��)
class CNbFlMove1 : public CNumberFloor1
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
	CNbFlMove1(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime,
		std::string modelPath);
	// �f�X�g���N�^
	virtual ~CNbFlMove1();

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