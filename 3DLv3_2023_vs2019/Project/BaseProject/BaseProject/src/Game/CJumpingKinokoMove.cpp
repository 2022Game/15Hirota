#include "CJumpingKinokoMove.h"
#include "Maths.h"

// �R���X�g���N�^
CJumpingKinokoMove::CJumpingKinokoMove(const CVector& pos, const CVector& scale, const CVector& rot,
	const CVector& move, float moveTime,
	std::string modelPath)
	: CJumpingKinoko(pos, scale, rot, modelPath)
	, mMoveVec(move)
	, mMoveTime(moveTime)
	, mDefaultPos(pos)
	, mMoveElapsedTime(0.0f)
{
}

// �f�X�g���N�^
CJumpingKinokoMove::~CJumpingKinokoMove()
{
}

// �X�V����
void CJumpingKinokoMove::Update()
{
	// �x�[�X�N���X�̍X�V����
	CJumpingKinoko::Update();

	// �ړ�����
	float per = mMoveElapsedTime / mMoveTime;
	Position(mDefaultPos + mMoveVec * sinf(M_PI * 2.0f * per));

	mMoveElapsedTime += Time::DeltaTime();
	if (mMoveElapsedTime >= mMoveTime)
	{
		mMoveElapsedTime -= mMoveTime;
	}
}