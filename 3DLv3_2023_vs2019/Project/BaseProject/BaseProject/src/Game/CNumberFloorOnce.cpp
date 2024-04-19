#include "CNumberFloorOnce.h"
#include "Maths.h"
#include "CPlayer.h"

// 消えるのにかかる時間
#define FADE_TIME 4.0f
// 消えた後の待ち時間
#define WAIT_TIME 4.0f

// コンストラクタ
CNumberFloorOnce::CNumberFloorOnce(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eNumberFalling)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mSwitchCount(0)
	, mFallingSwitch(0)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mElapsedTime(0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
{
	// 1回で消滅する床のモデル取得
	mpNumberOnce = CResourceManager::Get<CModel>("Number1");

	// 1回で消滅する床のコライダー作成
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpNumberOnce, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });

	// 生成時に設定された触れた時に反応するオブジェクトタグと
	// コライダーのレイヤーを個別に設定
	mpColliderMesh->SetCollisionTag(mReactionTag, true);
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);


	Position(pos);
	Scale(scale);
	Rotate(rot);

	// 初期位置を設定
	mStartPos = Position();

	mStateStep = 0;
}

// デストラクタ
CNumberFloorOnce::~CNumberFloorOnce()
{
	SAFE_DELETE(mpColliderMesh);
}

// 衝突処理
void CNumberFloorOnce::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// 衝突しているのが、反応するオブジェクトであれば
	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		// 反転した押し戻しベクトルと上方向のベクトルの内積(角度)を求める
		float dot = CVector::Dot(-hit.adjust.Normalized(), CVector::up);
		// 上に乗ったと判断するためのcos関数に渡した角度を求める
		float cosAngle = cosf(Math::DegreeToRadian(10.0f));
		// 求めた角度が指定した角度の範囲内であれば、
		if (dot >= cosAngle)
		{
			// 現在が待機状態であれば、フェード状態へ切り替える
			if (mState == EState::Idle)
			{
				ChangeState(EState::Waiting);
			}
		}
		mIsCollision = true;
	}
}

// 状態を切り替える
void CNumberFloorOnce::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	mFallingSwitch = 0;
}

// 待機状態の処理
void CNumberFloorOnce::UpdateIdle()
{

}

// 待ち状態の処理
void CNumberFloorOnce::UpdateWaiting()
{
	if (mIsCollision)
	{
		SetColor(CColor(0.5f, 0.1f, 0.1f, 1.0f));
	}
	else
	{
		SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
	}

	switch (mStateStep)
	{
		// ステップ0 オブジェクト表示の変更
	case 0:
	{
		if (!mIsCollision)
		{
			mStateStep++;
		}
		break;
	}
	case 1:
	{
		mpModel = CResourceManager::Get<CModel>("Number0");
		ChangeState(EState::Falling);
	}
	break;
	}
}

// 落下状態の処理
void CNumberFloorOnce::UpdateFalling()
{
	switch (mFallingSwitch)
	{
		// 赤色で点滅させる
	case 0:
	{
		static const float time = 2.0f;
		if (mElapsedTime < time)
		{
			mElapsedTime += Time::DeltaTime();
			float red = 0.5f + 0.5f * sin(2.0f * M_PI * mElapsedTime);
			CColor color = CColor(red, 0.0f, 0.0f, 1.0f);
			SetColor(color);
		}
		else
		{
			mSwitchCount++;
			mElapsedTime = 0.0f;
			if (mSwitchCount == 2)
			{
				mFallingSwitch++;
			}
		}
	}
	break;
	// 落下させる
	case 1:
	{
		static const float fall = 10.0f;
		mMoveSpeed = CVector(0.0f, -fall * Time::DeltaTime(), 0.0f);
		Position(Position() + mMoveSpeed);
		if (Position().Y() <= mStartPos.Y() - 30.0f)
		{
			mFallingSwitch++;
			Position(mStartPos);
		}
	}
	break;
	// 元の状態に戻す
	case 2:
	{
		mpModel = CResourceManager::Get<CModel>("Number1");
		SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
		mStateStep = 0;
		mSwitchCount = 0;
		mElapsedTime = 0;
		mFallingSwitch = 0;
		ChangeState(EState::Idle);
	}
	break;
	}
}

// 更新処理
void CNumberFloorOnce::Update()
{
	// 床の状態に合わせて処理を切り替え
	switch (mState)
	{
		// 待機状態
	case EState::Idle:
		UpdateIdle();
		break;
		// 待ち状態
	case EState::Waiting:
		UpdateWaiting();
		break;
		// 落下状態
	case EState::Falling:
		UpdateFalling();
		break;
	}

	// 衝突フラグを初期化
	mIsCollision = false;

}

// 描画処理
void CNumberFloorOnce::Render()
{
	mpNumberOnce->SetColor(mColor);
	mpNumberOnce->Render(Matrix());
}