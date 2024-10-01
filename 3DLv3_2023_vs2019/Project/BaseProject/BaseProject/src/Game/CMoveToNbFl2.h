#ifndef CMOVETONBFL2_H
#define CMOVETONBFL2_H

#include "CNumberFloor2.h"

// �w�肵���ړ��|�C���g�Ԃ��ړ����鐧����(2��)
class CMoveToNbFl2 : public CNumberFloor2
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="waitTime">�ړ��҂�����</param>
	CMoveToNbFl2(const CVector& scale, const CVector& rot, float waitTime);
	// �f�X�g���N�^
	virtual ~CMoveToNbFl2();

	/// <summary>
	/// �ړ��|�C���g��ǉ�
	/// </summary>
	/// <param name="point">�ړ���̍��W</param>
	/// <param name="time">�ړ��ɂ����鎞��</param>
	void AddMovePoint(const CVector& point, float time);

	// �Ō�̈ړ��|�C���g�Ɉړ���A�t���[�g�ɖ߂邩�ǂ���
	void SetReturnRoute(bool isReturn);

	// �X�V����
	void Update() override;

private:
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// �ړ���Ԃ̍X�V����
	void UpdateMove();
	// �ړ����[�g���X�V
	void UpdateMoveRoute();
	// ���
	enum EMoveState
	{
		eIdle,	// �ҋ@���
		eMove,	// �ړ����
	};
	// ��Ԃ�؂�ւ���
	void ChangeMoveState(EMoveState state);
	// ���݂̏��
	EMoveState mMoveState;

	// �ړ��|�C���g�̃f�[�^
	struct MovePoint
	{
		CVector point;	// �ړ���̍��W
		float time;		// �ړ��ɂ����鎞��
	};
	// �ړ��|�C���g�̃��X�g
	std::vector<MovePoint> mMovePoints;

	// �t���[�g�Ŗ߂邩�ǂ���
	bool mIsReturn;
	// �t���[�g�Ŗ߂��Ă���r�����ǂ���
	bool mIsReturnMove;
	// �ړ��J�n���̈ړ��|�C���g�̃C���f�b�N�X�l
	int mMoveStartIndex;
	// �ړ���̈ړ��|�C���g�̃C���f�b�N�X�l
	int mMoveEndIndex;
	// �ړ��҂�����
	float mWaitTime;
	// �ړ����Ԍv���p
	float mMoveElapsedTime;
};
#endif