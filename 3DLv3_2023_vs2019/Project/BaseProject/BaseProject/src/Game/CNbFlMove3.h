#ifndef CNBFLMOVE3_H
#define CNBFLMOVE3_H

#include "CNumberFloor3.h"

// ������(3��)
class CNbFlMove3 : public CNumberFloor3
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
	CNbFlMove3(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime,
		std::string modelPath);
	// �f�X�g���N�^
	virtual ~CNbFlMove3();

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