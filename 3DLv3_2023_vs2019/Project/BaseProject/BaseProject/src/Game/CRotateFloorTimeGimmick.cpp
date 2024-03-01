#include "CRotateFloorTimeGimmick.h"
#include "Maths.h"
#include "CPlayer.h"

// 待ち時間
#define WAIT_TIME 5.0f

// コンストラクタ
CRotateFloorTimeGimmick::CRotateFloorTimeGimmick(const CVector& pos, const CVector& scale,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eRotate)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mWaitTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
	, mNextRotateIsRotate2(false)
{
	// 初期位置を設定
	mStartPos = Position();

	// 落下する床枠モデルを取得
	mpRotateFrame = CResourceManager::Get<CModel>("RotateFloorFrame");

	// 櫂t年する床モデルを取得(コライダーも)
	mpRotateFloor = CResourceManager::Get<CModel>("RotateFloor");
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpRotateFloor, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });

	// 生成時に設定された触れた時に反応するオブジェクトタグと
	// コライダーのレイヤーを個別に設定
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderMesh->SetCollisionTag(mReactionTag, true);

	ChangeState(EState::Idle);

	Position(pos);
	Scale(scale);

	SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
}

// デストラクタ
CRotateFloorTimeGimmick::~CRotateFloorTimeGimmick()
{
	SAFE_DELETE(mpColliderMesh);
}

// 衝突処理
void CRotateFloorTimeGimmick::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;
}

// ステージの開始時の位置を設定
void CRotateFloorTimeGimmick::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// 状態を切り替える
void CRotateFloorTimeGimmick::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// 回転状態を切り替える
void CRotateFloorTimeGimmick::ChangeRotationState()
{
	mNextRotateIsRotate2 = !mNextRotateIsRotate2;
}

// 待機状態の処理
void CRotateFloorTimeGimmick::UpdateIdle()
{
	mWaitTime -= Time::DeltaTime();
	if (mWaitTime <= 0.0f)
	{
		ChangeRotationState();
		// 現在の回転状態に応じて適切な状態を設定
		if (mNextRotateIsRotate2) {
			ChangeState(EState::Rotate1);
		}
		else {
			ChangeState(EState::Rotate2);
		}
	}
	CDebugPrint::Print("WaitTime:%f\n", mWaitTime);
}

// 回転状態の更新処理1
void CRotateFloorTimeGimmick::UpdateRotate1()
{
	// 1秒間に90度回転する場合の回転速度を計算
	float rotationSpeed = 130.0f / 60.0f; // 1秒間に130度回転（60フレームで1秒）

	// 左端に移動
	Translate(CVector(25.0f, 15.0f, 0.0f));
	// 回転処理
	Rotate(CVector(0.0f, 0.0f, rotationSpeed));
	Translate(CVector(-25.0f, -15.0f, 0.0f));

	// 現在の回転角度を取得
	float currentRotationAngle = GetCurrentRotationAngle();

	// 目標の回転角度が180度の場合
	float targetRotationAngle = 180.0f;

	// Z軸周りの回転角度が目標の角度に達したかを確認
	if (currentRotationAngle >= targetRotationAngle - 1.0f && currentRotationAngle <= targetRotationAngle + 1.0f) {
		// 目標の角度に達したら回転を停止し、Idle状態に変更
		Rotate(CVector(0.0f, 0.0f, 0.0f)); // 回転速度をゼロに設定して停止
		ChangeState(EState::Idle);
		mWaitTime = WAIT_TIME;
	}
}

// 回転状態の更新処理2
void CRotateFloorTimeGimmick::UpdateRotate2()
{
	// 1秒間に90度回転する場合の回転速度を計算
	float rotationSpeed = 130.0f / 60.0f; // 1秒間に130度回転（60フレームで1秒）

	// 左端に移動
	Translate(CVector(25.0f, 15.0f, 0.0f));
	// 回転処理
	Rotate(CVector(0.0f, 0.0f, -rotationSpeed));
	Translate(CVector(-25.0f, -15.0f, 0.0f));

	// 現在の回転角度を取得
	float currentRotationAngle = GetCurrentRotationAngle();

	// 目標の回転角度が180度の場合
	float targetRotationAngle = 0.0f;

	// Z軸周りの回転角度が目標の角度に達したかを確認
	if (currentRotationAngle >= targetRotationAngle - 1.0f && currentRotationAngle <= targetRotationAngle + 1.0f) {
		// 目標の角度に達したら回転を停止し、Idle状態に変更
		// 回転速度をゼロに設定して停止
		Rotate(CVector(0.0f, 0.0f, 0.0f));
		ChangeState(EState::Idle);
		mWaitTime = WAIT_TIME;
	}
}

// 現在の回転値の取得
float CRotateFloorTimeGimmick::GetCurrentRotationAngle() const
{
	// クォータニオンからオイラー角に変換し、Z軸周りの回転角度を取得
	return GetWorldRotation().Euler().Z();
}

// 更新
void CRotateFloorTimeGimmick::Update()
{
	// 現在の状態に合わせて処理を切り替え
	switch (mState)
	{
		// 待機状態
	case EState::Idle:
		UpdateIdle();
		break;
		// 回転状態1
	case EState::Rotate1:
		UpdateRotate1();
		break;
		// 回転状態2
	case EState::Rotate2:
		UpdateRotate2();
		break;
	}

	// 衝突フラグを初期化
	mIsCollision = false;
}

// 描画
void CRotateFloorTimeGimmick::Render()
{
	mpRotateFloor->SetColor(mColor);
	mpRotateFloor->Render(Matrix());
	mpRotateFrame->SetColor(mColor);
	mpRotateFrame->Render(Matrix());
}