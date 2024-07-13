#include "CCircleLine.h"
#include "CStageManager.h"

// �R���X�g���N�^
CCircleLine::CCircleLine(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eObstacle, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
{
	mpCircle = CResourceManager::Get<CModel>("CircleLine");

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

// �f�X�g���N�^
CCircleLine::~CCircleLine()
{
	CStageManager::RemoveTask(this);
}

// �`�揈��
void CCircleLine::Render()
{
	mpCircle->SetColor(mColor);
	mpCircle->Render(Matrix());
}