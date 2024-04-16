#include "CTreasureChest.h"
#include "CCollisionManager.h"

#define WAIT_TIME 5.0f

CTreasureChest::CTreasureChest(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: mStateStep(0)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mWaitTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
{
	// 宝箱モデル
	mpChest =  CResourceManager::Get<CModel>("TreasureChest");
	// 宝箱モデルのコライダー
	CModel* col = CResourceManager::Get<CModel>("TreasureChestWallCol");
	mpChestCol = new CColliderMesh(this, ELayer::eFieldWall, col, true);
	// 衝突定用のコライダーと衝突判定を行う
	// タグ付け
	// レイヤー付け
	// コライダーの位置を調整
	mpChestCol->SetCollisionTags({ ETag::ePlayer});
	mpChestCol->SetCollisionLayers({ ELayer::ePlayer});

	// 宝箱(蓋)モデル
	CResourceManager::Get<CModel>("TreasureChestlid");

	ChangeState(EState::Idle);

	Position(pos);
	Scale(scale);
	Rotation(rot);

	mpChestCol->SetEnable(true);

	// 初期位置を設定
	mStartPos = Position();
}

CTreasureChest::~CTreasureChest()
{
	SAFE_DELETE(mpChestCol);
}

void CTreasureChest::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}

void CTreasureChest::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	mWaitTime = WAIT_TIME;
}

// 待機状態
void CTreasureChest::UpdateIdle()
{
}

// アイテムゲット状態
void CTreasureChest::UpdateGetItem()
{
}

void CTreasureChest::Update()
{
	switch (mState)
	{
	case 
	EState::Idle:
		UpdateIdle();
		break;
	case 
	EState::GetItem:
		UpdateGetItem();
		break;
	}
}

void CTreasureChest::Render()
{
	mpChest->SetColor(mColor);
	mpChest->Render(Matrix());
}

CTreasureChestTwo::CTreasureChestTwo(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: mStateStep(0)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mWaitTime(0.0f)
	, mRotateStartAngle(0.0f)
	, mRotateEndAngle(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
{
	// 宝箱モデル
	mpChestTwo =  CResourceManager::Get<CModel>("TreasureChestTwo");
}

CTreasureChestTwo::~CTreasureChestTwo()
{
}

void CTreasureChestTwo::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}


void CTreasureChestTwo::UpdateIdle()
{
}

void CTreasureChestTwo::UpdateTwo()
{
}

void CTreasureChestTwo::Update()
{

}

void CTreasureChestTwo::Render()
{

}