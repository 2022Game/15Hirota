#include "CGoalObject.h"
#include "CPlayer.h"

CGoalObject::CGoalObject(CModel* model, const CVector& pos, const CVector& scale, const CVector&rot)
	: mpModel(model)
{
	mpModel = CResourceManager::Get<CModel>("GoalModel");

	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eGoalCol,
		7.0f//0.5f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::eDamageCol });
	mpColliderSphere->SetCollisionTags({ ETag::ePlayer });
	// ゴールコライダーを少し上へずらす
	mpColliderSphere->Position(0.0f, 6.0f, 0.0f);
	//mpColliderSphere->SetEnable(false);

	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

CGoalObject::~CGoalObject()
{
	/*if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}*/

	if (mpColliderMesh != nullptr)
	{
		delete mpColliderMesh;
		mpColliderMesh = nullptr;
	}

	if (mpColliderSphere != nullptr)
	{
		delete mpColliderSphere;
		mpColliderSphere = nullptr;
	}
}

void CGoalObject::Update()
{
	
}

void CGoalObject::Render()
{
	mpModel->Render(Matrix());
}