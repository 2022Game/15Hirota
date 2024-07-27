#include "CSeesaw.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CModel.h"

// 回転にかかる時間
#define ROTATE_TIME 2.5f
// １秒間に回転する角度
#define ROTATE_SPEED 50.0f

// コンストラクタ
CSeesaw::CSeesaw(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eSeesaw, ETaskPriority::eSeesaw, 0, ETaskPauseType::eGame)
	, mState(EState::eIdle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mDeafaultRot(rot)
	, mStateStep(0)
	, mRotationAngle(0.0f)
	, mRotateStartAngle(0.0f)
	, mRotateEndAngle(0.0f)
	, mElapsedTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
{
	// シーソーモデルを取得
	mpSeesawModel = CResourceManager::Get<CModel>("SeesawModel");

	// シーソー全体コライダーを作成
	CModel* ceesaw = CResourceManager::Get<CModel>("SeesawModelCol");
	mpSeesawCol = new CColliderMesh(this, ELayer::eField, ceesaw, true);
	mpSeesawCol->SetCollisionLayers({ ELayer::ePlayer });
	mpSeesawCol->SetCollisionTags({ ETag::ePlayer });


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
	SAFE_DELETE(mpSeesawCol);
}

// 衝突処理
void CSeesaw::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// プレイヤーが触れた
	mIsHitCol = true;

	// プレイヤーの座標からシーソーの左右どちらに位置するか計算
	CVector playerPos = owner->Position();
	// シーソーの座標
	CVector seesawPos = Position();
	// シーソーからプレイヤーまでのベクトルを求める
	CVector vec = playerPos - seesawPos;
	// シーソーの横方向のベクトルを求める
	CVector side = VectorX();
	side.Y(0.0f);
	side.Normalize();
	// 2つのベクトルの内積から、
	// プレイヤーがシーソー上のどこに位置するか求める
	mHitDir = CVector::Dot(vec, side);
}

bool CSeesaw::CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit)
{
	bool isHit = CCollider::CollisionRay(mpSeesawCol, start, end, hit);
	// シーソーのコライダーに当たったら
	if (isHit)
	{
		return true;
	}

	return false;
}

// 状態を切り替える
void CSeesaw::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// 待機状態の更新処理
void CSeesaw::UpdateIdle()
{
	// プレイヤーがシーソーに触れている
	if (mIsHitCol)
	{
		// センターコライダーがtrueだったらそのまま
		if (abs(mHitDir) <= 10.0f)
		{
			// 元の角度を目的の角度(0度に)設定
			mRotateEndAngle = 0.0f;
			mElapsedTime = 0.0f;
		}
		// ライトコライダーに当たったら右に傾ける
		else if (mHitDir < 0.0f)
		{
			// 右に傾ける(目的の角度を45度に設定)
			mRotateEndAngle = 50.0f;
			mElapsedTime = 0.0f;
		}
		// レフトコライダーに当たったら左に傾ける
		else if (mHitDir > 0.0f)
		{
			// 左に傾ける(目的の角度を-45度に設定)
			mRotateEndAngle = -50.0f;
			mElapsedTime = 0.0f;
		}
	}
	// シーソーに一定時間触れていなかったら、
	// 元の角度(0度に戻す)
	else
	{
		if (mElapsedTime < 0.1f)
		{
			mElapsedTime += Time::DeltaTime();
		}
		else
		{
			mRotateEndAngle = 0.0f;
		}
	}

	// 現在の角度が目的の角度より小さいのであれば、
	if (mRotationAngle < mRotateEndAngle)
	{
		// 角度を加算(右に傾ける)
		mRotationAngle += ROTATE_SPEED * Time::DeltaTime();
		if (mRotationAngle > mRotateEndAngle)
		{
			mRotationAngle = mRotateEndAngle;
		}
	}
	// 現在の角度が目的の角度より小さいのであれば、
	else if (mRotationAngle > mRotateEndAngle)
	{
		// 角度を減算(左に傾ける)
		mRotationAngle -= ROTATE_SPEED * Time::DeltaTime();
		if (mRotationAngle < mRotateEndAngle)
		{
			mRotationAngle = mRotateEndAngle;
		}
	}

	// 現在の角度を反映
	Rotation(mDeafaultRot * CQuaternion(0.0f, 0.0f, mRotationAngle));
}

// 更新処理
void CSeesaw::Update()
{
	/*CDebugPrint::Print("mIsCenterCol:%s\n", mIsCenterCol ? "true" : "false");
	CDebugPrint::Print("mIsRightCol:%s\n", mIsRightCol ? "true" : "false");
	CDebugPrint::Print("mIsLeftCol:%s\n", mIsLeftCol ? "true" : "false");*/

	/*CDebugPrint::Print("mRotationAngle:%f\n", mRotationAngle);
	CDebugPrint::Print("mRotateStartAngle:%f\n", mRotateStartAngle);
	CDebugPrint::Print("mRotateEndAngle:%f\n", mRotateEndAngle);*/

	// 現在の状態に合わせて処理を切り替え
	switch (mState)
	{
	case EState::eIdle:		// 待機状態
		UpdateIdle();
		break;
	}

	mIsHitCol = false;
}

// 描画処理
void CSeesaw::Render()
{
	mpSeesawModel->SetColor(mColor);
	mpSeesawModel->Render(Matrix());
}