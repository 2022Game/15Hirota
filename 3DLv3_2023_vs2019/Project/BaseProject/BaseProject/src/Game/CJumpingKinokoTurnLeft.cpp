#include "CJumpingKinokoTurnLeft.h"

// �R���X�g���N�^
CJumpingKinokoTurnLeft::CJumpingKinokoTurnLeft(const CVector& pos, const CVector& scale, const CVector& rot,
	float angle, float dist, bool rotateangle)
	: CJumpingKinokoRotate(pos, scale, rot, angle, dist, rotateangle
		, "JumpingKinoko2Color")
{
}

// �f�X�g���N�^
CJumpingKinokoTurnLeft::~CJumpingKinokoTurnLeft()
{
}