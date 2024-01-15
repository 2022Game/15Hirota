#include "CRecoveryObject.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"

#define GRAVITY 0.0625f			// 重力
#define RUN_SPEED 10.0f

#define TIMERETURN 5.0f

CRecoveryObject::CRecoveryObject()
	: mMoveSpeed(0.0f,0.0f,0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mElapsedTime(0.0f)
{
	mpRecoverModel = CResourceManager::Get<CModel>("MajicSword");

	// 回復判定用のコライダー作成
	mpRecoverCol = new CColliderSphere
	(
		this, ELayer::eRecoverCol,
		6.0f
	);
	// 衝突定用のコライダーと衝突判定を行う
	mpRecoverCol->SetCollisionLayers({ ELayer::ePlayer, ELayer::eBlockCol, ELayer::eField,ELayer::eFieldWall });
	mpRecoverCol->SetCollisionTags({ ETag::ePlayer, ETag::eRideableObject, ETag::eField });

	mpRecoverCol->SetEnable(true);

}

CRecoveryObject::~CRecoveryObject()
{
	SAFE_DELETE(mpRecoverCol);
}

void CRecoveryObject::Update()
{
	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	bool time = false;

	Move();
	if (mElapsedTime < TIMERETURN)
	{
		mElapsedTime += Time::DeltaTime();
		if (mElapsedTime > TIMERETURN)
		{
			mpRecoverCol->SetEnable(false);
			SetAlpha(0.0f);
		}
	}
}

void CRecoveryObject::Render()
{
	mpRecoverModel->Render(Matrix());
}

// 衝突処理
void CRecoveryObject::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// 衝突した自分のコライダーが攻撃判定用のコライダーであれば
	if (self == mpRecoverCol)
	{
		CPlayer* player = dynamic_cast<CPlayer*>(other->Owner());
		if (player)
		{
			// すでに回復済みのキャラでなければ
			if (!IsAttachHitObj(player))
			{
				// 回復させる
				player->TakeRecovery(1);

				// 回復済みリストに追加
				AddAttachHitObj(player);
			}
		}
		else if (other->Layer() == ELayer::eField)
		{
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust * hit.weight);
		}
	}
}

// 回復スタート
void CRecoveryObject::RecoverStart()
{
	CItemObjectBase::RecoverStart();
	// 回復が始まったら、回復コライダーをオンにする
	mpRecoverCol->SetEnable(true);
}

// 回復終了
void CRecoveryObject::RecoverEnd()
{
	CItemObjectBase::RecoverEnd();
	// 回復が終われば、回復コライダーをオフにするん
	mpRecoverCol->SetEnable(false);
}


// 移動処理
void CRecoveryObject::Move()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	// 速度を設定
	float moveSpeed = RUN_SPEED;

	// mTargetDir に速度を掛けて移動ベクトルを得る
	CVector moveVector = mTargetDir * moveSpeed;

	// deltaTime を考慮して移動量を計算
	moveVector *= Time::DeltaTime();

	// 現在の座標を更新
	Position(Position() + -moveVector + mMoveSpeed);
}

void CRecoveryObject::MoveZ()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	// 速度を設定
	float moveSpeed = RUN_SPEED;

	// mTargetDir に速度を掛けて移動ベクトルを得る
	CVector moveVector = mTargetDir * moveSpeed;

	// deltaTime を考慮して移動量を計算
	moveVector *= Time::DeltaTime();

	// 現在の座標を更新
	Position(Position() + moveVector + mMoveSpeed);
}