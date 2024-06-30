#include "COneShotFloorField.h"
#include "CCollisionManager.h"
#include "CCamera.h"

COneShotFloorField::COneShotFloorField()
	: CObjectBase(ETag::eFall,ETaskPriority::eFall)
{
	// 落下判定用のコライダー
	mpStageModel = CResourceManager::Get<CModel>("NumberFallCol");

	// 落下判定用のコライダー作成
	mpFallCol = new CColliderMesh(this, ELayer::eFall, mpStageModel, true);
	mpFallCol->SetCollisionTags({ ETag::ePlayer });
	mpFallCol->SetCollisionLayers({ ELayer::ePlayer });
}

COneShotFloorField::~COneShotFloorField()
{
	SAFE_DELETE(mpFallCol);
}

// 壁のコライダーが必要であれば実装
//CColliderMesh* COneShotFloorField::GetWallCol() const
//{
//	
//}

void COneShotFloorField::Update()
{

}

void COneShotFloorField::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
}