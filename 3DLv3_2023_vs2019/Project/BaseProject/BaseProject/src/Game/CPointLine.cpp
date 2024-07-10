#include "CPointLine.h"

// �R���X�g���N�^
CPointLine::CPointLine(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eObstacle, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
{
	mpPointLine = CResourceManager::Get<CModel>("PointLine");

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

// �f�X�g���N�^
CPointLine::~CPointLine()
{

}

// �`�揈��
void CPointLine::Render()
{
	mpPointLine->SetColor(mColor);
	mpPointLine->Render(Matrix());
}