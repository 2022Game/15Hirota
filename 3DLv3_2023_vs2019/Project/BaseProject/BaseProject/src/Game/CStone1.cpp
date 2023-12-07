#include "CStone1.h"

CStone1::CStone1(CModel* model, const CVector& pos, const CVector& scale, const CVector& rot)
	: mpModel(model)
{
	mpModel = CResourceManager::Get<CModel>("Stone1");

	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

CStone1::~CStone1()
{
	if (mpColliderMesh != nullptr)
	{
		delete mpColliderMesh;
		mpColliderMesh = nullptr;
	}
}

void CStone1::Update()
{

}

void CStone1::Render()
{
	mpModel->Render(Matrix());
}