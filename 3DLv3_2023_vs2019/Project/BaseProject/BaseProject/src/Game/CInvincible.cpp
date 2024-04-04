#include "CInvincible.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"
#include "CSound.h"

// 重力
#define GRAVITY 0.0625f
// 無敵アイテムのスピード
#define INVINCIBLE_SPEED 45.0f
// 無敵アイテムの時間切り替え処理
#define TIMERETURN 2.0f
// 無敵アイテムの跳ねる速度
#define BOUNCE_FORCE 1.5f
// カウント処理
#define SWITCHCOUNTER 15

CInvincible::CInvincible()
	: mSwitchCounter(0)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mMoveVector(0.0f, 0.0f, 0.0f)
	, mElapsedTime(0.0f)
	, mIsGround(false)
	, mInvincibleUsed(false)
	, mIsHeld(false)
{
	// 無敵アイテムモデル取得
	mpInvincibleModel = CResourceManager::Get<CModel>("Star");

	// 無敵アイテムを取った時SE取得
	mpInvincibleSE = CResourceManager::Get<CSound>("8bitMutekiTime");

	// 無敵アイテムコライダー作成
	mpInvincibleCol = new CColliderSphere
	(
		this, ELayer::eInvincbleCol,
		1.5f
	);
	// 衝突定用のコライダーと衝突判定を行う
	// タグ付け
	// レイヤー付け
	// コライダーの位置を調整
	mpInvincibleCol->SetCollisionTags({ ETag::ePlayer, ETag::eRideableObject, ETag::eField,});
	mpInvincibleCol->SetCollisionLayers({ ELayer::ePlayer, ELayer::eBlockCol, ELayer::eField,ELayer::eFieldWall });
	mpInvincibleCol->Position(0.0f, 1.0f, 0.0f);

	// 最初はコライダーをオンにしておく
	mpInvincibleCol->SetEnable(true);

}

CInvincible::~CInvincible()
{
	SAFE_DELETE(mpInvincibleCol);
}


// 衝突処理
void CInvincible::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// 衝突した自分のコライダーが攻撃判定用のコライダーであれば
	if (self == mpInvincibleCol)
	{
		CPlayer* player = dynamic_cast<CPlayer*>(other->Owner());
		if (player)
		{
			// すでに無敵のキャラでなければ
			if (!IsAttachHitObjInvincible(player) && !mInvincibleUsed)
			{
				//mpInvincibleSE->Play(1.0f, false, 0.0f);
				mInvincibleUsed = true;
				// 無敵状態(コライダーオフ)
				//player->TakeInvincible();

				// 無敵リストに追加
				AddAttachHitObjInvincible(player);

				if (mInvincibleUsed)
				{
					Kill();
				}
			}
		}
		else if (other->Layer() == ELayer::eField)
		{
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eBlockCol)
		{
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust);
		}
	}
}


// 移動処理
void CInvincible::MoveFront()
{
	// 速度を設定
	float moveSpeed = INVINCIBLE_SPEED;

	// mTargetDir に速度を掛けて移動ベクトルを得る
	mMoveVector = mTargetDir * moveSpeed;

	// deltaTime を考慮して移動量を計算
	mMoveVector *= Time::DeltaTime();
}

void CInvincible::MoveBack()
{
	// 速度を設定
	float moveSpeed = INVINCIBLE_SPEED;

	// mTargetDir に速度を掛けて移動ベクトルを得る
	mMoveVector = mTargetDir * -moveSpeed;

	// deltaTime を考慮して移動量を計算
	mMoveVector *= Time::DeltaTime();
}

void CInvincible::MoveLight()
{
	// 速度を設定
	float moveSpeed = INVINCIBLE_SPEED;

	// mTargetDir を横方向に変更（左右に動く）
	CVector moveDirection(mTargetDir.Z(), 0.0f, mTargetDir.X());
	moveDirection.Normalize();

	// mTargetDir に速度を掛けて移動ベクトルを得る
	mMoveVector = moveDirection * moveSpeed;

	// deltaTime を考慮して移動量を計算
	mMoveVector *= Time::DeltaTime();
}

void CInvincible::MoveReft()
{
	// 速度を設定
	float moveSpeed = INVINCIBLE_SPEED;

	// mTargetDir を横方向に変更（左右に動く）
	CVector moveDirection(-mTargetDir.Z(), 0.0f, mTargetDir.X());
	moveDirection.Normalize();

	// mTargetDir に速度を掛けて移動ベクトルを得る
	mMoveVector = moveDirection * moveSpeed;

	// deltaTime を考慮して移動量を計算
	mMoveVector *= Time::DeltaTime();
}

void CInvincible::OnTouch(CPlayer* player)
{
	if (mIsHeld)
	{
		player->AddItem(CPlayer::ItemType::INVINCIBLE);
		mIsHeld = true;
	}
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

	// タイム加算
	mElapsedTime += Time::DeltaTime();
	
	// タイムが2秒以下だったら
	if (mElapsedTime >= TIMERETURN)
	{
		// カウントを増加
		mSwitchCounter++;
		// カウントが15回になるとKill処理を実行
		if (mSwitchCounter == SWITCHCOUNTER)
		{
			Kill();
		}
		// ランダムに移動させる処理
		int random = Math::Rand(0, 3);
		switch (random)
		{
		case 0:
			// 手前に移動
			MoveFront();
			break;
		case 1:
			// 奥に移動
			MoveBack();
			break;
		case 2:
			// 右に移動
			MoveLight();
			break;
		case 3:
			// 左に移動
			MoveReft();
			break;
		default:
			break;
		}

		// 処理が一つ終わるとタイムを初期化
		mElapsedTime = 0.0f;
	}

	// 移動
	Position(Position() + mMoveVector + mMoveSpeed * 60.0f * Time::DeltaTime());

	// 確認
	//CDebugPrint::Print("TIme:%f\n", mElapsedTime);

	mIsGround = false;
}

// 描画
void CInvincible::Render()
{
	mpInvincibleModel->SetColor(mColor);
	mpInvincibleModel->Render(Matrix());
}