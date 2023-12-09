#include "CSoldier.h"
#include "CCamera.h"
#include "CBillBoard.h"
#include "CImage.h"
#include "CPlayer.h"
#include <algorithm>
#include "Maths.h"
#include <BaseSystem/CInput.h>
#include "CGun.h"
#include "CBullet.h"
#include "CKick.h"
#include "CSoldierFrame.h"
#include "CSoldierGauge.h"

#define _USE_MATH_DEFINES


// フレームの線の幅
#define FRAME_BORDER	(1.0f)


// バーの横サイズ
#define NEW_BAR_SIZE_X	(139.0f)
// バーの縦サイズ
#define NEW_BAR_SIZE_Y	(11.5f)

// バーの横サイズ * 線の幅
#define BAR_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// バーの縦サイズ * 線の幅
#define BAR_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)


// CSoldierのインスタンス
CSoldier* CSoldier::spInstance = nullptr;

//// CSoldierのモデルデータのパス
//#define MODEL_PATH	"Character\\Gas mask soldier\\GasMask_Soldier_Model.x"

#define EFFECT	 "Effect\\exp.tga"

// CSoldierのアニメーションデータのテーブル
const CSoldier::AnimData CSoldier::ANIM_DATA[] =
{
	{ "",																				true,	  0.0f	},	// Tポーズ
	{ "Character\\Gas mask soldier\\anim\\Rifle_Idle1_515.x",							true,   515.0f	},	// Idle時
	{ "Character\\Gas mask soldier\\anim\\Rifle_Idle3_187.x",							true,   187.0f	},	// ライフルIdle時
	{ "Character\\Gas mask soldier\\anim\\Rifle_walk_79.x",								true,	 79.0f	},	// 移動
	{ "Character\\Gas mask soldier\\anim\\Alert_83.x",									true,	 83.0f	},	// 警戒
	{ "Character\\Gas mask soldier\\anim\\Rifle_1shot_71.x",							true,	 71.0f	},	// プレイヤー発見時攻撃
	{ "Character\\Gas mask soldier\\anim\\Right foot kick_121.x",					false,	121.0f	},		// 格闘
	{ "Character\\Gas mask soldier\\anim\\Reload_199.x",								true,	 99.0f	},	// リロード
	{ "Character\\Gas mask soldier\\anim\\Rilfle_Aim_to_Dwon._91.x",				false,	 91.0f	},		// エイム解除
	{ "Character\\Gas mask soldier\\anim\\Hit_27.x",								false,	 27.0f	},		// Hit

};

#define ENEMY_HEIGHT 8.0f
#define ENEMY_HEIGHT2 20.0f
#define MOVE_SPEED 0.5f
#define JUMP_SPEED 1.5f
#define GRAVITY 0.0625f
#define JUMP_END_Y 1.0f

//移動速度
#define FOV_ANGLE 100.0f		// 視野の角度(ー角度+角度も出)
#define ATTACK_RANGE 70.0f	// プレイヤーまでの距離
#define ATTACK_RANGE_KICK 27.0f

// HP関連
#define HP 5

// レベル関連
#define LEVEL 1

// 攻撃力関連
#define ATTACK 10

// 弾丸の発射間隔
#define ATTACK 10

// 弾丸の発射間隔
#define SHOT_INTERVAL 0.1f

// 敵を見失った後の時間
#define PLAYER_LOST 10.0f

