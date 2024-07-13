#include "CJumpingKinokoLeftRight.h"
#include "CStageManager.h"

// �R���X�g���N�^
CJumpingKinokoLeftRight::CJumpingKinokoLeftRight(const CVector& pos, const CVector& scale, const CVector& rot,
	const CVector& move, float moveTime)
	: CJumpingKinokoMove(pos, scale, rot, move, moveTime, "JumpingKinoko3Color")
{
}

// �f�X�g���N�^
CJumpingKinokoLeftRight::~CJumpingKinokoLeftRight()
{
	CStageManager::RemoveTask(this);
}