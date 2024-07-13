#include "CJumpingKinokoTurnLeft.h"
#include "CStageManager.h"

// �R���X�g���N�^
CJumpingKinokoTurnLeft::CJumpingKinokoTurnLeft(const CVector& pos, const CVector& scale, const CVector& rot,
	float angle, float dist, float speed, bool rotateangle)
	: CJumpingKinokoRotate(pos, scale, rot, angle, dist, speed, rotateangle
		, "JumpingKinoko2Color")
{
}

// �f�X�g���N�^
CJumpingKinokoTurnLeft::~CJumpingKinokoTurnLeft()
{
	CStageManager::RemoveTask(this);
}