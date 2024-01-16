#include "CRengaBlock.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CSound.h"

// 消えるのにかかる時間
#define FADE_TIME 3.0f
// 消えた後の待ち時間
#define WAIT_TIME 3.0f

#define MAXHEIGHT 15.0f

// コンストラクタ
CRengaBlock::CRengaBlock(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eHatenaOBJ)
	, mState(EState::Idle)
	, mStateStep(0)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mIsCollision(false)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
{
	// レンガブロックモデルを取得
	mpModel = CResourceManager::Get<CModel>("RengaBlock");


	mStartPos = Position();

	// レンガロックのコライダーを作成
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eBlockCol,
		1.0f, true
	);
	mpColliderSphere->SetCollisionTags({ ETag::ePlayer,ETag::eItem });
	mpColliderSphere->SetCollisionLayers({ ELayer::ePlayer,ELayer::eRecoverCol });
	mpColliderSphere->Position(0.0f, 5.0f, 0.0f);

	// 生成時に設定された触れた時に反応するオブジェクトタグと
	// コライダーのレイヤーを個別に設定
	mpColliderSphere->SetCollisionTag(mReactionTag, true);
	mpColliderSphere->SetCollisionLayer(mReactionLayer, true);

	Position(pos);
	Scale(scale);

}

// デストラクタ
CRengaBlock::~CRengaBlock()
{
	SAFE_DELETE(mpColliderSphere);
}

// 衝突処理
void CRengaBlock::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// 衝突しているのが反応するオブジェクトであれば
	if (owner->Tag() == mReactionTag && other->Layer() == mReactionLayer)
	{
		CPlayer* player = dynamic_cast<CPlayer*>(owner);
		//// 反転した押し戻しベクトルと上方向のベクトルの内積(角度)を求める
		//float dot = CVector::Dot(-hit.adjust.Normalized(), CVector::down);
		//// 下側に当たったと判断するためのcos関数に渡した角度を求める
		//float cosAngle = cosf(Math::DegreeToRadian(10.0f)); && dot >= cosAngle
		if (player)
		{
			// 現在が待機状態であれば、当たった時の処理にする
			if (mState == EState::Idle)
			{
				ChangeState(EState::Hit);
			}
		}
	}
}

// 状態を切り替える
void CRengaBlock::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}


// ステージ開始時の位置を設定
void CRengaBlock::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// 待機状態の処理
void CRengaBlock::UpdateIdle()
{

}

// 当たった時の更新処理
void CRengaBlock::UpdateHit()
{
	// ステップごとに処理を切り替え
	switch (mStateStep)
	{
		// ステップ0 オブジェクトを上に揺らす
	case 0:
		// 揺らす
		// 最大値まで
		if (Position().Y() < mStartPos.Y() + MAXHEIGHT)
		{
			mMoveSpeed = CVector(0.0f, 100.0f * Time::DeltaTime(), 0.0f);
			Position(Position() + mMoveSpeed);
		}
		else
		{
			mStateStep++;
		}
		break;
		// ステップ1 元に戻す
	case 1:
		mMoveSpeed = CVector(0.0f, -50.0f * Time::DeltaTime(), 0.0f);
		Position(Position() + mMoveSpeed);
		if (CVector::Distance(Position(), mStartPos) < 0.5f)
		{
			Position(mStartPos);
			// 当たった後の状態に遷移
			ChangeState(EState::After);
			mStateStep = 0;
		}
		break;
	}
}

// 当たった後の更新処理
void CRengaBlock::UpdateAfter()
{
	SetAlpha(0.0f);
	mpColliderSphere->SetEnable(false);
}

// 更新処理
void CRengaBlock::Update()
{
	// 現在の状態に合わせて処理を切り替え
	switch (mState)
	{
		// 待機状態
	case EState::Idle:
		UpdateIdle();
		break;
		// 当たった状態
	case EState::Hit:
		UpdateHit();
		break;
		// 当たった後の状態
	case EState::After:
		UpdateAfter();
		break;
	}

}

// 描画
void CRengaBlock::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}