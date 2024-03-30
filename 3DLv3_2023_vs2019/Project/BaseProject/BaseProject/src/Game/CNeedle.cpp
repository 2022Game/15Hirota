#include "CNeedle.h"
#include "CCharaBase.h"
#include "Maths.h"

// 針の上昇する際の最大値
#define MAXHEIGHT 0.8f
// 針の上昇スピード
#define NEEDLE_INCREASE_VALUE 30.0f
// 針の下降スピード
#define NEEDLE_DESCENDING_VALUE 20.0f

// 攻撃待機時間
#define ATTACKWAIT_TIME 3.0f
// 待機時間
#define WAIT_TIME 5.0f
// 戻り状態
#define RETURN_TIME 5.0f
// 攻撃後の再起時間
#define WAIT_ATTACK_TIME 5.0f

// コンストラクタ
CNeedle::CNeedle(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eNeedle)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mWait(0.0f)
	, mReturnTime(0.0f)
	, mAttackWait(0.0f)
	, mWaitAttackTime(0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
	, mIsAttack(false)
{
	// 初期位置を設定
	mStartPos = Position();

	// 針モデル取得
	mpNeedle = CResourceManager::Get<CModel>("Needle");

	// 針モデルのコライダーを作成
	CModel* Col = CResourceManager::Get<CModel>("NeedleCol");
	mpColliderMesh = new CColliderMesh(this, ELayer::eNeedleCol, Col, true);
	// 衝突定用のコライダーと衝突判定を行う
	// タグ付け
	// レイヤー付け
	// コライダーの位置を調整
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer, ETag::eItemRecover, ETag::eItemInvincible });
	mpColliderMesh->SetCollisionLayers({ ELayer::eDamageCol, ELayer::eRecoverCol, ELayer::eInvincbleCol });

	// 生成時に設定された触れた時に反応するオブジェクトタグと
	// コライダーのレイヤーを個別に設定
	mpColliderMesh->SetCollisionTag(mReactionTag, true);
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);


	// 針モデルのコライダーを作成
	CModel* Col1 = CResourceManager::Get<CModel>("NeedleBaseCol");
	mpColliderBaseMesh = new CColliderMesh(this, ELayer::eField, Col1, true);
	// 衝突定用のコライダーと衝突判定を行う
	// タグ付け
	// レイヤー付け
	// コライダーの位置を調整
	mpColliderBaseMesh->SetCollisionTags({ ETag::ePlayer, ETag::eItemRecover, ETag::eItemInvincible });
	mpColliderBaseMesh->SetCollisionLayers({ ELayer::ePlayer, ELayer::eRecoverCol, ELayer::eInvincbleCol });

	// 生成時に設定された触れた時に反応するオブジェクトタグと
	// コライダーのレイヤーを個別に設定
	mpColliderBaseMesh->SetCollisionTag(mReactionTag, true);
	mpColliderBaseMesh->SetCollisionLayer(mReactionLayer, true);


	ChangeState(EState::Idle);

	Position(pos);
	Scale(scale);
	Rotation(rot);
}

// デストラクタ
CNeedle::~CNeedle()
{
	SAFE_DELETE(mpColliderMesh);
	SAFE_DELETE(mpColliderBaseMesh)
}

// 衝突処理
void CNeedle::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// 衝突した自分のコライダーが針コライダーであれば
	if (self == mpColliderMesh)
	{
		// キャラのポインタに変換
		CCharaBase* chara = dynamic_cast<CCharaBase*>(other->Owner());
		// 相手のコライダーの持ち主がキャラであれば
		if (chara != nullptr)
		{
			// すでに攻撃済みのキャラでなければ
			if (!IsAttackHitObj(chara))
			{
				// ダメージを与える
				chara->TakeDamage(1);

				// 攻撃済みリストに追加
				AddAttackHitObj(chara);

				mIsAttack = true;
			}
			mIsCollision = true;
		}
	}

}

// ステージ開始時の位置を設定
void CNeedle::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// 攻撃開始
void CNeedle::AttackStart()
{
	CRideableObject::AttackStart();
	// 攻撃が始まったら、攻撃判定用のコライダーをオフにする
	mpColliderMesh->SetEnable(true);
}

