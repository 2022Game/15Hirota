#include "CNumberFloor1.h"
#include "Maths.h"
#include "CPlayer.h"

// 消えるのにかかる時間
#define FADE_TIME 3.0f
// 消えた後の待ち時間
#define WAIT_TIME 3.0f

// コンストラクタ
CNumberFloor1::CNumberFloor1(const CVector& pos, const CVector& scale, const CVector& rot,
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
	, mCase0End(false)
	, mCase1End(false)
	, mIsCollision(false)
{
	// 回数で落ちる床(3回)のモデル取得
	mpModel = CResourceManager::Get<CModel>("Number3");

	// 回数で落ちる床(3回)のコライダー作成
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
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
CNumberFloor1::~CNumberFloor1()
{
	SAFE_DELETE(mpColliderMesh);
}

// 衝突処理
void CNumberFloor1::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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

// ステージ開始時の位置を設定
void CNumberFloor1::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// 状態を切り替える
void CNumberFloor1::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	mFallingSwitch = 0;
}

// 待機状態の処理
void CNumberFloor1::UpdateIdle()
{

}

// 待ち状態の処理
void CNumberFloor1::UpdateWaiting()
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
		if (!mCase0End)
		{
			// プレイヤーが離れたらIdleに遷移
			if (!mIsCollision)
			{
				mpModel = CResourceManager::Get<CModel>("Number2");

				mCase0End = true;
				mStateStep++;
				ChangeState(EState::Idle);
			}
			break;
		}
		else
		{
			mStateStep++;
		}
		break;
	}
	// ステップ1 オブジェクト表示の変更
	case 1:
	{
		if (!mCase1End && mCase0End)
		{
			// プレイヤーが離れたらIdleに遷移
			if (!mIsCollision)
			{
				mpModel = CResourceManager::Get<CModel>("Number1");

				ChangeState(EState::Idle);
				mStateStep++;
				mCase1End = true;
			}
			break;
		}
		if (!mIsCollision && mCase0End && mCase1End)
		{
			SetColor(CColor(0.5f, 0.0f, 0.0f, 1.0f));
			mStateStep++;
		}
		break;
	}
	// ステップ2 状態遷移
	case 2:
	{
		mpModel = CResourceManager::Get<CModel>("Number0");
		ChangeState(EState::Falling);
	}
	break;
	}
}

// 落下状態の更新処理
void CNumberFloor1::UpdateFalling()
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
		mpModel = CResourceManager::Get<CModel>("Number3");
		SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
		mCase0End = false;
		mCase1End = false;
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
void CNumberFloor1::Update()
{
	// 減殺の状態に合わせて処理を切り替え
	switch (mState)
	{
		// 待機状態
	case EState::Idle:
		UpdateIdle();
		break;
		// 待機状態
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

	/*CDebugPrint::Print("mCase0: %s\n", mCase0End ? "true" : "false");
	CDebugPrint::Print("mCase1: %s\n", mCase1End ? "true" : "false");
	CDebugPrint::Print("mIsCollsion:%s\n", mIsCollision ? "true" : "false");*/
}

// 描画処理
void CNumberFloor1::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}