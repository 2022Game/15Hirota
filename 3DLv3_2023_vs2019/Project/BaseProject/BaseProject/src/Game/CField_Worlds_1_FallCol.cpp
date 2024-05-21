#include "CField_Worlds_1_FallCol.h"
#include "CCollisionManager.h"
#include "CCamera.h"

CField_Worlds_1_FallCol::CField_Worlds_1_FallCol()
	: CObjectBase(ETag::eFall,ETaskPriority::eFall)
{
	// 落下判定用のコライダー
	CModel* fallCol = CResourceManager::Get<CModel>("FallCol");
	mpFallCol = new CColliderMesh(this, ELayer::eFall, fallCol, true);
	mpFallCol->SetCollisionTags({ ETag::ePlayer });
	mpFallCol->SetCollisionLayers({ ELayer::eDamageCol });
}

CField_Worlds_1_FallCol::~CField_Worlds_1_FallCol()
{
	SAFE_DELETE(mpFallCol);
}

void CField_Worlds_1_FallCol::Update()
{

}

void CField_Worlds_1_FallCol::Render()
{

}