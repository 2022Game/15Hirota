#include "CStone1.h"

CStone1::CStone1(const CVector& pos, const CVector& scale, const CVector& rot)
{
	mpModel = CResourceManager::Get<CModel>("Stone1");

	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eField,
		1.5f, true
	);
	mpColliderSphere->Position(0.0f, 1.0f, 0.0f);

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

CStone1::~CStone1()
{
	if (mpColliderSphere != nullptr)
	{
		delete mpColliderSphere;
		mpColliderSphere = nullptr;
	}
}

void CStone1::Update()
{

}

void CStone1::Render()
{
	mpModel->Render(Matrix());
}