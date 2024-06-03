#include "CRingBeamer.h"
#include "CCharaBase.h"
#include "Maths.h"
#include "CBiribiri.h"
#include "CStageManager.h"

// �U���҂�����
#define ATTACK_WAIT_TIME 0.4f
// �U���I����̑҂�����
#define ATTACK_END_TIME 2.0f
// �ҋ@���
#define WAIT_TIME 5.0f
// �߂���
#define RETURN_TIME 5.0f
#define ATTACK_COUNTER 3

// �R���X�g���N�^
CRingBeamerUpper::CRingBeamerUpper(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eRingBeam, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mState(EState::eIdle)
	, mStateStep(0)
	, mAttackCount(0)
	, mElapsedTime(0.0f)
	, mStartPosition(0.0f)
	, mEndPosition(0.0f)
	, mAttackWait(0.0f)
	, mAttackEndWait(0.0f)
	, mIsAttackWave(false)
{
	// �����O�r�[�}(��)���f���擾
	mpRingBeamerUpper = CResourceManager::Get<CModel>("RingBeamerUP");

	Position(pos);
	Scale(scale);
	Rotation(rot);

	mStartPos = Position();
}

// �f�X�g���N�^
CRingBeamerUpper::~CRingBeamerUpper()
{

}

// ��Ԃ�؂�ւ���
void CRingBeamerUpper::ChangeState(EState state)
{
	mState = state;
	mElapsedTime = 0.0f;
	mStateStep = 0;
}

// �ҋ@��Ԃ̏���
void CRingBeamerUpper::UpdateIdle()
{
	if (mAttackWait >= WAIT_TIME)
	{
		mStartPosition = 0.0f;
		mElapsedTime = 0.0f;
		mAttackWait = 0.0f;
		mAttackEndWait = 0.0f;
		mEndPosition = -3.0f;
		ChangeState(EState::eAttack);
	}
	mAttackWait += Time::DeltaTime();
}

// �U�����̍X�V����
void CRingBeamerUpper::UpdateAttack()
{
	switch (mStateStep)
	{
		// �U������
	case 0:
		if (mElapsedTime < ATTACK_WAIT_TIME)
		{
			float per = mElapsedTime / ATTACK_WAIT_TIME;
			float PositionY = Math::Lerp
			(
				mStartPosition,
				mEndPosition,
				per
			);
			mElapsedTime += Time::DeltaTime();

			Position(mStartPos + CVector(0.0f, PositionY, 0.0f));
		}
		else
		{
			if (!mIsAttackWave)
			{
				mIsAttackWave = true;
				// �����O�r�[���𔭎�
				CBiribiri* biribiri = new CBiribiri
				(
					this,
					Position()
				);
				// �����O�r�[���G�t�F�N�g�̐F�ݒ�
				biribiri->SetColor(CColor(1.0f, 1.0f, 0.0f));
			}

			Position(mStartPos + CVector(0.0f, mEndPosition, 0.0f));
			mAttackEndWait += Time::DeltaTime();
			if (mAttackEndWait >= ATTACK_WAIT_TIME)
			{
				mElapsedTime = 0.0f;
				mAttackEndWait = 0.0f;
				mStateStep++;
			}
		}
		break;
		// ���ɖ߂�
	case 1:
		if (mElapsedTime < ATTACK_WAIT_TIME)
		{
			float per = mElapsedTime / ATTACK_WAIT_TIME;
			float PositionY = Math::Lerp
			(
				mEndPosition,
				mStartPosition,
				per
			);
			mElapsedTime += Time::DeltaTime();

			Position(mStartPos + CVector(0.0f, PositionY, 0.0f));
		}
		else
		{
			// �J�E���g��������������
			if (mAttackCount < ATTACK_COUNTER)
			{
				// �J��Ԃ�
				mAttackCount++;
				mIsAttackWave = false;
				mStateStep = 0;
				mAttackWait = 0.0f;
				mElapsedTime = 0.0f;
				Position(mStartPos + CVector(0.0f, mStartPosition, 0.0f));
			}
			else
			{
				mAttackCount = 0;
				mIsAttackWave = false;
				ChangeState(EState::eIdle);
			}
			break;
		}
		break;
	}
}

// �U���I�����̍X�V����
void CRingBeamerUpper::UpdateAttackEnd()
{

}

 // �X�V����
void CRingBeamerUpper::Update()
{
	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::eIdle:
		UpdateIdle();
		break;
		// �U�����
	case EState::eAttack:
		UpdateAttack();
		break;
		// �U���I�����
	case EState::eAttackEnd:
		UpdateAttackEnd();
		break;
	}
	CDebugPrint::Print("mAttackWait:%f\n", mAttackWait);
}

// �`�揈��
void CRingBeamerUpper::Render()
{
	mpRingBeamerUpper->SetColor(mColor);
	mpRingBeamerUpper->Render(Matrix());
}

CRingBeamerLower::CRingBeamerLower(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eRingBeam, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
{
	// �����O�r�[�}(��)���f���擾
	mpRingBeamerLower = CResourceManager::Get<CModel>("RingBeamerLO");


	Position(pos);
	Scale(scale);
	Rotation(rot);

	mStartPos = Position();
}

CRingBeamerLower::~CRingBeamerLower()
{

}

void CRingBeamerLower::Update()
{

}

void CRingBeamerLower::Render()
{
	mpRingBeamerLower->SetColor(mColor);
	mpRingBeamerLower->Render(Matrix());
}