#include "CRingBeamer.h"
#include "CCharaBase.h"
#include "Maths.h"
#include "CBiribiri.h"
#include "CStageManager.h"

// 攻撃待ち時間
#define ATTACK_WAIT_TIME 0.4f
// 攻撃終了後の待ち時間
#define ATTACK_END_TIME 2.0f
// 待機状態
#define WAIT_TIME 5.0f
// 戻り状態
#define RETURN_TIME 5.0f
#define ATTACK_COUNTER 3

// コンストラクタ
CRingBeamerUpper::CRingBeamerUpper(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eRingBeam, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mState(EState::eIdle)
	, mStateStep(0)
	, mAttackCount(0)
	, mElapsedTime(0.0f)
	, mStartPosition(0.0f)
	, mEndPosition(0.0f)
	, mAttackWait(0.0f)
	, mAttackEndWait(0.0f)
	, mIsAttackWave(false)
{
	// リングビーマ(上)モデル取得
	mpRingBeamerUpper = CResourceManager::Get<CModel>("RingBeamerUP");

	Position(pos);
	Scale(scale);
	Rotation(rot);

	mStartPos = Position();
}

// デストラクタ
CRingBeamerUpper::~CRingBeamerUpper()
{

}

// 状態を切り替える
void CRingBeamerUpper::ChangeState(EState state)
{
	mState = state;
	mElapsedTime = 0.0f;
	mStateStep = 0;
}

// 待機状態の処理
void CRingBeamerUpper::UpdateIdle()
{
	if (mAttackWait >= WAIT_TIME)
	{
		mStartPosition = 0.0f;
		mElapsedTime = 0.0f;
		mAttackWait = 0.0f;
		mAttackEndWait = 0.0f;
		mEndPosition = -3.0f;
		ChangeState(EState::eAttack);
	}
	mAttackWait += Time::DeltaTime();
}

// 攻撃時の更新処理
void CRingBeamerUpper::UpdateAttack()
{
	switch (mStateStep)
	{
		// 攻撃する
	case 0:
		if (mElapsedTime < ATTACK_WAIT_TIME)
		{
			float per = mElapsedTime / ATTACK_WAIT_TIME;
			float PositionY = Math::Lerp
			(
				mStartPosition,
				mEndPosition,
				per
			);
			mElapsedTime += Time::DeltaTime();

			Position(mStartPos + CVector(0.0f, PositionY, 0.0f));
		}
		else
		{
			if (!mIsAttackWave)
			{
				mIsAttackWave = true;
				// リングビームを発射
				CBiribiri* biribiri = new CBiribiri
				(
					this,
					Position()
				);
				// リングビームエフェクトの色設定
				biribiri->SetColor(CColor(1.0f, 1.0f, 0.0f));
			}

			Position(mStartPos + CVector(0.0f, mEndPosition, 0.0f));
			mAttackEndWait += Time::DeltaTime();
			if (mAttackEndWait >= ATTACK_WAIT_TIME)
			{
				mElapsedTime = 0.0f;
				mAttackEndWait = 0.0f;
				mStateStep++;
			}
		}
		break;
		// 元に戻す
	case 1:
		if (mElapsedTime < ATTACK_WAIT_TIME)
		{
			float per = mElapsedTime / ATTACK_WAIT_TIME;
			float PositionY = Math::Lerp
			(
				mEndPosition,
				mStartPosition,
				per
			);
			mElapsedTime += Time::DeltaTime();

			Position(mStartPos + CVector(0.0f, PositionY, 0.0f));
		}
		else
		{
			// カウントが小さかったら
			if (mAttackCount < ATTACK_COUNTER)
			{
				// 繰り返す
				mAttackCount++;
				mIsAttackWave = false;
				mStateStep = 0;
				mAttackWait = 0.0f;
				mElapsedTime = 0.0f;
				Position(mStartPos + CVector(0.0f, mStartPosition, 0.0f));
			}
			else
			{
				mAttackCount = 0;
				mIsAttackWave = false;
				ChangeState(EState::eIdle);
			}
			break;
		}
		break;
	}
}

// 攻撃終了時の更新処理
void CRingBeamerUpper::UpdateAttackEnd()
{

}

 // 更新処理
void CRingBeamerUpper::Update()
{
	// 現在の状態に合わせて処理を切り替え
	switch (mState)
	{
		// 待機状態
	case EState::eIdle:
		UpdateIdle();
		break;
		// 攻撃状態
	case EState::eAttack:
		UpdateAttack();
		break;
		// 攻撃終了状態
	case EState::eAttackEnd:
		UpdateAttackEnd();
		break;
	}
	CDebugPrint::Print("mAttackWait:%f\n", mAttackWait);
}

// 描画処理
void CRingBeamerUpper::Render()
{
	mpRingBeamerUpper->SetColor(mColor);
	mpRingBeamerUpper->Render(Matrix());
}

CRingBeamerLower::CRingBeamerLower(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eRingBeam, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
{
	// リングビーマ(下)モデル取得
	mpRingBeamerLower = CResourceManager::Get<CModel>("RingBeamerLO");


	Position(pos);
	Scale(scale);
	Rotation(rot);

	mStartPos = Position();
}

CRingBeamerLower::~CRingBeamerLower()
{

}

void CRingBeamerLower::Update()
{

}

void CRingBeamerLower::Render()
{
	mpRingBeamerLower->SetColor(mColor);
	mpRingBeamerLower->Render(Matrix());
}