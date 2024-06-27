#include "CJumpingKinokoTurnRight.h"

// コンストラクタ
CJumpingKinokoTurnRight::CJumpingKinokoTurnRight(const CVector& pos, const CVector& scale, const CVector& rot,
	float angle, float dist, bool rotateangle)
	: CJumpingKinokoRotate(pos, scale, rot, angle, dist, rotateangle
		, "JumpingKinoko3Color")
{
}

// デストラクタ
CJumpingKinokoTurnRight::~CJumpingKinokoTurnRight()
{
}