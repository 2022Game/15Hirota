#include "CJumpingKinokoTurnRight.h"

// �R���X�g���N�^
CJumpingKinokoTurnRight::CJumpingKinokoTurnRight(const CVector& pos, const CVector& scale, const CVector& rot,
	float angle, float dist, float speed, bool rotateangle)
	: CJumpingKinokoRotate(pos, scale, rot, angle, dist, speed, rotateangle
		, "JumpingKinoko3Color")
{
}

// �f�X�g���N�^
CJumpingKinokoTurnRight::~CJumpingKinokoTurnRight()
{
}