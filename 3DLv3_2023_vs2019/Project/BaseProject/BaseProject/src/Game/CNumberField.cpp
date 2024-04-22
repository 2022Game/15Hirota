#include "CNumberField.h"
#include "CCollisionManager.h"
#include "CCamera.h"

CNumberField::CNumberField()
	: CObjectBase(ETag::eFall,ETaskPriority::eFall)
{
	// 落下判定用のコライダー
	mpStageModel = CResourceManager::Get<CModel>("NumberFallCol");

	// 1回で消滅する床のコライダー作成
	mpFallCol = new CColliderMesh(this, ELayer::eFall, mpStageModel, true);
	mpFallCol->SetCollisionTags({ ETag::ePlayer });
	mpFallCol->SetCollisionLayers({ ELayer::eDamageCol });
}

CNumberField::~CNumberField()
{
	SAFE_DELETE(mpFallCol);
}

// 壁のコライダーが必要であれば実装
//CColliderMesh* CNumberField::GetWallCol() const
//{
//	
//}

void CNumberField::Update()
{

}

void CNumberField::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
}