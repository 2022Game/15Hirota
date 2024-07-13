#include "CRingBeamer.h"
#include "CCharaBase.h"
#include "Maths.h"
#include "CBiribiri.h"
#include "CStageManager.h"
#include "CPlayer.h"

// �U���҂�����
#define ATTACK_WAIT_TIME 0.3f
// �U���I����̑҂�����
#define ATTACK_END_TIME 2.0f
// �ҋ@���
#define WAIT_TIME 2.0f
// �߂���
#define RETURN_TIME 5.0f
// �U����
#define ATTACK_COUNTER 3
// ����p�̊p�x
#define FOV_ANGLE 150.0f

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
	CStageManager::RemoveTask(this);
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
	if (IsFoundPlayer())
	{
		if (mAttackWait >= WAIT_TIME)
		{
			mStartPosition = 0.0f;
			mElapsedTime = 0.0f;
			mAttackWait = 0.0f;
			mAttackEndWait = 0.0f;
			mEndPosition = -4.0f;
			ChangeState(EState::eAttack);
		}
		mAttackWait += Time::DeltaTime();
	}
	else
	{
		mAttackCount = 0;
		mAttackWait = 0.0f;
	}
}

// �U�����̍X�V����
void CRingBeamerUpper::UpdateAttack()
{
	if (!IsFoundPlayer())
	{
		mIsAttackWave = false;
		mStateStep = 0;
		mElapsedTime = 0.0f;
		mAttackEndWait = 0.0f;
		Position(mStartPos);
		ChangeState(EState::eIdle);
		return;
	}

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
					Position() + CVector(0.0f, 2.0f, 0.0f)
				);
				// �����O�r�[���G�t�F�N�g�̐F�ݒ�
				biribiri->SetColor(CColor(1.0f, 1.0f, 0.0f));
				CStageManager::AddTask(biribiri);
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
			if (mAttackCount <= ATTACK_COUNTER)
			{
				// �J��Ԃ�
				mAttackCount += 1;
				mIsAttackWave = false;
				mStateStep = 0;
				mAttackWait = 0.0f;
				mElapsedTime = 0.0f;
				Position(mStartPos + CVector(0.0f, mStartPosition, 0.0f));
			}
			else if (mAttackCount >= ATTACK_COUNTER)
			{
				mAttackCount = 0;
				mElapsedTime = 0.0f;
				mAttackWait = 0.0f;
				mIsAttackWave = false;
				Position(mStartPos + CVector(0.0f, mStartPosition, 0.0f));
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
	//CDebugPrint::Print("mAttackCount%d\n", mAttackCount);
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
	//CDebugPrint::Print("mAttackWait:%f\n", mAttackWait);
}

// �`�揈��
void CRingBeamerUpper::Render()
{
	mpRingBeamerUpper->SetColor(mColor);
	mpRingBeamerUpper->Render(Matrix());
}

// �v���C���[����������
bool CRingBeamerUpper::IsFoundPlayer() const
{
	CVector playerPos = CPlayer::Instance()->Position();
	CVector beamer = Position();

	// �v���C���[�Ƃ̋������v�Z����
	float distance = (playerPos - beamer).Length();
	const float detectionRadius = FOV_ANGLE;

	// �v���C���[�Ƃ̋��������o���a�ȓ��ł���΁A�v���C���[��F������
	if (distance <= detectionRadius)
	{
		return true;
	}

	return false;

	//CVector playerPos = CPlayer::Instance()->Position();
	//CVector beamer = Position();

	//CVector toPlayer = (playerPos - beamer).Normalized();
	//CVector forward = Matrix().VectorZ().Normalized();

	//float dot = forward.Dot(toPlayer);

	//// ����p�̔������v�Z����
	//float halfFOV = FOV_ANGLE * 0.5f;

	//// ����p�̔�����菬�������v���C���[�Ƃ̋��������͈͈ȓ��ł���΁A�v���C���[��F������
	//if (dot >= cosf(halfFOV * M_PI / 180.0f))
	//{
	//	float distance = (playerPos - beamer).Length();
	//	const float chaseRange = 100.0f;

	//	if (distance <= chaseRange)
	//	{
	//		return true;
	//	}
	//}

	//return false;
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
	CStageManager::RemoveTask(this);
}

void CRingBeamerLower::Update()
{

}

void CRingBeamerLower::Render()
{
	mpRingBeamerLower->SetColor(mColor);
	mpRingBeamerLower->Render(Matrix());
}