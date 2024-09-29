#ifndef CNUMBERFLOOR2_H
#define CNUMBERFLOOR2_H

#include "CNumberFloorBase.h"

// �񐔂ŗ����鏰(2��)�N���X
class CNumberFloor2 : public CNumberFloorBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="scale">�X�P�[���l</param>
	CNumberFloor2(const CVector& pos, const CVector& scale, const CVector& rot,
		std::string modelPath = "Number2");

	// �f�X�g���N�^
	virtual ~CNumberFloor2();

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