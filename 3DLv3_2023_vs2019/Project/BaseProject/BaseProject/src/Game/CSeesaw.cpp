#include "CSeesaw.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CModel.h"

// 回転にかかる時間
#define ROTATE_TIME 1.5f

// コンストラクタ
CSeesaw::CSeesaw(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eField, ETaskPriority::eSeesaw, 0, ETaskPauseType::eGame)
	, mState(EState::eIdle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mDeafaultRot(rot)
	, mStateStep(0)
	, mRotationAngle(0.0f)
	, mRotateStartAngle(0.0f)
	, mRotateEndAngle(0.0f)
	, mElpasedTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCenterCol(false)
	, mIsRightCol(false)
	, mIsLeftCol(false)
{
	// シーソーモデルを取得
	mpSeesawModel = CResourceManager::Get<CModel>("SeesawModel");

	// シーソーセンターコライダーを作成
	CModel* center = CResourceManager::Get<CModel>("centerCol");
	mpCenterCol = new CColliderMesh(this, ELayer::eField, center, true);
	mpCenterCol->SetCollisionLayers({ ELayer::ePlayer });
	mpCenterCol->SetCollisionTags({ ETag::ePlayer });

	// シーソーライトコライダーを作成
	CModel* right = CResourceManager::Get<CModel>("rightCol");
	mpRightCol = new CColliderMesh(this, ELayer::eField, right, true);
	mpRightCol->SetCollisionLayers({ ELayer::ePlayer });
	mpRightCol->SetCollisionTags({ ETag::ePlayer });

	// シーソーレフトコライダーを作成
	CModel* left = CResourceManager::Get<CModel>("leftCol");
	mpLeftCol = new CColliderMesh(this, ELayer::eField, left, true);
	mpLeftCol->SetCollisionLayers({ ELayer::ePlayer });
	mpLeftCol->SetCollisionTags({ ETag::ePlayer });

	Position(pos);
	Scale(scale);
	Rotation(mDeafaultRot);

	// 初期位置
	mStartPos = Position();

	SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
}

// デストラクタ
CSeesaw::~CSeesaw()
{
	SAFE_DELETE(mpCenterCol);
	SAFE_DELETE(mpRightCol);
	SAFE_DELETE(mpLeftCol);
}

// 衝突処理
void CSeesaw::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// センターコライダーに当たったら
	if (self == mpCenterCol)
	{
		mIsCenterCol = true;
	}
	// ライトコライダーに当たったら
	else if (self == mpRightCol)
	{
		mIsRightCol = true;
	}
	// レフトコライダーに当たったら
	else if (self == mpLeftCol)
	{
		mIsLeftCol = true;
	}
}

// 状態を切り替える
void CSeesaw::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	mElpasedTime = 0.0f;
}

// 待機状態の更新処理
void CSeesaw::UpdateIdle()
{
	// センターコライダーがtrueだったらそのまま
	if (mIsCenterCol)
	{
		// 何もしない
		// いらないかも
	}
	// ライトコライダーに当たったら右に傾ける
	else if (mIsRightCol)
	{
		mRotateStartAngle = mRotationAngle; // 現在の角度を開始角度に設定
		mRotateEndAngle = 45.0f;
		mElpasedTime = 0.0f;
		ChangeState(EState::eRight);
	}
	// レフトコライダーに当たったら左に傾ける
	else if (mIsLeftCol)
	{
		mRotateStartAngle = mRotationAngle; // 現在の角度を開始角度に設定
		mRotateEndAngle = -45.0f;
		mElpasedTime = 0.0f;
		ChangeState(EState::eLeft);
	}
	// シーソーに触れていなかったら元の角度に戻す
	else
	{
		mRotateStartAngle = mRotationAngle; // 現在の角度を開始角度に設定
		mRotateEndAngle = 0.0f;
		mElpasedTime = 0.0f;
		ChangeState(EState::eReturn);
	}
}

// 右に傾く更新処理
void CSeesaw::UpdateRight()
{
	if (mIsLeftCol)
	{
		mRotateStartAngle = mRotationAngle; // 現在の角度を開始角度に設定
		mRotateEndAngle = -45.0f;
		//mElpasedTime = 0.0f;
		ChangeState(EState::eLeft);
	}
	
	// 回転にかかる時間を経過していない
	if (mElpasedTime < ROTATE_TIME)
	{
		// 回転開始時の角度から徐々に回転終了時の角度へ回転させる
		float per = mElpasedTime / ROTATE_TIME;
		float angleZ = Math::Lerp
		(
			mRotateStartAngle,
			mRotateEndAngle,
			per
		);
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, angleZ)));
		mElpasedTime += Time::DeltaTime();
	}
	// 回転にかかる時間を経過した
	else
	{
		mRotationAngle = mRotateEndAngle;
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, mRotateEndAngle)));
		if (!mIsRightCol)
		{
			ChangeState(EState::eIdle);
		}
	}
}

