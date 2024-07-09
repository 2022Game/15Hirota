#include "CReflectionMove.h"
#include "Maths.h"

// �R���X�g���N�^
CReflectionMove::CReflectionMove(const CVector& pos, const CVector& scale, const CVector& rot,
	const CVector& move, float moveTime,
	std::string modelPath)
	: CReflectionKinoko(pos, scale, rot, modelPath)
	, mMoveVec(move)
	, mMoveTime(moveTime)
	, mDefaultPos(pos)
	, mMoveElapsedTime(0.0f)
{
}

// �f�X�g���N�^
CReflectionMove::~CReflectionMove()
{
}

// �X�V����
void CReflectionMove::Update()
{
	// �x�[�X�N���X�̍X�V����
	CReflectionKinoko::Update();

	// �ړ�����
	float per = mMoveElapsedTime / mMoveTime;
	Position(mDefaultPos + mMoveVec * sinf(M_PI * 2.0f * per));

	mMoveElapsedTime += Time::DeltaTime();
	if (mMoveElapsedTime >= mMoveTime)
	{
		mMoveElapsedTime -= mMoveTime;
	}
}