// コンストラクタ
CSoldier::CSoldier()
	: CXCharacter(ETag::eEnemy, ETaskPriority::eEnemy)
	, mState(EState::eIdle)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mpRideObject(nullptr)
	, mTimeShot(0)
	, mTimeShotEnd(20)
	, mElapsedTime(0.0f)
	, mElapsedTime_End(0.0f)
{
	//インスタンスの設定
	spInstance = this;

	// モデルデータ取得
	CModelX* model = CResourceManager::Get<CModelX>("Soldier");

	mpFrame = new CSoldierFrame();
	mpGauge = new CSoldierGauge();

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
		CVector(0.0f, ENEMY_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eField });

	// ダメージを受けるコライダーを作成
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.5f //後で変更
	);
	// ダメージを受けるコライダーと
	// 衝突判定を行うコライダーのレイヤーとタグを設定
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol });
	mpDamageCol->SetCollisionTags({ ETag::eWeapon });
	// ダメージを受けるコライダーを少し下へずらす
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx);


	// 右足にダメージコライダーを設定
	mpKick = new CKick();
	mpKick->AttachMtx(GetFrameMtx("Armature_mixamorig_RightToeBase"));
	mpKick->SetOwner(this);


	// 銃を作成して持たせる
	mpGun = new CGun();
	mpGun->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHand"));
	mpGun->SetOwner(this);

	//const CMatrix* bodyMtx = GetFrameMtx("Armature_")

	// 最初に1レベルに設定
	ChangeLevel(1);
}


CSoldier::~CSoldier()
{
	if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}

	// ダメージを受けるコライダーを削除
	if (mpDamageCol != nullptr)
	{
		delete mpDamageCol;
		mpDamageCol = nullptr;
	}

}

CSoldier* CSoldier::Instance()
{
	return spInstance;
}

// レベルアップ
void CSoldier::LevelUp()
{
	int level = mCharaStatus.level;
	ChangeLevel(level + 1);
}

// レベルを変更
void CSoldier::ChangeLevel(int level)
{
	// ステータスのテーブルのインデックス地に変換
	int index = Math::Clamp(level - 1, 0, ENEMY_LEVEL_MAX);
	// 最大ステータスに設定
	mCharaMaxStatus = ENEMY_STATUS[index];
	// 現在のステータスを最大値にすることで、HP回復
	mCharaStatus = mCharaMaxStatus;

	// 最大HPと現在HPをHPゲージに反映
	mpGauge->SetMaxValue(mCharaMaxStatus.hp);
	mpGauge->SetValue(mCharaStatus.hp);
}

// アニメーション切り替え
void CSoldier::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// 待機
void CSoldier::UpdateIdle()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	//プレイヤーを見つけたら、追跡状態へ移行
	if (IsFoundPlayer())
	{
		mState = EState::eChase;
	}
	else
	{
		ChangeAnimation(EAnimType::eIdle);
	}
}

// 追跡
void CSoldier::UpdateChase()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	if (!IsFoundPlayer())
	{
		ChangeAnimation(EAnimType::eRifleIdle);
		mElapsedTime_End += Time::DeltaTime();
		CDebugPrint::Print("TimeEnd%f\n", mElapsedTime_End);
		if (mElapsedTime_End >= PLAYER_LOST)
		{
			mState = EState::eAimDwon;
			mElapsedTime_End = 0.0f; // プレイヤーが視界から消えたら経過時間をリセット
		}
	}
	else
	{
		mElapsedTime_End = 0.0f;
		CPlayer* player = CPlayer::Instance();
		CVector playerPos = player->Position();
		playerPos.Y(Position().Y());

		CVector toPlayer = (playerPos - Position()).Normalized();
		mMoveSpeed += toPlayer * MOVE_SPEED;
		mTargetDir = toPlayer;

		// プレイヤーとの距離が一定範囲以内であれば攻撃モードに切り替える
		float distanceToPlayer = (player->Position() - Position()).Length();
		ChangeAnimation(EAnimType::eAlert);
		
		if (distanceToPlayer <= ATTACK_RANGE)
		{
			mState = EState::eAttack;
		}
	}
}


