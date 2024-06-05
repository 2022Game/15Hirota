#ifndef CRINGBEAMER_H
#define CRINGBEAMER_H

#include "CObjectBase.h"
#include "CModel.h"

// �����O�r�[�}
class CRingBeamerUpper : public CObjectBase
{
public:

	CRingBeamerUpper(const CVector& pos, const CVector& scale, const CVector& rot);
	~CRingBeamerUpper();

	void Update() override;
	void Render() override;

private:
	// �����O�r�[�}���f��
	CModel* mpRingBeamerUpper;

	// ��Ԋ֘A
	// �����O�r�[�}�̏��
	enum class EState
	{
		eIdle,		// �ҋ@���
		eAttack,	// �U�����
		eAttackEnd,	// �U���I�����
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// �U�����
	void UpdateAttack();
	// �U���I�����
	void UpdateAttackEnd();

	// ���݂̏��
	EState mState;

	// �x�N�g���֘A
	CVector mStartPos;

	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �U���̃J�E���g
	int mAttackCount;
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// �����ʒu
	float mStartPosition;
	// �Ō�̈ʒu
	float mEndPosition;
	// �U���҂�����
	float mAttackWait;
	// �U���I����̑҂�����
	float mAttackEndWait;
	// �Ռ��g�͈�x����
	bool mIsAttackWave;

	// �v���C���[����������
	bool IsFoundPlayer() const;
};

class CRingBeamerLower : public CObjectBase
{
public:
	CRingBeamerLower(const CVector& pos, const CVector& scale, const CVector& rot);
	~CRingBeamerLower();

	void Update() override;
	void Render() override;
private:
	// �����O�r�[�}���f��(��)
	CModel* mpRingBeamerLower;

	CVector mStartPos;
};
#endif