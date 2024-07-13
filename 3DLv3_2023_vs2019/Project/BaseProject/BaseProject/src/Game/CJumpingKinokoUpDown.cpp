#include "CJumpingKinokoUpDown.h"
#include "CStageManager.h"

// �R���X�g���N�^
CJumpingKinokoUpDown::CJumpingKinokoUpDown(const CVector& pos, const CVector& scale, const CVector& rot,
	const CVector& move, float moveTime)
	: CJumpingKinokoMove(pos, scale, rot, move, moveTime,
		"JumpingKinoko2Color")
{
}

// �f�X�g���N�^
CJumpingKinokoUpDown::~CJumpingKinokoUpDown()
{
	CStageManager::RemoveTask(this);
}