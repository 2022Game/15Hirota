#include "CNbFlUpDown3.h"
#include "CStageManager.h"

// �R���X�g���N�^
CNbFlUpDown3::CNbFlUpDown3(const CVector& pos, const CVector& scale, const CVector& rot,
	const CVector& move, float moveTime)
	: CNbFlMove3(pos, scale, rot, move, moveTime,
		"Number3")
{
}

// �f�X�g���N�^
CNbFlUpDown3::~CNbFlUpDown3()
{
	CStageManager::RemoveTask(this);
}