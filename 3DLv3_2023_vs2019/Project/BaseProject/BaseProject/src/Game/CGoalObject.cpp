#include "CGoalObject.h"
#include "CPlayer.h"

CGoalObject::CGoalObject(CModel* model, const CVector& pos, const CVector& scale, const CVector& rot)
	: mpModel(model)
	, mpGoalPost(model)
{
	mpModel = CResourceManager::Get<CModel>("GoalCube");
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);

	//CModel* post = CResourceManager::Get<CModel>("GoalPost");
	mpGoalPost = CResourceManager::Get<CModel>("GoalPost");


	mpColliderLine = new CColliderLine
	(
		this, ELayer::eGoalCol,
		CVector(0.0f, 5.0f, 0.0f),
		CVector(0.0f, 30.0, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eDamageCol });
	mpColliderLine->SetCollisionTags({ ETag::ePlayer });


	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eGoalCol,
		2.0f//0.5f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::eDamageCol });
	mpColliderSphere->SetCollisionTags({ ETag::ePlayer });
	// ゴールコライダーを少し上へずらす
	mpColliderSphere->Position(0.0f, 20.0f, 0.0f);
	

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

CGoalObject::~CGoalObject()
{
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
	
	if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}
}

void CGoalObject::Update()
{
	
}

void CGoalObject::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
	mpGoalPost->SetColor(mColor);
	mpGoalPost->Render(Matrix());
}