// 左に傾く更新処理
void CSeesaw::UpdateLeft()
{
	if (mIsRightCol)
	{
		mRotateStartAngle = mRotationAngle; // 現在の角度を開始角度に設定
		mRotateEndAngle = 45.0f;
		//mElpasedTime = 0.0f;
		ChangeState(EState::eRight);
		return;
	}

	// 回転にかかる時間を経過していない
	if (mElpasedTime < ROTATE_TIME)
	{
		// 回転開始時の角度から徐々に回転終了時の角度へ回転させる
		float per = mElpasedTime / ROTATE_TIME;
		float angleZ = Math::Lerp
		(
			mRotateStartAngle,
			mRotateEndAngle,
			per
		);
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, angleZ)));
		mElpasedTime += Time::DeltaTime();
	}
	// 回転にかかる時間を経過した
	else
	{
		mRotationAngle = mRotateEndAngle;
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, mRotateEndAngle)));
		if (!mIsLeftCol)
		{
			ChangeState(EState::eIdle);
		}
	}
}

// 元に戻す更新処理
void CSeesaw::UpdateReturn()
{
	if (mIsRightCol)
	{
		mRotateStartAngle = mRotationAngle; // 現在の角度を開始角度に設定
		mRotateEndAngle = 45.0f;
		mElpasedTime = 0.0f;
		ChangeState(EState::eRight);
		return;
	}
	else if (mIsLeftCol)
	{
		mRotateStartAngle = mRotationAngle; // 現在の角度を開始角度に設定
		mRotateEndAngle = -45.0f;
		mElpasedTime = 0.0f;
		ChangeState(EState::eLeft);
		return;
	}

	// 回転にかかる時間を経過していない
	if (mElpasedTime < ROTATE_TIME)
	{
		// 回転開始時の角度から徐々に元の角度へ回転させる
		float per = mElpasedTime / ROTATE_TIME;
		float angleZ = Math::Lerp
		(
			mRotateStartAngle,
			mIsRightCol ? 45.0f : (mIsLeftCol ? -45.0f : 0.0f), // 傾いている方向の角度に戻す
			per
		);
		mRotationAngle = angleZ; // 現在の角度を更新
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, angleZ)));
		mElpasedTime += Time::DeltaTime();
	}
	// 回転にかかる時間を経過した
	else
	{
		mElpasedTime = 0.0f;
		mRotationAngle = mIsRightCol ? 45.0f : (mIsLeftCol ? -45.0f : 0.0f); // 傾いている方向の角度に設定
		Rotation(mDeafaultRot * CQuaternion(CVector(0.0f, 0.0f, 0.0f)));
		ChangeState(EState::eIdle); // 待機状態に戻す
	}
}

// 更新処理
void CSeesaw::Update()
{
	/*CDebugPrint::Print("mIsCenterCol:%s\n", mIsCenterCol ? "true" : "false");
	CDebugPrint::Print("mIsRightCol:%s\n", mIsRightCol ? "true" : "false");
	CDebugPrint::Print("mIsLeftCol:%s\n", mIsLeftCol ? "true" : "false");*/

	CDebugPrint::Print("mRotationAngle:%f\n", mRotationAngle);
	CDebugPrint::Print("mRotateStartAngle:%f\n", mRotateStartAngle);
	CDebugPrint::Print("mRotateEndAngle:%f\n", mRotateEndAngle);

	// 現在の状態に合わせて処理を切り替え
	switch (mState)
	{
	case EState::eIdle:		// 待機状態
		UpdateIdle();
		break;
	case EState::eRight:	// 右に傾く状態
		UpdateRight();
		break;
	case EState::eLeft:		// 左に傾く状態
		UpdateLeft();
		break;
	case EState::eReturn:	// 元に戻る状態
		UpdateReturn();
		break;
	}

	mIsCenterCol = false;
	mIsRightCol = false;
	mIsLeftCol = false;
}

// 描画処理
void CSeesaw::Render()
{
	mpSeesawModel->SetColor(mColor);
	mpSeesawModel->Render(Matrix());
}