// 攻撃
void CSoldier::UpdateAttack()
{
	// 攻撃するときは移動を停止
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	// プレイヤーのポインタが0以外の時
	CPlayer* player = CPlayer::Instance();

	// プレイヤーまでのベクトルを求める
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	if (distancePlayer <= ATTACK_RANGE)
	{
		ChangeAnimation(EAnimType::eAttack);
		// 弾丸発射間隔時間が経過するのを待つ
		if (mElapsedTime < SHOT_INTERVAL)
		{
			mElapsedTime += Time::DeltaTime();
		}
		// 弾丸発射間隔が経過した
		else
		{
			mElapsedTime -= SHOT_INTERVAL;

			// 弾丸を発射
			CBullet* bullet = new CBullet();
			bullet->Position(CVector(0.0f, 10.0f, 10.0f) * Matrix());
			bullet->Rotation(Rotation());

			// 全弾発射したら、攻撃終了
			mTimeShot++;
			if (mTimeShot >= mTimeShotEnd)
			{
				// 攻撃終了後の待機状態に遷移
				mState = EState::eAttackWait;
				mTimeShot = 0;
				mElapsedTime = 0.0f;
			}
			if (distancePlayer <= ATTACK_RANGE_KICK)
			{
				mState = EState::eKick;
				return;
			}
		}
	}
	else
	{
		mState = EState::eChase;
		mElapsedTime_End = 0.0f;
	}
}

// キック
void CSoldier::UpdateKick()
{
	// 攻撃するときは移動を停止
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	// プレイヤーのポインタが0以外の時
	CPlayer* player = CPlayer::Instance();

	// プレイヤーまでのベクトルを求める
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();

	ChangeAnimation(EAnimType::eKick);
	if (mAnimationFrame >= 45.0f && mAnimationFrame < 60.0f)
	{
		mpKick->AttackStart();
		mState = EState::eKickWait;
	}
}

// キック終了
void CSoldier::UpdateKickWait()
{
	if (IsAnimationFinished())
	{
		mState = EState::eChase;
		ChangeAnimation(EAnimType::eIdle);

		mpKick->AttackEnd();
	}
}

// 攻撃終了待ち
void CSoldier::UpdateAttackWait()
{
	ChangeAnimation(EAnimType::eReload);
	if (IsAnimationFinished())
	{
		CPlayer* player = CPlayer::Instance();
		float distanceToPlayer = (player->Position() - Position()).Length();

		if (distanceToPlayer <= ATTACK_RANGE)
		{
			mState = EState::eAttack;
		}
		else
		{
			mState = EState::eAimDwon;
			mElapsedTime_End = 0.0f;
		}
	}
}

// エイム解除
void CSoldier::UpdateAimDwon()
{
	ChangeAnimation(EAnimType::eAimDwou);
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
		mElapsedTime_End = 0.0f;
	}
}

// プレイヤーの攻撃を受けた時
void CSoldier::UpdateHit()
{
	// ダメージを受けた時は移動を停止
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eHit);
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
	}
}

// ジャンプ開始
void CSoldier::UpdateJumpStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	mState = EState::eJump;

	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
	mIsGrounded = false;
}


// ジャンプ中
void CSoldier::UpdateJump()
{
	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		mState = EState::eJumpEnd;
	}
}

// ジャンプ終了
void CSoldier::UpdateJumpEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
	}
}

