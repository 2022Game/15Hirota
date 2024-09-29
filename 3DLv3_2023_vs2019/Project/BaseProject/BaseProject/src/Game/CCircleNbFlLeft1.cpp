#include "CCircleNbFlLeft1.h"
#include "CStageManager.h"

// �R���X�g���N�^
CCircleNbFlLeft1::CCircleNbFlLeft1(const CVector& pos, const CVector& scale, const CVector& rot,
	float angle, float dist, float speed, bool rotateangle)
	: CCircleNbFl1(pos, scale, rot, angle, dist, speed, rotateangle
		, "Number1")
{
}

// �f�X�g���N�^
CCircleNbFlLeft1::~CCircleNbFlLeft1()
{
	CStageManager::RemoveTask(this);
}