#include "CSpikyBall.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "CTrailEffect.h"
#include <Test/Primitive.h>

// 重力
#define GRAVITY 0.0625f

CSpikyBall::CSpikyBall(const CVector& pos, const CVector& dir,
	float speed, float distance)
	: mMoveSpeedY(0.0f)
	, mMoveSpeed(speed)
	, mFlyingDistance(distance)
	, mCurrentFlyingDistance(0.0f)
	, mHasLaunched(false)
	, mMoveSpeedXZ(CVector::zero)
{
	Position(pos);
	Rotation(CQuaternion::LookRotation(dir, CVector::up));

	mpSpikyBallModel = CResourceManager::Get<CModel>("SpikyBall");

	// 軌跡のエフェクトを作成
	mpTrailEffect = new CTrailEffect
	(
		ETag::eWeapon,	// オブジェクトタグ
		this,
		nullptr,
		CVector(0.0f, 0.0f, 0.0f),
		0.01f,			// 更新間隔（時間）
		30.0f,			// 更新間隔（距離）// 変更した(30.0f)
		3.0f,			// 開始時の軌跡の幅
		0.0f,			// 終了時の軌跡の幅
		0.0625f			// 表示時間
	);
	mpTrailEffect->SetTexture("Laser");
	mpTrailEffect->SetColor(CColor(1.0f, 1.0f, 1.0f, 0.6f));

	// 攻撃判定用のコライダーを作成
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eAttackCol,
		5.0f
	);
	// 攻撃判定用のコライダーと衝突判定を行う
	// レイヤーとタグを設定
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::eEnemy });

	// 最初は攻撃判定用のコライダーをオフにしておく
	mpAttackCol->SetEnable(true);

	//SetAlpha(0.0f);
}

CSpikyBall::~CSpikyBall()
{
	mpTrailEffect->SetOwner(nullptr);
	// コライダーを破棄
	SAFE_DELETE(mpAttackCol);
}

// 衝突処理
void CSpikyBall::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// 衝突した自分のコライダーが攻撃判定用コライダーであれば
	if (self == mpAttackCol)
	{
		// キャラのポインタに変換
		CCharaBase* chara = dynamic_cast<CCharaBase*>(other->Owner());
		// 相手のコライダーの持ち主がキャラであれば
		if (chara != nullptr)
		{
			// すでに攻撃済みのキャラでなければ
			if (!IsAttackHitObj(chara))
			{
				//　ダメージを与える
				chara->TakeDamage(2);

				// 攻撃済みリストに追加
				AddAttackHitObj(chara);
			}
		}
	}
}

// 攻撃開始
void CSpikyBall::AttackStart()
{
	// すでに攻撃中であれば、再度開始処理は実行しない
	if (mIsAttack) return;

	CWeapon::AttackStart();
	// 攻撃が始まったら、攻撃判定用のコライダーをオンにする
	mpAttackCol->SetEnable(true);
}

// 攻撃終了
void CSpikyBall::AttackEnd()
{
	CWeapon::AttackEnd();
	// 攻撃が終われば、攻撃判定用のコライダーをオフにする
	mpAttackCol->SetEnable(false);
}

// 武器の行列を取得
CMatrix CSpikyBall::Matrix() const
{
	const CMatrix* attachMtx = GetAttachMtx();
	// 持っていないときは、自分自身の行列を返す
	if (attachMtx == nullptr)
	{
		return CTransform::Matrix();
	}
	// 持っているときは、アタッチしている行列を返す
	else
	{
		CMatrix sm;
		sm.Scale(8.5f, 8.5f, 8.5f);

		return sm * (*attachMtx);
	}
}

void CSpikyBall::SetSpeed(float newSpeed)
{
	mMoveSpeed = newSpeed;
}

void CSpikyBall::SetDistance(float newDistance)
{
	mFlyingDistance = newDistance;
}

// 更新処理
void CSpikyBall::Update()
{
	if (IsKill()) return;
	
	CPlayer* player = CPlayer::Instance();
	bool hand = player->IsSpikyBall();

	if (hand)
	{
		if (!mHasLaunched)
		{
			mHasLaunched = true;
			mMoveSpeedY = 1.4f;
		}
		else
		{

		}

		CDebugPrint::Print("has:%s\n", mHasLaunched ? "true" : "false");
		// 残り飛距離が0ならば、弾丸削除
		float remain = mFlyingDistance - mCurrentFlyingDistance;
		if (remain <= 0.0f)
		{
			Kill();
			return;
		}

		mMoveSpeedY -= GRAVITY;

		// 移動速度を計算
		// 移動速度が残りの飛距離より大きい場合は、
		// 残りの飛距離を移動速度とする
		float moveSpeed = mMoveSpeed * Time::DeltaTime();
		if (abs(moveSpeed) > remain)
		{
			moveSpeed = remain * (moveSpeed < 0.0f ? -1.0f : 1.0f);
		}

		// 水平方向の移動
		Position(Position() + player->VectorZ() * moveSpeed);

		CVector moveSpeedXZ = mMoveSpeedXZ + CVector(0.0f, mMoveSpeedY, 0.0f * Time::DeltaTime());

		// 移動
		Position(Position() + moveSpeedXZ * 60.0f * Time::DeltaTime());

		// 現在の飛距離を更新
		mCurrentFlyingDistance += abs(moveSpeed);

		//CDebugPrint::Print("mMoveSpeedY:%f\n", mMoveSpeedY);
	}
	else
	{

	}
	/*CDebugPrint::Print("distance:%f\n", mFlyingDistance);
	CDebugPrint::Print("speed:%f\n", mMoveSpeed);*/
}

// 描画処理
void CSpikyBall::Render()
{
	mpSpikyBallModel->SetColor(mColor);
	mpSpikyBallModel->Render(Matrix());
	Primitive::DrawSphere(Matrix(), 0.5f, mColor);
}