#include "CRotationg.h"
#include "Maths.h"

#define ROTATE_Y  1.0f

CRotationg::CRotationg(const CVector& pos, const CVector& scale,
	float rotateSpeedY)
	: mRotateSpeedY(rotateSpeedY)
{
	mpRotationgModel = CResourceManager::Get<CModel>("Rotationg");

	CModel* rotationgCol = CResourceManager::Get<CModel>("RotationgCol");
	mpRotationgCol = new CColliderMesh(this, ELayer::eField, rotationgCol, true);

	SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));

	Position(pos);
	Scale(scale);
}

CRotationg::~CRotationg()
{
	SAFE_DELETE(mpRotationgCol);
}

void CRotationg::Update()
{
	Rotate(0.0f, mRotateSpeedY, 0.0f);
}

void CRotationg::Render()
{
	mpRotationgModel->SetColor(mColor);
	mpRotationgModel->Render(Matrix());
}