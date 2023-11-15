#include "CYukari.h"
#include "CCamera.h"
#include "CBillBoard.h"
#include "CImage.h"
#include "CPlayer.h"
#include <algorithm>
#include "Maths.h"

// プレイヤーのインスタンス
CYukari* CYukari::spInstance = nullptr;

// プレイヤーのモデルデータのパス
#define MODEL_PATH "Character\\Yukari\\Yukari_Model.x"

// プレイヤーのアニメーションデータのテーブル
const CYukari::AnimData CYukari::ANIM_DATA[] =
{
	{ "",													true,	0.0f	},	// Tポーズ
	{ "Character\\Yukari\\anim\\Yukari_GunIdle463.x",		true,	463.0f	},	// Idle時
	{ "Character\\Yukari\\anim\\Yukari_GunWorlk79.x",		true,	79.0f	},	// 移動
	{ "Character\\Yukari\\anim\\Yukari_GunPlay13.x",		true,	13.0f	},	// プレイヤー発見時攻撃

};

#define PLAYER_HEIGHT 8.0f
#define MOVE_SPEED 1.0f
#define JUMP_SPEED 1.5f
#define GRAVITY 0.0625f
#define JUMP_END_Y 1.0f

// コンストラクタ
CYukari::CYukari()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eIdle)
	, mpRideObject(nullptr)
{

	//インスタンスの設定
	spInstance = this;

	// モデルデータ読み込み
	CModelX* model = new CModelX();
	model->Load(MODEL_PATH);

	// テーブル内のアニメーションデータを読み込み
	int size = ARRAY_SIZE(ANIM_DATA);
	for (int i = 0; i < size; i++)
	{
		const AnimData& data = ANIM_DATA[i];
		if (data.path.empty()) continue;
		model->AddAnimationSet(data.path.c_str());
	}
	// CXCharacterの初期化
	Init(model);

	// 最初は待機アニメーションを再生
	ChangeAnimation(EAnimType::eIdle);

	mpColliderLine = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, PLAYER_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eField });

	// ダメージを受けるコライダーを作成
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		5.0f
	);
	// ダメージを受けるコライダーと
	// 衝突判定を行うコライダーのレイヤーとタグを設定
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol });
	mpDamageCol->SetCollisionTags({ ETag::ePlayer });
}

CYukari::~CYukari()
{
	if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}

	if (mpModel != nullptr)
	{
		delete mpModel;
		mpModel = nullptr;
	}

	// ダメージを受けるコライダーを削除
	if (mpDamageCol != nullptr)
	{
		delete mpDamageCol;
		mpDamageCol = nullptr;
	}
}

CYukari* CYukari::Instance()
{
	return spInstance;
}

// レベルアップ
void CYukari::LevelUp()
{
	int level = mCharaStatus_Enemy.level;
	ChangeLevel(level + 1);
}

// レベルを変更
void CYukari::ChangeLevel(int level)
{
	// ステータスのテーブルのインデックス地に変換
	int index = Math::Clamp(level - 1, 0, ENEMY_LEVEL_MAX);
	// 最大ステータスに設定
	mCharaMaxStatus_Enemy = ENEMY_STATUS[index];
	// 現在のステータスを最大値にすることで、HP回復
	mCharaStatus_Enemy = mCharaMaxStatus_Enemy;

}

// アニメーション切り替え
void CYukari::ChangeAnimation(EAnimType type)
{
	if (type != EAnimType::eIdle) return;
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// 待機
void CYukari::UpdateIdle()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	{
		// 待機アニメーションに切り替え
		ChangeAnimation(EAnimType::eIdle);
	}
}

// 攻撃
void CYukari::UpdateAttack()
{
	// 攻撃アニメーションを開始
	ChangeAnimation(EAnimType::eAttack);
	// 攻撃終了待ち状態へ移行
	mState = EState::eAttackWait;
}

// 攻撃終了待ち
void CYukari::UpdateAttackWait()
{
	// 攻撃アニメーションが終了したら、
	if (IsAnimationFinished())
	{
		// 待機状態へ移行
		mState = EState::eIdle;
		ChangeAnimation(EAnimType::eIdle);
	}
}

// ジャンプ開始
void CYukari::UpdateJumpStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	mState = EState::eJump;

	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
	mIsGrounded = false;
}

// ジャンプ中
void CYukari::UpdateJump()
{
	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		mState = EState::eJumpEnd;
	}
}

// ジャンプ終了
void CYukari::UpdateJumpEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
	}
}

// 更新
void CYukari::Update()
{
	SetParent(mpRideObject);
	mpRideObject = nullptr;

	// 状態に合わせて、更新処理を切り替える
	switch (mState)
	{
		// 待機状態
	case EState::eIdle:
		UpdateIdle();
		break;
		// 攻撃
	case EState::eAttack:
		UpdateAttack();
		break;
		// 攻撃終了待ち
	case EState::eAttackWait:
		UpdateAttackWait();
		break;
		// ジャンプ開始
	case EState::eJumpStart:
		UpdateJumpStart();
		break;
		// ジャンプ中
	case EState::eJump:
		UpdateJump();
		break;
		// ジャンプ終了
	case EState::eJumpEnd:
		UpdateJumpEnd();
		break;
	}

	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	// 移動
	Position(Position() + mMoveSpeed);

	CVector PlayerPosition;

	// プレイヤーを移動方向へ向ける
	CVector current = VectorZ();
	CVector target = mMoveSpeed;
	target.Y(0.0f);
	target.Normalize();
	CVector forward = CVector::Slerp(current, target, 0.125f);
	Rotation(CQuaternion::LookRotation(forward));

	// キャラクターの更新
	CXCharacter::Update();

	mIsGrounded = false;
}

// 衝突処理
void CYukari::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (self == mpColliderLine)
	{
		if (other->Layer() == ELayer::eField)
		{
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
			mIsGrounded = true;

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
	}
}

// 描画
void CYukari::Render()
{
	CXCharacter::Render();
}

// 被ダメージ処理
void CYukari::TakeDamage(int damage)
{
	// 死亡していたらダメージは受けない
	if (mCharaStatus_Enemy.hp <= 0) return;

	// HPからダメージを引く
	//mCharaStatus_Enemy.hp = max(mCharaStatus_Enemy.hp - damage, 0);
	// HPが0になったら
	if (mCharaStatus_Enemy.hp == 0)
	{
		//死亡処理 後で
	}
}