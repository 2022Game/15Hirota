#include "CInvincible.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"

#define GRAVITY 0.0625f			// 重力
#define RUN_SPEED 40.0f

#define TIMERETURN 5.0f

#define BOUNCE_FORCE 1.5f

CInvincible::CInvincible()
	: mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mElapsedTime(1.0f)
	, mIsGround(false)
	, mSwitchCounter(0)
	, mRecoveryUsed(false)
{
	mpRecoverModel = CResourceManager::Get<CModel>("Star");

	// 無敵オブジェコライダー作成
	mpRecoverCol = new CColliderSphere
	(
		this, ELayer::eRecoverCol,
		1.5f
	);
	// 衝突定用のコライダーと衝突判定を行う
	mpRecoverCol->SetCollisionLayers({ ELayer::ePlayer, ELayer::eBlockCol, ELayer::eField,ELayer::eFieldWall });
	mpRecoverCol->SetCollisionTags({ ETag::ePlayer, ETag::eRideableObject, ETag::eField });
	mpRecoverCol->Position(0.0f, 1.0f, 0.0f);

	mpRecoverCol->SetEnable(true);

}

CInvincible::~CInvincible()
{
	SAFE_DELETE(mpRecoverCol);
}

void CInvincible::Update()
{
	// 重力
	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	if (mIsGround)
	{
		mMoveSpeed += CVector(0.0f, BOUNCE_FORCE, 0.0f);
		mIsGround = false;
	}


	// 回転
	float rot = 1.0f;
	Rotate(0.0f, rot, 0.0f);

	// 確認
	CDebugPrint::Print("TIme:%f\n", mElapsedTime);
	// タイム加算
	mElapsedTime += Time::DeltaTime();

	// タイムが2秒以下だったら
	if (mElapsedTime >= 2.0f)
	{
		mSwitchCounter++;
		if (mSwitchCounter == 6)
		{
			Kill();
		}
		// ランダムに移動させる処理
		int random = Math::Rand(0, 3);
		switch (random)
		{
		case 0:
			Move();
			break;
		case 1:
			MoveX();
			break;
		case 2:
			MoveY();
			break;
		case 3:
			MoveZ();
			break;
		default:
			break;
		}

		mElapsedTime = 0.0f;
	}

	// 移動
	Position(Position() + moveVector + mMoveSpeed * 60.0f * Time::DeltaTime());

	mIsGround = false;
}

void CInvincible::Render()
{
	mpRecoverModel->Render(Matrix());
}

// 衝突処理
void CInvincible::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// 衝突した自分のコライダーが攻撃判定用のコライダーであれば
	if (self == mpRecoverCol)
	{
		CPlayer* player = dynamic_cast<CPlayer*>(other->Owner());
		if (player)
		{
			// すでに無敵のキャラでなければ
			if (!IsAttachHitObj(player) && !mRecoveryUsed)
			{
				// 無敵状態(コライダーオフ)
				player->TakeInvincible();

				// 無敵リストに追加
				AddAttachHitObj(player);

				mRecoveryUsed = true;
				if (mRecoveryUsed)
				{
					Kill();
				}
			}
		}
		else if (other->Layer() == ELayer::eField)
		{
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust * hit.weight);
		}
		else if (other->Layer() == ELayer::eBlockCol)
		{
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust * hit.weight);
		}
	}
}
//
//// 回復スタート
//void CInvincible::RecoverStart()
//{
//	CItemObjectBase::RecoverStart();
//	// 回復が始まったら、回復コライダーをオンにする
//	mpRecoverCol->SetEnable(true);
//}
//
//// 回復終了
//void CInvincible::RecoverEnd()
//{
//	CItemObjectBase::RecoverEnd();
//	// 回復が終われば、回復コライダーをオフにするん
//	mpRecoverCol->SetEnable(false);
//}


// 移動処理
void CInvincible::Move()
{
	// 速度を設定
	float moveSpeed = RUN_SPEED;

	// mTargetDir に速度を掛けて移動ベクトルを得る
	moveVector = mTargetDir * moveSpeed;

	// deltaTime を考慮して移動量を計算
	moveVector *= Time::DeltaTime();

	// 現在の座標を更新
	//Position(Position() + -moveVector + mMoveSpeed);
}

void CInvincible::MoveZ()
{
	// 速度を設定
	float moveSpeed = RUN_SPEED;

	// mTargetDir に速度を掛けて移動ベクトルを得る
	moveVector = mTargetDir * moveSpeed;

	// deltaTime を考慮して移動量を計算
	moveVector *= Time::DeltaTime();

	// 現在の座標を更新
	Position(Position() + moveVector + mMoveSpeed);
}

void CInvincible::MoveX()
{
	// 速度を設定
	float moveSpeed = RUN_SPEED;

	// mTargetDir を横方向に変更（左右に動く）
	CVector moveDirection(mTargetDir.Z(), 0.0f, -mTargetDir.X());
	moveDirection.Normalize();

	// mTargetDir に速度を掛けて移動ベクトルを得る
	moveVector = moveDirection * moveSpeed;

	// deltaTime を考慮して移動量を計算
	moveVector *= Time::DeltaTime();

	// 現在の座標を更新
	Position(Position() + moveVector + mMoveSpeed);
}

void CInvincible::MoveY()
{
	// 速度を設定
	float moveSpeed = RUN_SPEED;

	// mTargetDir を横方向に変更（左右に動く）
	CVector moveDirection(mTargetDir.Z(), 0.0f, -mTargetDir.X());
	moveDirection.Normalize();

	// mTargetDir に速度を掛けて移動ベクトルを得る
	moveVector = moveDirection * moveSpeed;

	// deltaTime を考慮して移動量を計算
	moveVector *= Time::DeltaTime();

	// 現在の座標を更新
	Position(Position() + moveVector + mMoveSpeed);
}