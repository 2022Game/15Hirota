#include "CCannonBall.h"

// 重力
#define GRAVITY 0.0625f

// コンストラクタ
CCannonBall::CCannonBall(const CVector& pos, const CVector& dir,
	float speed, float distance, float verticalSpeed)
	: CObjectBase(ETag::eBullet, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
	, mMoveSpeed(speed)
	, mDirection(dir)
	, mFlyingDistance(distance)
	, mVerticalSpeed(verticalSpeed)
	, mCurrentFlyingDistance(0.0f)
{
	Position(pos);
	Rotation(CQuaternion::LookRotation(dir, CVector::up));

	// 大砲の弾のコライダー
	mpSpherer = new CColliderSphere
	(
		this, ELayer::eBulletCol,
		5.0f
	);
	mpSpherer->SetCollisionLayers({ ELayer::eDamageCol });
	mpSpherer->SetCollisionTags({ ETag::ePlayer });
}

// デストラクタ
CCannonBall::~CCannonBall()
{
	SAFE_DELETE(mpSpherer);
}

// 初速度を設定
void CCannonBall::SetVerticalSpeed(float speed) 
{
	mVerticalSpeed = speed;
}

// 更新処理
void CCannonBall::Update()
{
	if (IsKill()) return;

	// 残り飛距離が0ならば、弾丸削除
	float remain = mFlyingDistance - mCurrentFlyingDistance;
	if (remain <= 0.0f)
	{
		Kill();
		return;
	}

	// 移動速度を計算
	// 移動速度が残りの飛距離より大きい場合は、
	// 残りの飛距離を移動速度とする
	float moveSpeed = mMoveSpeed;
	if (abs(moveSpeed) > remain)
	{
		moveSpeed = remain * (moveSpeed < 0.0f ? -1.0f : 1.0f);
	}

	mVerticalSpeed -= GRAVITY; // 重力を加算

	// 弾丸の位置を更新
	Position(Position() + mDirection * moveSpeed + CVector(0.0f, mVerticalSpeed, 0.0f));

	// 現在の飛距離を更新
	mCurrentFlyingDistance += abs(moveSpeed);
	CDebugPrint::Print("mCurrentFlyingDistance:%f\n", mCurrentFlyingDistance);
	CDebugPrint::Print("mFlyingDistance:%f\n", mFlyingDistance);
}

// 描画処理
void CCannonBall::Render()
{

}