// 攻撃終了
void CNeedle::AttackEnd()
{
	CRideableObject::AttackEnd();
	// 攻撃が終われば、攻撃判定用のコライダーをオフにする
	mpColliderMesh->SetEnable(false);
}

// 状態を切り替える
void CNeedle::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// 待機状態の処理
void CNeedle::UpdateIdle()
{
	mpColliderBaseMesh->SetEnable(true);
	if (mWait <= WAIT_TIME)
	{
		ChangeState(EState::Attack);
	}
}

// 攻撃状態
void CNeedle::UpdateAttack()
{
	// ステップごとに処理を切り替え
	switch (mStateStep)
	{
		// ステップ0 攻撃後の待ち時間
	case 0:
		// 針を上昇させる
		if (Position().Y() < mStartPos.Y() + MAXHEIGHT)
		{
			mpColliderMesh->SetEnable(true);
			// 上昇させる
			CVector mSpeed = mMoveSpeed;
			mSpeed = CVector(0.0f, NEEDLE_INCREASE_VALUE * Time::DeltaTime(), 0.0f);
			Position(Position() + mSpeed);
		}
		// 最大値になったら、待機させる
		else
		{
			mAttackWait += Time::DeltaTime();
			if (mAttackWait >= ATTACKWAIT_TIME)
			{
				mStateStep++;
			}
		}
		break;
		// ステップ1 針を戻す
	case 1:
		// 下降させる
		CVector mDawnSpeed = mMoveSpeed;
		mDawnSpeed = CVector(0.0f, NEEDLE_DESCENDING_VALUE * Time::DeltaTime(), 0.0f);
		Position(Position() - mDawnSpeed);

		// 針オブジェクトの位置が0.5fになったら
		// 元の位置に戻す
		if (CVector::Distance(Position(), mStartPos) < 0.5f)
		{
			Position(mStartPos);
			// 当たった後の状態に遷移
			ChangeState(EState::AttackEnd);
			mStateStep = 0;
			mAttackWait = 0.0f;
			mpColliderMesh->SetEnable(false);
		}
		break;
	}
}

// 攻撃終了状態
void CNeedle::UpdateAttackEnd()
{
	mpColliderBaseMesh->SetEnable(true);
	mWait += Time::DeltaTime();
	if (mWait >= WAIT_TIME)
	{
		mWait = 0.0f;
		ChangeState(EState::Idle);
	}
}

// 更新
void CNeedle::Update()
{
	if (mIsAttack)
	{
		mpColliderMesh->SetEnable(false);
		mWaitAttackTime += Time::DeltaTime();
		if (mWaitAttackTime >= WAIT_ATTACK_TIME)
		{
			// プレイヤーに当たった時間をリセット
			mWaitAttackTime = 0.0f;
			mIsAttack = false;
			mAttackHitObjects.clear();
		}
	}

	// 現在の状態に合わせて処理を切り替え
	switch (mState)
	{
		// 待機状態
	case EState::Idle:
		UpdateIdle();
		break;
		// 攻撃状態
	case EState::Attack:
		UpdateAttack();
		break;
		// 攻撃終了状態
	case EState::AttackEnd:
		UpdateAttackEnd();
		break;
	}
	//CDebugPrint::Print("wait%f\n", mWait);
	//CDebugPrint::Print("attackwait%f\n", mAttackWait);
	//CDebugPrint::Print("waitAttackTime%f\n", mWaitAttackTime);
}

// 描画
void CNeedle::Render()
{
	mpNeedle->SetColor(mColor);
	mpNeedle->Render(Matrix());
}


// 針モデルの土台
CNeedleBase::CNeedleBase(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eNeedle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
{
	// 初期位置を設定
	mStartPos = Position();

	// 針ベースモデル
	mpNeedleBase = CResourceManager::Get<CModel>("Needlebase");

	Position(pos);
	Scale(scale);
	Rotation(rot);
}

// デストラクタ
CNeedleBase::~CNeedleBase()
{
	
}

void CNeedleBase::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

void CNeedleBase::Update()
{
}

void CNeedleBase::Render()
{
	mpNeedleBase->SetColor(mColor);
	mpNeedleBase->Render(Matrix());
}