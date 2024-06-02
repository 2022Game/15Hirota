#include "CBiribiri.h"

// コンストラクタ
CBiribiri::CBiribiri(CObjectBase* owner, const CVector& pos, const CVector& dir,
	float speed, float dist)
	: CObjectBase(ETag::eSlash, ETaskPriority::eEffect, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mKillMoveDist(dist)
	, mMovedDist(0.0f)
	, mInitialRingSize(1.0f) // 初期サイズ
	, mCurrentRingSize(1.0f) // 現在のサイズ
	, mMaxRingSize(20.0f)    // 最大サイズを設定
{
	Position(pos);
	mMoveSpeed = dir.Normalized() * speed;
	Rotation(CQuaternion::LookRotation(mMoveSpeed, CVector::up));

	mpModel = CResourceManager::Get<CModel>("Biribiri");
	mpModel->SetupEffectSettings();
}

// デストラクタ
CBiribiri::~CBiribiri()
{
}

// 更新
void CBiribiri::Update()
{
	// リングのサイズを速く増加させるための係数
	const float growthFactor = 8.0f;

	// 現在のリングサイズを更新
    mCurrentRingSize += Time::DeltaTime() * growthFactor;

    // リングのサイズが最大サイズを超えた場合は消滅させる
    if (mCurrentRingSize >= mMaxRingSize)
    {
        Kill();
        return;
    }

    // 移動処理はここで行います

	// リングのスケールを適用する
	CVector scaleVector(mCurrentRingSize, 5.0f, mCurrentRingSize);
	Scale(scaleVector);
}

// 描画
void CBiribiri::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}