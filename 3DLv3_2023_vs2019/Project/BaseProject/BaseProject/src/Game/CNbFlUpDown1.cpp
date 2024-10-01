#include "CNbFlUpDown1.h"
#include "CStageManager.h"

// �R���X�g���N�^
CNbFlUpDown1::CNbFlUpDown1(const CVector& pos, const CVector& scale, const CVector& rot,
	const CVector& move, float moveTime)
	: CNbFlMove1(pos, scale, rot, move, moveTime,
		"Number1")
{
}

// �f�X�g���N�^
CNbFlUpDown1::~CNbFlUpDown1()
{
	CStageManager::RemoveTask(this);
}