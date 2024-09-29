#include "CCircleNbFlRight3.h"
#include "CStageManager.h"

// �R���X�g���N�^
CCircleNbFlRight3::CCircleNbFlRight3(const CVector& pos, const CVector& scale, const CVector& rot,
	float angle, float dist, float speed, bool rotateangle)
	: CCircleNbFl3(pos, scale, rot, angle, dist, speed, rotateangle
		, "Number3")
{
}

// �f�X�g���N�^
CCircleNbFlRight3::~CCircleNbFlRight3()
{
	CStageManager::RemoveTask(this);
}