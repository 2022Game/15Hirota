#include "CCircleLine.h"

// コンストラクタ
CCircleLine::CCircleLine(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eObstacle, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
{
	mpCircle = CResourceManager::Get<CModel>("CircleLine");

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

// デストラクタ
CCircleLine::~CCircleLine()
{

}

// 描画処理
void CCircleLine::Render()
{
	mpCircle->SetColor(mColor);
	mpCircle->Render(Matrix());
}