#include "CClimbWall.h"

// コンストラクタ
CClimbWall::CClimbWall()
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
{
	// 登れるモデル取得
	mpWallModel = CResourceManager::Get<CModel>("Stage2Climb");

	mpWallCol = new CColliderMesh(this, ELayer::eClimb, mpWallModel, true);
	mpWallCol->SetCollisionTags({ ETag::ePlayer });
}

// デストラクタ
CClimbWall::~CClimbWall()
{
	SAFE_DELETE(mpWallCol);
}

// 更新
void CClimbWall::Update()
{

}

// 描画
void CClimbWall::Render()
{
	mpWallModel->SetColor(mColor);
	mpWallModel->Render(Matrix());
}