// 更新
void CSoldier::Update()
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
		// キック
	case EState::eKick:
		UpdateKick();
		break;
		// キック終了
	case EState::eKickWait:
		UpdateKickWait();
		break;
		// エイム解除
	case EState::eAimDwon:
		UpdateAimDwon();
		break;
		// 攻撃終了待ち
	case EState::eAttackWait:
		UpdateAttackWait();
		break;
		// 追跡状態
	case EState::eChase:
		UpdateChase();
		break;
		// プレイヤーの攻撃Hit
	case EState::eHit:
		UpdateHit();
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

	// CSoldierのデバッグ表示
	static bool debug = false;
	if (CInput::PushKey('F'))
	{
		debug = !debug;
	}
	if (debug)
	{
		//CDebugPrint::Print(" レベル %d\n", mCharaMaxStatus.level);
		CDebugPrint::Print(" HP%d / %d\n", mCharaStatus.hp, mCharaMaxStatus.hp);
		CDebugPrint::Print(" 攻撃値%d\n", mCharaStatus.power);
		CDebugPrint::Print(" ST%d / %d\n", mCharaStatus.stamina, mCharaMaxStatus.stamina);
	}
	// 1キーを押しながら、↑ ↓ でHP増減
	if (CInput::Key('3'))
	{
		if (CInput::PushKey(VK_UP)) mCharaStatus.hp++;
		else if (CInput::PushKey(VK_DOWN)) mCharaStatus.hp--;
	}
	else if (CInput::Key('2'))
	{
		LevelUp();
	}

	// 移動
	Position(Position() + mMoveSpeed * 60.0f * Time::DeltaTime());

	CVector PlayerPosition;

	// CSoldierを移動方向へ向ける
	CVector current = VectorZ();
	CVector target = mTargetDir;
	CVector forward = CVector::Slerp(current, target, 0.125f);
	Rotation(CQuaternion::LookRotation(forward));


	CDebugPrint::Print("Shot%d\n", mTimeShot);
	CDebugPrint::Print("Shotend%d\n", mTimeShotEnd);

	// CSoldierの更新
	CXCharacter::Update();

	mIsGrounded = false;

	
	// カメラの取得
	CCamera* cam = CCamera::CurrentCamera();
	// フレームの位置を頭上に固定
	CVector gaugeWorldPos = Position() + CVector(-5.0f, 30.0f, 0.0f);
	// カメラでワールド座標をスクリーン座標へ変換
	CVector gp = cam->WorldToScreenPos(gaugeWorldPos);

	// プレイヤーの座標
	CVector playerPos = CPlayer::Instance()->Position();
	// プレイヤーと敵の距離を計算
	float distance = (playerPos - Position()).Length();

	// 一定の範囲内に居る場合は表示
	float displayRange = 100.0f;
	if (distance < displayRange)
	{
		// フレーム座標
		mpFrame->SetPos(gp.X(), gp.Y());

		// ゲージの座標を2Dで設定（右にずらす）
		float GaugeOffsetX = 20.0f;
		// ゲージの座標を2Dで設定
		mpGauge->SetPos(gp.X() + GaugeOffsetX, gp.Y());
	}
	else
	{
		// 無理やり非表示
		mpFrame->SetPos(-1000, -1000);
		mpGauge->SetPos(-1000, -1000);
	}

	//// フレームの座標を2Dで設定
	//mpFrame->SetPos(gp.X(), gp.Y());

	//// ゲージの座標を2Dで設定（右にずらす）
	//float GaugeOffsetX = 20.0f;
	//// ゲージの座標を2Dで設定
	//mpGauge->SetPos(gp.X() + GaugeOffsetX, gp.Y());

	// 現在のHpを設定
	mpGauge->SetValue(mCharaStatus.hp);
}

// プレイヤー追跡
bool CSoldier::IsFoundPlayer() const
{
	CVector playerPos = CPlayer::Instance()->Position();
	CVector enemyPos = Position();

	CVector toPlayer = (playerPos - enemyPos).Normalized();
	CVector forward = Matrix().VectorZ().Normalized();

	float dot = forward.Dot(toPlayer);

	// 視野角の半分を計算する
	float halfFOV = FOV_ANGLE * 0.5f;

	//// acos関数を使用して実際の角度を計算する
	//float angle = acos(dot) * (180.0f / M_PI);

	// 視野角の半分より小さいかつプレイヤーとの距離が一定範囲以内であれば、プレイヤーを認識する
	if (dot >= cosf(halfFOV * M_PI / 180.0f))
	{
		float distance = (playerPos - enemyPos).Length();
		const float chaseRange = 100.0f;

		if (distance <= chaseRange)
			return true;
	}

	return false;

}

// 衝突処理
void CSoldier::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
	if (self == mpDamageCol)
	{
		if (other->Layer() == ELayer::eAttackCol)
		{
			mState = EState::eHit;
		}
	}
}

// 描画
void CSoldier::Render()
{
	CXCharacter::Render();
}

// 被ダメージ処理
void CSoldier::TakeDamage(int damage)
{
	// 死亡していたらダメージは受けない
	//if (mCharaStatus.hp <= 0) return;

	// HPからダメージを引く
	//mCharaStatus.hp = std::max(mCharaStatus.hp - damage, 0);
	mCharaStatus.hp -= damage;
	// HPが0になったら
	if (mCharaStatus.hp == 0)
	{
		//死亡処理 後で
	}
}
