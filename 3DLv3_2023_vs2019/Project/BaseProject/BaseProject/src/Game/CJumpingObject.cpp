#include "CJumpingObject.h"
#include "CPlayer.h"

CJumpingObject::CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot)
{
	mpModel = CResourceManager::Get<CModel>("FieldCube");
	mpColliderMesh = new CColliderMesh(this, ELayer::eJumpingCol, mpModel, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

CJumpingObject::~CJumpingObject()
{
	if (mpColliderMesh != nullptr)
	{
		delete mpColliderMesh;
		mpColliderMesh = nullptr;
	}
}

void CJumpingObject::Update()
{

}

void CJumpingObject::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}