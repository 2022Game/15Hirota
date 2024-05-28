#include "CJumpingObject.h"
#include "CPlayer.h"
#include "CInput.h"
#include "Maths.h"
#include "Easing.h"

// 消えた後の時間
#define DELETE 5.0f
#define WAIT 5.0f

#define SHRINK_SCALE 0.8f
#define SHRINK_TIME 0.15f
#define RETURN_TIME 0.8f

// コンストラクタ
CJumpingObject::CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eJumpingObject, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mState(EState::eIdle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mElapsedTime(0.0f)
	, mIsCollisionPlayer(false)
{
	// 跳ねさせる床のモデル取得
	mpModel = CResourceManager::Get<CModel>("FieldCube");
	// 跳ねさせる床のコライダー作成
	mpColliderMesh = new CColliderMesh(this, ELayer::eJumpingCol, mpModel, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });

	// 生成時に設定された触れた時に反応するオブジェクトタグと
	// コライダーのレイヤーを個別に設定
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	Position(pos);
	Scale(scale);
	Rotate(rot);

	SetColor(CColor(1.0f, 0.0f, 0.0f, 1.0f));
}

// デストラクタ
CJumpingObject::~CJumpingObject()
{
	SAFE_DELETE(mpColliderMesh);
}

// 衝突処理
void CJumpingObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	bool KeyPush = CInput::PushKey(VK_SPACE);

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
			if (mState == EState::eIdle && KeyPush)
			{
				CPlayer* player = dynamic_cast<CPlayer*>(owner);
				if (player)
				{
					player->UpdateHighJumpingStart();
				}
				ChangeState(EState::eBounce);
			}
			else if (mState == EState::eIdle)
			{
				CPlayer* player = dynamic_cast<CPlayer*>(owner);
				if (player)
				{
					if (player)
					{
						player->UpdateJumpingStart();
					}
				}
				ChangeState(EState::eBounce);
			}
			mIsCollisionPlayer = true;
		}
	}
}

// 状態を切り替える
void CJumpingObject::ChangeState(EState state)
{
	if (mState == state) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// 待機状態の処理
void CJumpingObject::UpdateIdle()
{
	if (mIsCollisionPlayer)
	{
		ChangeState(EState::eBounce);
	}
}

// 跳ねている状態の更新処理			必要ないかも
void CJumpingObject::UpdateBounce()
{
	switch (mStateStep)
	{
	case 0:
		mStartScale = Scale();
		mShrinkScale = mStartScale;
		mShrinkScale.X(mShrinkScale.X() * SHRINK_SCALE);
		mShrinkScale.Y(mShrinkScale.Y() * SHRINK_SCALE);
		mShrinkScale.Z(mShrinkScale.Z() * SHRINK_SCALE);
		Scale(mShrinkScale);
		mStateStep++;
		break;

	case 1:
		if (mElapsedTime < SHRINK_TIME)
		{
			mElapsedTime += Time::DeltaTime();
		}
		else
		{
			mStateStep++;
			mElapsedTime = 0.0f;
		}
		break;
	case 2:
		if (mElapsedTime < RETURN_TIME)
		{
			float percent = Easing::BounceOut
			(
				mElapsedTime,	// 現在の時間
				RETURN_TIME,	// 目的の時間
				0.0f,			// 最小値
				1.0f			// 最大値
			);
			/*float percent = Easing::BackOut
			(
				mElapsedTime,
				RETURN_TIME,
				0.3f, 1.0f, 5.0f
			);*/

			// 線形補間
			CVector scale = CVector::LerpUnclamped(
				mShrinkScale,
				mStartScale,
				percent
			);
			Scale(scale);

			mElapsedTime += Time::DeltaTime();
		}
		else
		{
			Scale(mStartScale);
			mElapsedTime = 0.0f;
			mStateStep++;
		}
		break;
	case 3:
		if (!mIsCollisionPlayer)
		{
			ChangeState(EState::eIdle);
		}
		break;
	}
}

// 更新処理
void CJumpingObject::Update()
{
	// 現在の状態に合わせて処理を切り替え
	switch (mState)
	{
		// 待機状態
	case EState::eIdle:
		UpdateIdle();
		break;
		// 現れている状態
	case EState::eBounce:
		UpdateBounce();
		break;

	}
	// 衝突フラグを初期化
	mIsCollisionPlayer = false;
}

// 描画処理
void CJumpingObject::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}