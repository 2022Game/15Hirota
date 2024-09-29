#ifndef CNUMBERFLOOR1_H
#define CNUMBERFLOOR1_H

#include "CNumberFloorBase.h"

// �񐔂ŗ����鏰(1��)�N���X
class CNumberFloor1 : public CNumberFloorBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="scale">�X�P�[���l</param>
	CNumberFloor1(const CVector& pos, const CVector& scale, const CVector& rot,
		std::string modelPath = "Number1");

	// �f�X�g���N�^
	virtual ~CNumberFloor1();

	// �v���C���[�ҋ@���
	virtual void UpdateWaiting();

	void Update() override;

protected:
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// ��]����
	bool mRotateAngle;
};
#endif