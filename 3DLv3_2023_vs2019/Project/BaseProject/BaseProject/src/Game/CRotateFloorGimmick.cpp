#include "CRotateFloorGimmick.h"
#include "Maths.h"
#include "CPlayer.h"

CPlayer* playerInstance = CPlayer::Instance();

// コンストラクタ
CRotateFloorGimmick::CRotateFloorGimmick(const CVector& pos, const CVector& scale,
	 ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eRotate)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mRotationAngle(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
	, mIsJumping(false)
	, mNextRotateIsRotate2(false)
{
	// 初期位置を設定
	mStartPos = Position();

	// 回転する床枠モデルを取得
	mpRotateFrame = CResourceManager::Get<CModel>("RotateFloorFrame");

	// 回転する床モデルを取得(コライダーも)
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
CRotateFloorGimmick::~CRotateFloorGimmick()
{
	SAFE_DELETE(mpColliderMesh);
}

// 衝突処理
void CRotateFloorGimmick::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;
}

// ステージ開始時の位置を設定
void CRotateFloorGimmick::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// 状態を切り替える
void CRotateFloorGimmick::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// 回転状態を切り替える
void CRotateFloorGimmick::ChangeRotationState() {
	mNextRotateIsRotate2 = !mNextRotateIsRotate2;
}

// 待機状態の処理
void CRotateFloorGimmick::UpdateIdle()
{
	CPlayer* player = CPlayer::Instance();
	bool isPlayerJumping = player->IsJumping();
	if (isPlayerJumping && IsFoundPlayer() && !mIsJumping) {
		// プレイヤーがジャンプしているかどうかを使用して判別処理を行う
		mIsJumping = true;
		ChangeRotationState(); // 回転状態を切り替え
		 // 現在の回転状態に応じて適切な状態を設定
		if (mNextRotateIsRotate2) {
			ChangeState(EState::Rotate1);
		}
		else {
			ChangeState(EState::Rotate2);
		}
	}
}

// 回転状態の更新処理1
void CRotateFloorGimmick::UpdateRotateStart()
{
	// 目標の回転角度が0度の場合
	float targetRotationAngle = 180.0f;

	float totalNumberOfFrames = 180.0f / 15.0f;	// * 60.0f / 4.0f

	// 現在の回転角度を取得
	float currentRotationAngle = GetCurrentRotationAngle();

	// 目標の回転角度と現在の回転角度の差を計算
	float rotationDifference = targetRotationAngle - currentRotationAngle;

	// 回転速度を1フレームごとの回転量に反映
	float rotationSpeedPerFrame = rotationDifference / totalNumberOfFrames;

	// 左端に移動
	Translate(CVector(25.0f, 15.0f, 0.0f));
	// 回転処理
	Rotate(CVector(0.0f, 0.0f, rotationSpeedPerFrame));
	Translate(CVector(-25.0f, -15.0f, 0.0f));

	// 目標角度を正規化する
	while (targetRotationAngle < 0.0f)
	{
		targetRotationAngle += 360.0f;
	}
	while (targetRotationAngle >= 360.0f)
	{
		targetRotationAngle -= 360.0f;
	}

	const float rotationThreshold = 1.0f;

	// Z軸周りの回転角度が目標の角度に達したかを確認
	if (fabs(currentRotationAngle - targetRotationAngle) <= rotationThreshold)
	{
		// 目標の角度に達したら回転を停止し、Idle状態に変更
		// 回転速度をゼロに設定して停止
		Rotate(CVector(0.0f, 0.0f, 0.0f));
		ChangeState(EState::Idle);
		mIsJumping = false;
	}
}

// 回転状態の更新処理2
void CRotateFloorGimmick::UpdateRotateEnd()
{
	// 目標の回転角度が0度の場合
	float targetRotationAngle = 0.0f;

	float totalNumberOfFrames = 180.0f / 15.0f;	// * 60.0f / 4.0f

	// 現在の回転角度を取得
	float currentRotationAngle = GetCurrentRotationAngle();

	// 目標の回転角度と現在の回転角度の差を計算
	float rotationDifference = targetRotationAngle - currentRotationAngle;

	// 回転速度を1フレームごとの回転量に反映
	float rotationSpeedPerFrame = rotationDifference / totalNumberOfFrames;

	// 左端に移動
	Translate(CVector(25.0f, 15.0f, 0.0f));
	// 回転処理
	Rotate(CVector(0.0f, 0.0f, rotationSpeedPerFrame));
	Translate(CVector(-25.0f, -15.0f, 0.0f));

	// 目標角度を正規化する
	while (targetRotationAngle < 0.0f)
	{
		targetRotationAngle += 360.0f;
	}
	while (targetRotationAngle >= 360.0f)
	{
		targetRotationAngle -= 360.0f;
	}

	const float rotationThreshold = 1.0f;

	// Z軸周りの回転角度が目標の角度に達したかを確認
	if (fabs(currentRotationAngle - targetRotationAngle) <= rotationThreshold)
	{
		// 目標の角度に達したら回転を停止し、Idle状態に変更
		// 回転速度をゼロに設定して停止
		Rotate(CVector(0.0f, 0.0f, 0.0f));
		ChangeState(EState::Idle);
		mIsJumping = false;
	}
}

// 現在の回転値の取得
float CRotateFloorGimmick::GetCurrentRotationAngle() const
{
	// クォータニオンからオイラー角に変換し、Z軸周りの回転角度を取得
	float rotationAngle = GetWorldRotation().Euler().Z();
	// 角度が負数の場合は正規化する
	while (rotationAngle < 0.0f)
	{
		rotationAngle += 360.0f;
	}
	// 角度が360度を超えた場合は正規化する
	while (rotationAngle >= 360.0f)
	{
		rotationAngle -= 360.0f;
	}
	return rotationAngle;
}

// 更新
void CRotateFloorGimmick::Update()
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
		UpdateRotateStart();
		break;
		// 回転状態2
	case EState::Rotate2:
		UpdateRotateEnd();
		break;
	}

	// 衝突フラグを初期化
	mIsCollision = false;
}

// 描画
void CRotateFloorGimmick::Render()
{
	mpRotateFloor->SetColor(mColor);
	mpRotateFloor->Render(Matrix());
	mpRotateFrame->SetColor(mColor);
	mpRotateFrame->Render(Matrix());
}

//プレイヤーを見つけたか
bool CRotateFloorGimmick::IsFoundPlayer() const
{
	CVector playerPos = CPlayer::Instance()->Position();
	CVector object = Position();

	// プレイヤーとの距離を計算する
	float distance = (playerPos - object).Length();
	const float detectionRadius = 100.0f;

	// プレイヤーとの距離が検出半径以内であれば、プレイヤーを認識する
	if (distance <= detectionRadius)
	{
		return true;
	}

	return false;
}