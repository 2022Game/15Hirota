#include "CGoalObject.h"

CGoalObject::CGoalObject(CModel* model, const CVector& pos, const CVector& scale, const CVector&rot)
	: mpModel(model)
{
	mpModel = CResourceManager::Get<CModel>("GoalModel");

	mpColliderLine = new CColliderLine(this, ELayer::eGoalCol,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 50.0f, 0.0f),
		true, 1.0f);
	mpColliderLine->SetCollisionLayers({ ELayer::ePlayer });

	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

CGoalObject::~CGoalObject()
{
	if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}

	if (mpColliderMesh != nullptr)
	{
		delete mpColliderMesh;
		mpColliderMesh = nullptr;
	}
}

void CGoalObject::Update()
{

}

void CGoalObject::Render()
{
	mpModel->Render(Matrix());
}