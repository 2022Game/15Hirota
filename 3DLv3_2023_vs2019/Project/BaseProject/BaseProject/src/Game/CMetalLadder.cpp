#include "CMetalLadder.h"

// コンストラクタ
CMetalLadder::CMetalLadder(std::string wireName, std::string topName,
	const CVector& moveUp, const CVector& moveForward)
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
	, mClimbedMoveUp(moveUp)
	, mClimbMoveForward(moveForward)
{
	// 登れる金網モデル取得
	mpMetalLadderModel = CResourceManager::Get<CModel>(wireName);

	// 登れる金網のコライダー取得
	CModel* wireCol = CResourceManager::Get<CModel>("MetalladderCol");
	mpWallCol = new CColliderMesh(this, ELayer::eMetalLadder, wireCol, true);
	mpWallCol->SetCollisionTags({ ETag::ePlayer });

	// 登れる金網の頂上コライダー取得
	CModel* top = CResourceManager::Get<CModel>(topName);
	mpWallTopCol = new CColliderMesh(this, ELayer::eMetalLadderTop, top, true);
	mpWallTopCol->SetCollisionTags({ ETag::ePlayer });
	mpWallTopCol->SetCollisionLayers({ ELayer::ePlayer });

}

// デストラクタ
CMetalLadder::~CMetalLadder()
{
	SAFE_DELETE(mpWallCol);
	SAFE_DELETE(mpWallTopCol);
}

// 頂上へ上り切った時の移動量を取得
void CMetalLadder::GetClimbedMoveVec(CVector* outUp, CVector* outForward) const
{
	*outUp = mClimbedMoveUp;
	*outForward = mClimbMoveForward;
}

// 更新
void CMetalLadder::Update()
{

}

// 描画
void CMetalLadder::Render()
{
	mpMetalLadderModel->SetColor(mColor);
	mpMetalLadderModel->Render(Matrix());
}