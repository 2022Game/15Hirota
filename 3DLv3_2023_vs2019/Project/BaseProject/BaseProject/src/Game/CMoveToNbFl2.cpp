#include "CMoveToNbFl2.h"
#include "CStageManager.h"

// rot�̌�Ƀ��f���p�X��I���ł���
CMoveToNbFl2::CMoveToNbFl2(const CVector& scale, const CVector& rot
	, float waitTime)
	: CNumberFloor2(CVector::zero, scale, rot)
	, mMoveState(EMoveState::eIdle)
	, mIsReturn(false)
	, mIsReturnMove(false)
	, mMoveStartIndex(0)
	, mMoveEndIndex(0)
	, mWaitTime(waitTime)
	, mMoveElapsedTime(0.0f)
{
}

CMoveToNbFl2::~CMoveToNbFl2()
{
	CStageManager::RemoveTask(this);
}

// �ړ��|�C���g��ǉ�
void CMoveToNbFl2::AddMovePoint(const CVector& point, float time)
{
	MovePoint mp;
	mp.point = point;
	mp.time = time;
	mMovePoints.push_back(mp);

	// 1�ڂ̃|�C���g�ł���΁A���݂̍��W�ɔ��f�ł���
	if (mMovePoints.size() == 1)
	{
		Position(point);
	}
}

// �Ō�̈ړ��|�C���g�Ɉړ���A�t���[�g�ɖ߂邩�ǂ���
void CMoveToNbFl2::SetReturnRoute(bool isReturn)
{
	mIsReturn = isReturn;
}

// ��Ԃ�؂�ւ���
void CMoveToNbFl2::ChangeMoveState(EMoveState state)
{
	if (state == mMoveState) return;
	mMoveState = state;
}

// �ړ����[�g���X�V
void CMoveToNbFl2::UpdateMoveRoute()
{
	// �����[�g�ňړ���
	if (!mIsReturnMove)
	{
		// �ړ���́A���݂̈ړ��|�C���g + 1
		mMoveEndIndex = mMoveStartIndex + 1;
		// �ړ���̃C���f�b�N�X�l���ړ��|�C���g�̐��𒴂�����
		if (mMoveEndIndex >= mMovePoints.size())
		{
			// �t���[�g�ňړ�����ꍇ
			if (mIsReturn)
			{
				// ���݂̈ړ��|�C���g - 1
				mMoveEndIndex = mMoveStartIndex - 1;
				// �t���[�g�ړ����̃t���O���I��
				mIsReturnMove = true;
			}
			// �J�n�ʒu�ɖ߂�
			else
			{
				mMoveEndIndex = 0;
			}
		}
	}
	// �t���[�g�ňړ���
	else
	{
		// �ړ���́A���݂̈ړ��|�C���g - 1
		mMoveEndIndex = mMoveStartIndex - 1;
		// ���݂̈ړ��|�C���g����O�̈ړ��|�C���g�����݂��Ȃ��ꍇ
		if (mMoveEndIndex < 0)
		{
			// �ړ���́A���݂̈ړ��|�C���g + 1
			mMoveEndIndex = mMoveStartIndex + 1;
			// �t���[�g�ړ��t���O���I�t�ɂ���
			mIsReturnMove = false;
		}
	}
}

// �ҋ@��Ԃ̍X�V����
void CMoveToNbFl2::UpdateIdle()
{
	// �҂����Ԃ��o�߂��Ă��Ȃ�
	if (mMoveElapsedTime < mWaitTime)
	{
		mMoveElapsedTime += Time::DeltaTime();
	}
	// �҂����Ԃ��o�߂���
	else
	{
		// �o�ߎ��Ԃ���҂����ԕ�����
		mMoveElapsedTime -= mWaitTime;
		// ���Ɉړ�����|�C���g������
		UpdateMoveRoute();
		// �ړ���Ԃֈڍs
		ChangeMoveState(EMoveState::eMove);
	}
}

// �ړ���Ԃ̍X�V����
void CMoveToNbFl2::UpdateMove()
{
	// �J�n�n�_�ƏI���n�_�̈ړ��|�C���g���擾
	// &��t���Ȃ��ƃR�s�[�����̂�2�{���������g���Ă��܂�
	const MovePoint& start = mMovePoints[mMoveStartIndex];
	const MovePoint& end = mMovePoints[mMoveEndIndex];
	// �ړ����Ԃ��擾(�����[�g�Ƌt���[�g�ŎQ�Ɛ��ς���)
	float moveTime = mIsReturnMove ? start.time : end.time;

	// �ړ����Ԃ��o�߂��Ă��Ȃ�
	if (mMoveElapsedTime < moveTime)
	{
		// �ړ����Ԃ̊����ŁA���݈ʒu�����߂�
		float percent = mMoveElapsedTime / moveTime;
		CVector pos = CVector::Lerp(start.point, end.point, percent);
		Position(pos);

		// ���Ԃ��o��
		mMoveElapsedTime += Time::DeltaTime();
	}
	// �ړ����Ԃ��o�߂���
	else
	{
		// �I���ʒu�ɔz�u
		Position(end.point);
		// ���݂̃C���f�b�N�X�l�Ɉړ���̃C���f�b�N�X�l��ݒ�
		mMoveStartIndex = mMoveEndIndex;

		mMoveElapsedTime -= moveTime;
		// �ҋ@��Ԃֈڍs
		ChangeMoveState(EMoveState::eIdle);
	}
}

// �X�V
void CMoveToNbFl2::Update()
{
	if (mState != EState::Falling)
	{
		switch (mMoveState)
		{
		case EMoveState::eIdle:
			UpdateIdle();
			break;
		case EMoveState::eMove:
			UpdateMove();
			break;
		}
	}
	else
	{

	}

	CNumberFloor2::Update();
}