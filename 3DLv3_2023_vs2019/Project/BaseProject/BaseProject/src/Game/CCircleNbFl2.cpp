#include "CCircleNbFl2.h"
#include "Maths.h"

// �R���X�g���N�^
CCircleNbFl2::CCircleNbFl2(const CVector& pos, const CVector& scale, const CVector& rot,
	float angle, float dist, float speed, bool rotateangle,
	std::string modelPath)
	: CNumberFloor2(pos, scale, rot)
	, mAngle(angle)
	, mDistance(dist)
	, mDefaultPos(pos)
	, mSpeed(speed)
	, mElapsedRotateTime(0.0f)
{
	mRotateAngle = rotateangle;
}

// �f�X�g���N�^
CCircleNbFl2::~CCircleNbFl2()
{
}

// �X�V����
void CCircleNbFl2::Update()
{
	if (mState != EState::Falling)
	{
		// ��]
		CVector pos = CVector::zero;
		pos.X(cosf(Math::DegreeToRadian(mAngle)) * mDistance);
		pos.Z(sinf(Math::DegreeToRadian(mAngle)) * mDistance);
		pos.Y(0.0f);
		Position(mDefaultPos + pos);

		if (mRotateAngle)
		{
			mAngle += mSpeed * Time::DeltaTime();
			if (mAngle >= 360.0f) mAngle -= 360.0f;
		}
		else
		{
			mAngle -= mSpeed * Time::DeltaTime();
			if (mAngle >= 360.0f) mAngle += 360.0f;
		}
	}
	else
	{
		// �������Ȃ�
	}
	// �x�[�X�N���X�̍X�V����
	CNumberFloor2::Update();
}