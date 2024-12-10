#include "CShockWave_1.h"
#include "Easing.h"
#include "CStageManager.h"

// コンストラクタ
CShockWave_1::CShockWave_1(CObjectBase* owner, const CVector& pos, const CVector& startscale, const CVector& endscale,
	const CVector& dir, float speed, float dist)
	: CObjectBase(ETag::eShockWave, ETaskPriority::eEffect, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mKillMoveDist(dist)
	, mStartScale(startscale)
	, mEndScale(endscale)
	, mElapsedTime(0.0f)
	, mScaleTime(0.0f)
	, mMovedDist(0.0f)
{
	Position(pos);
	Scale(mStartScale);
	mMoveSpeed = dir.Normalized() * speed;
	Rotation(CQuaternion::LookRotation(mMoveSpeed, CVector::up));

	mpModel = CResourceManager::Get<CModel>("ShockWave");
	mpModel->SetupEffectSettings();

	mpCapsule1 = new CColliderCapsule
	(
		this, ELayer::eShockWave,
		CVector(35.0f, 0.0f, 0.0f),
		CVector(-35.0f, 0.0f, 0.0f),
		2.0f,
		true,
		1.0f
	);
	mpCapsule1->SetCollisionLayers({ ELayer::eDamageCol });
	mpCapsule1->SetCollisionTags({ ETag::eEnemy });
	mpCapsule2 = new CColliderCapsule
	(
		this, ELayer::eShockWave,
		CVector(35.0f, 20.0f, 0.0f),
		CVector(-35.0f, 20.0f, 0.0f),
		2.0f,
		true,
		1.0f
	);
	mpCapsule2->SetCollisionLayers({ ELayer::eDamageCol });
	mpCapsule2->SetCollisionTags({ ETag::eEnemy });
}

// デストラクタ
CShockWave_1::~CShockWave_1()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpCapsule1);
	SAFE_DELETE(mpCapsule2);
}

#define STARTSCALETIME 0.0f
#define ENDSCALETIME 1.0f
// 更新処理
void CShockWave_1::Update()
{
	if (mScaleTime < ENDSCALETIME)
	{
		float percent = Easing::QuadIn
		(
			mScaleTime,		// 現在の時間
			ENDSCALETIME,	// 目的の時間
			STARTSCALETIME,	// 最小値
			ENDSCALETIME	// 最大値
		);

		// 線形補間
		CVector scale = CVector::LerpUnclamped(
			mStartScale,
			mEndScale,
			percent
		);
		Scale(scale);

		mScaleTime += Time::DeltaTime();
	}
	else
	{
		Scale(mEndScale);		
	}

	CVector move = mMoveSpeed * Time::DeltaTime();
	float dist = move.Length();
	if (mMovedDist + dist >= mKillMoveDist)
	{
		dist = mKillMoveDist - mMovedDist;
		move = move.Normalized() * dist;
	}
	Position(Position() + move);

	mMovedDist += dist;
	if (mMovedDist >= mKillMoveDist)
	{
		Kill();
	}
}

// 描画処理
void CShockWave_1::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}