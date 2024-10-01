#include "CNbFlUpDown2.h"
#include "CStageManager.h"

// �R���X�g���N�^
CNbFlUpDown2::CNbFlUpDown2(const CVector& pos, const CVector& scale, const CVector& rot,
	const CVector& move, float moveTime)
	: CNbFlMove2(pos, scale, rot, move, moveTime,
		"Number2")
{
}

// �f�X�g���N�^
CNbFlUpDown2::~CNbFlUpDown2()
{
	CStageManager::RemoveTask(this);
}