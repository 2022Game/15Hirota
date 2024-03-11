#include "CClimbWall.h"

// コンストラクタ
CClimbWall::CClimbWall(std::string climbName, std::string topName, const CVector& moveVec)
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
{
	// 登れるモデル取得
	mpWallModel = CResourceManager::Get<CModel>(climbName);

	mpWallCol = new CColliderMesh(this, ELayer::eClimb, mpWallModel, true);
	mpWallCol->SetCollisionTags({ ETag::ePlayer });

	CModel* top = CResourceManager::Get<CModel>(topName);
	mpWallTopCol = new CColliderMesh(this, ELayer::eClimbedTop, top, true);
	mpWallTopCol->SetCollisionTags({ ETag::ePlayer });
	mpWallTopCol->SetCollisionLayers({ ELayer::ePlayer });
}

// デストラクタ
CClimbWall::~CClimbWall()
{
	SAFE_DELETE(mpWallCol);
	SAFE_DELETE(mpWallTopCol);
}

// 頂上へ上り切った時の移動量を取得
const CVector& CClimbWall::GetClimbedMoveVec() const
{
	return mClimbedMoveVec;
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