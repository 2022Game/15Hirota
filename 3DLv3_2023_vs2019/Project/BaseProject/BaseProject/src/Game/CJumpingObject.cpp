#include "CJumpingObject.h"
#include "CPlayer.h"
#include "CInput.h"
#include "Maths.h"

#define DELETE 5.0f
#define WAIT 5.0f


CJumpingObject::CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CJumpingBase(ETaskPriority::eBackground)
	, mState(EState::Idle)
	, mStateStep(0)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mIsCollision(false)
{
	mpModel = CResourceManager::Get<CModel>("FieldCube");
	mpColliderMesh = new CColliderMesh(this, ELayer::eJumpingCol, mpModel, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });

	// 生成時に設定された触れた時に反応するオブジェクトタグと
	// コライダーのレイヤーを個別に設定
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	Position(pos);
	Scale(scale);
	Rotate(rot);

	SetColor(CColor(1.0f, 0.0f, 0.0f, 1.0f));
}

CJumpingObject::~CJumpingObject()
{
	SAFE_DELETE(mpColliderMesh);
}

void CJumpingObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	bool KeyPush = CInput::PushKey(VK_SPACE);

	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// 衝突しているのが、反応するオブジェクトであれば
	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		if (mState == EState::Idle && KeyPush)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(owner);
			if (player)
			{
				player->UpdateJumpingStart();
			}
			ChangeState(EState::Bounce);
		}
		else if (mState == EState::Idle)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(owner);
			if (player)
			{
				player->UpdateJumpStart();
			}
			ChangeState(EState::Bounce);
		}
		mIsCollision = true;
	}
}

// 状態を切り替える
void CJumpingObject::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// 待機状態の処理
void CJumpingObject::UpdateIdle()
{

}

// 跳ねている状態の更新処理			必要ないかも
void CJumpingObject::UpdateBounce()
{
	// 反応するオブジェクトが触れていたら
	if (mIsCollision)
	{
		// ステップ0からやり直し
		mStateStep = 0;
	}
	// ステップごとに処理を切り替え
	switch (mStateStep)
	{
		// ステップ0 フェード後の待ち時間
	case 0:
		// 待ち時間が経過していなければ、経過時間分減らす
		if (mWaitTime > 0.0f)
		{
			mWaitTime -= Time::DeltaTime();
		}
		// 待ち時間が経過したら、次のステップへ
		else
		{
			mStateStep++;
		}
		break;
		// ステップ1 消えた床をもとに戻す
	case 1:
		if (mFadeTime > 0.0f)
		{
			mFadeTime -= Time::DeltaTime();
		}
		else
		{
			// 待機状態へ戻す
			ChangeState(EState::Idle);
			mFadeTime = 0.0f;
			mWaitTime = 0.0f;

		}
		break;
	}
}

void CJumpingObject::Update()
{
	// 現在の状態に合わせて処理を切り替え
	switch (mState)
	{
		// 待機状態
	case EState::Idle:
		UpdateIdle();
		break;
		// 現れている状態
	case EState::Bounce:
		UpdateBounce();
		break;

	}
	// 衝突フラグを初期化
	mIsCollision = false;

}

void CJumpingObject::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}