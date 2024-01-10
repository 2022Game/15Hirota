#include "CFallingObjects.h"
#include "Maths.h"
#include "CPlayer.h"


// 消えるのにかかる時間
#define FADE_TIME 3.0f
// 消えた後の待ち時間
#define WAIT_TIME 3.0f

// コンストラクタ
CFallingObjects::CFallingObjects(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eFallingOBJ)
	, mState(EState::Idle)
	, mStateStep(0)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mIsCollision(false)
	, mMoveSpeed(0.0f,0.0f,0.0f)
	, mPosition(0.0f,0.0f,0.0f)
{

	//Position(0.0f, 6.0f, -430.0f);
	mStartPos = Position();

	// 床のモデルを取得
	mpModel = CResourceManager::Get<CModel>("FieldCube");

	// 消える床のコライダー作成
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer, ELayer::eEnemy });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer, ETag::eEnemy });

	// 生成時に設定された触れた時に反応するオブジェクトタグと
	// コライダーのレイヤーを個別に設定
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	Position(pos);
	Scale(scale);

	SetColor(CColor(0.0f, 1.0f, 1.0f, 1.0f));

}

// デストラクタ
CFallingObjects::~CFallingObjects()
{
	SAFE_DELETE(mpColliderMesh);
}

// ステージ開始時の位置を設定
void CFallingObjects::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// 衝突処理
void CFallingObjects::Collision(CCollider* slef, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// 衝突しているのが、反応するオブジェクトであれば
	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		// 現在が待機状態であれば、フェード状態へ切り替える
		if (mState == EState::Idle)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(owner);
			if (player)
			{
				ChangeState(EState::Falling);
				mFadeTime = FADE_TIME;
				mWaitTime = WAIT_TIME;
			}
		}

		// 反応するオブジェクトが触れているので
		// 衝突フラグをオン
		mIsCollision = true;
	}
}

// 状態を切り替える
void CFallingObjects::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// 待機状態の処理
void CFallingObjects::UpdateIdle()
{

}

// 現れている状態の更新処理
void CFallingObjects::UpdateFalling()
{
	// 反応するオブジェクトが触れていたら
	if (mIsCollision)
	{
		float fallSpeed = 5.0f;
		mMoveSpeed = CVector(0.0f, -fallSpeed * Time::DeltaTime(), 0.0f);
		Position(Position() + mMoveSpeed);
		// ステップ0からやり直し
		mStateStep = 0;
		mWaitTime = WAIT_TIME;
		mFadeTime = FADE_TIME;
	}
	else
	{
		// プレイヤーが離れたら上昇
		float ascendSpeed = 5.0f; // 適切な速度を設定
		mMoveSpeed = CVector(0.0f, +ascendSpeed * Time::DeltaTime(), 0.0f);
		Position(Position() + mMoveSpeed);

		// 離れた位置に達したら初期位置に戻す
		if (CVector::Distance(Position(), mStartPos) < 0.1f)
		{
			Position(mStartPos);
			// 待機状態へ戻す
			ChangeState(EState::Idle);
			mFadeTime = 0.0f;
			mWaitTime = 0.0f;
		}
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

			// プレイヤーが触れていた場合、元の位置に戻す
			if (mIsCollision)
			{
				Position(mStartPos);
			}
		}
		break;
	}
}

// 更新
void CFallingObjects::Update()
{
	// 現在の状態に合わせて処理を切り替え
	switch (mState)
	{
		// 待機状態
	case EState::Idle:
		UpdateIdle();
		break;
		// 落下状態
	case EState::Falling:
		UpdateFalling();
		break;

	}

	//// フェード時間に合わせて床のα値を求める
	//// α値を設定
	//float alpha = Math::Clamp01(mFadeTime / FADE_TIME);
	//SetAlpha(alpha);

	// 衝突フラグを初期化
	mIsCollision = false;
}

// 描画
void CFallingObjects::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}