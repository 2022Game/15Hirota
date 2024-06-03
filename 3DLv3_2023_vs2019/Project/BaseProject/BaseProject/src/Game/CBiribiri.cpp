#include "CBiribiri.h"
#include "Maths.h"

#define SCALE_Y 3.0f

// コンストラクタ
CBiribiri::CBiribiri(CObjectBase* owner, const CVector& pos)
	: CObjectBase(ETag::eBiribiri, ETaskPriority::eEffect, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mMovedDist(0.0f)
	, mInitialRingSize(1.0f) // 初期サイズ
	, mCurrentRingSize(1.0f) // 現在のサイズ
	, mMaxRingSize(100.0f)    // 最大サイズを設定
{
	Position(pos);

	mpModel = CResourceManager::Get<CModel>("Biribiri");
	mpModel->SetupEffectSettings();

	CModel* col = CResourceManager::Get<CModel>("BiribiriCol");
	mpMesh = new CColliderMesh(this, ELayer::eBiribiri, col, true);
	mpMesh->SetCollisionLayers({ ELayer::eDamageCol });
	mpMesh->SetCollisionTags({ ETag::ePlayer });
}

// デストラクタ
CBiribiri::~CBiribiri()
{
	SAFE_DELETE(mpMesh);
}

// 更新
void CBiribiri::Update()
{
	// リングのサイズを速く増加させるための係数
	const float growthFactor = 50.0f;

	// 現在のリングサイズを更新
    mCurrentRingSize += Time::DeltaTime() * growthFactor;

    // リングのサイズが最大サイズを超えた場合は消滅させる
    if (mCurrentRingSize >= mMaxRingSize)
    {
        Kill();
        return;
    }

	// リングのスケールを適用する
	CVector scaleVector(mCurrentRingSize, mCurrentRingSize, mCurrentRingSize);
	Scale(scaleVector);
}

// 描画
void CBiribiri::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}