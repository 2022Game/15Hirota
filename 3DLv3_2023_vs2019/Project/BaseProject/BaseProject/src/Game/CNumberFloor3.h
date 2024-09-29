#ifndef CNUMBERFLOOR3_H
#define CNUMBERFLOOR3_H

#include "CNumberFloorBase.h"

// �񐔂ŗ����鏰(3��)�N���X
class CNumberFloor3 : public CNumberFloorBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="scale">�X�P�[���l</param>
	CNumberFloor3(const CVector& pos, const CVector& scale, const CVector& rot,
		std::string modelPath = "Number3");

	// �f�X�g���N�^
	virtual ~CNumberFloor3();

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