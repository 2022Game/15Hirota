#include "CJumpingKinokoRotate.h"
#include "Maths.h"

// �R���X�g���N�^
CJumpingKinokoRotate::CJumpingKinokoRotate(const CVector& pos, const CVector& scale, const CVector& rot,
	float angle, float dist, float speed, bool rotateangle,
	std::string modelPath)
	: CJumpingKinoko(pos, scale, rot, modelPath)
	, mAngle(angle)
	, mDistance(dist)
	, mDefaultPos(pos)
	, mSpeed(speed)
	, mElapsedTime(0.0f)
{
	mRotateAngle = rotateangle;
}

// �f�X�g���N�^
CJumpingKinokoRotate::~CJumpingKinokoRotate()
{
}

// �X�V����
void CJumpingKinokoRotate::Update()
{
	// �x�[�X�N���X�̍X�V����
	CJumpingKinoko::Update();

	// ��]
	CVector pos =  CVector::zero;
	pos.X(cosf(Math::DegreeToRadian(mAngle)) * mDistance);
	pos.Z(sinf(Math::DegreeToRadian(mAngle)) * mDistance);
	pos.Y(0.0f);
	Position(mDefaultPos + pos);

	// ����
	/*CVector dir = Position();
	dir.Y(0.0f);
	dir.Normalized();
	Rotation(CQuaternion::LookRotation(dir));*/
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