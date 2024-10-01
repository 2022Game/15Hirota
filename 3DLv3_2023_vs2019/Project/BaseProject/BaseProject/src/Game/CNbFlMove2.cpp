#include "CNbFlMove2.h"
#include "Maths.h"

// �R���X�g���N�^
CNbFlMove2::CNbFlMove2(const CVector& pos, const CVector& scale, const CVector& rot,
	const CVector& move, float moveTime,
	std::string modelPath)
	: CNumberFloor2(pos, scale, rot, modelPath)
	, mMoveVec(move)
	, mMoveTime(moveTime)
	, mDefaultPos(pos)
	, mMoveElapsedTime(0.0f)
{
}

// �f�X�g���N�^
CNbFlMove2::~CNbFlMove2()
{
}

// �X�V����
void CNbFlMove2::Update()
{
	if (mState != EState::Falling)
	{
		// �ړ�����
		float per = mMoveElapsedTime / mMoveTime;
		Position(mDefaultPos + mMoveVec * sinf(M_PI * 2.0f * per));

		mMoveElapsedTime += Time::DeltaTime();
		if (mMoveElapsedTime >= mMoveTime)
		{
			mMoveElapsedTime -= mMoveTime;
		}
	}
	else
	{

	}
	// �x�[�X�N���X�̍X�V����
	CNumberFloor2::Update();
}