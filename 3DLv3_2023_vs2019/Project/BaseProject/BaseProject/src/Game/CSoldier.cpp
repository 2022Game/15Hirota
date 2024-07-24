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
#include "CStageManager.h"
#include "CEnemyManager.h"
#include "CExclamationMark.h"
#include "CGameManager.h"

#define _USE_MATH_DEFINES

// ソルジャー関連
// ソルジャーの頭上
#define ENEMY_HEIGHT 8.0f
// 移動速度
#define MOVE_SPEED 0.7f
// 自動移動速度
#define MOVE_AUTOMATIC_SPEED 30.0f
// ジャンプ速度
#define JUMP_SPEED 1.5f
// 重力加速度
#define GRAVITY 0.0625f


// 追従時移動速度
// 視野の角度(ー角度+角度も出)
#define FOV_ANGLE 100.0f
// プレイヤーまでの距離
#define ATTACK_RANGE 70.0f
// プレイヤーまでの距離(キック)
#define ATTACK_RANGE_KICK 25.0f
// プレイヤーまでの距離(バックステップ)
#define BACKSTEP_RANGE 24.0f
// バックステップの待機時間
#define BACKSTEP_WEIT_TIME 5.0f


// HP関連
#define HP 5
// レベル関連
#define LEVEL 1
// 攻撃力関連
#define ATTACK 10


// 弾丸関連
// 弾丸の発射間隔
#define ATTACK 10

// 弾丸の発射間隔
#define SHOT_INTERVAL 2.0f

// 敵を見失った後の時間
#define PLAYER_LOST 10.0f

// キックコライダーの時間
#define KICKCOL 10.0f

// プレイヤーを発見した後の時間
#define DISCOVERY 2.0f
// プレイヤーを発見した後の待ち時間
#define DISCOVERY_END 40.0f

// CSoldierのインスタンス
CSoldier* CSoldier::spInstance = nullptr;

CSoldier* CSoldier::Instance()
{
	return spInstance;
}

// CSoldierのアニメーションデータのテーブル
const CSoldier::AnimData CSoldier::ANIM_DATA[] =
{
	{ "",																			true,	  0.0f	},	// Tポーズ
	{ "Character\\Gas mask soldier\\anim\\Rifle_Idle1_515.x",						true,   515.0f	},	// Idle時
	{ "Character\\Gas mask soldier\\anim\\Rifle_Idle3_187.x",						true,   187.0f	},	// ライフルIdle時
	{ "Character\\Gas mask soldier\\anim\\Rifle_walk_79.x",							true,	 79.0f	},	// 移動
	{ "Character\\Gas mask soldier\\anim\\Alert_83.x",								true,	 83.0f	},	// 警戒
	{ "Character\\Gas mask soldier\\anim\\Rifle_1shot_71.x",						true,	 71.0f	},	// プレイヤー発見時攻撃
	{ "Character\\Gas mask soldier\\anim\\Right foot kick_121.x",				false,		121.0f	},	// 格闘
	{ "Character\\Gas mask soldier\\anim\\Reload_199.x",							true,	 99.0f	},	// リロード
	{ "Character\\Gas mask soldier\\anim\\Rilfle_Aim_to_Dwon._91.x",			false,		91.0f	},	// エイム解除
	{ "Character\\Gas mask soldier\\anim\\Hit_27.x",							false,		27.0f	},	// Hit
	{ "Character\\Gas mask soldier\\anim\\Death_Fall down1_157.x",				false,		157.0f	},	// 死亡
	{ "Character\\Gas mask soldier\\anim\\BackStep_101.x",						false,		101.0f	},	// バックステップ

};

// コンストラクタ
CSoldier::CSoldier()
	: CXCharacter(ETag::eEnemy, ETaskPriority::eEnemy)
	, mState(EState::eReady)
	, mTimeShot(0)
	, mTimeShotEnd(5)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mElapsedTime_End(0.0f)
	, mKickTime(0.0f)
	, mBackStepTime(0.0f)
	, mDiscoveryTime(0.0f)
	, mDiscoveryTimeEnd(0.0f)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mInitialPosition(0.0f, 0.0f, 0.0f)
	, mTimeToChange(Math::Rand(2.0f, 5.0f))
	, mIsGrounded(false)
	, mKickTimeEnd(false)
	, mDiscovery(false)
	, mDiscoveryEnd(false)
	, mBackStep(false)
	, mpRideObject(nullptr)
{
	//インスタンスの設定
	spInstance = this;

	// 初期位置の保存
	//Position(mInitialPosition);
	mInitialPosition = Position();

	// ソルジャーの数を取得
	CEnemyManager::IncrementSoldierCount();

	// モデルデータ取得
	CModelX* model = CResourceManager::Get<CModelX>("Soldier");

	// フレーム設定
	mpFrame = new CSoldierFrame();
	// 0~1の値を設定
	mpFrame->SetCenterRatio(CVector2(0.5f, 0.0f));
	// ゲージ設定
	mpGauge = new CSoldierGauge();
	mpGauge->SetCenterRatio(CVector2(0.3f, 0.0f));
	// ビックリマーク設定
	mpExclamationMark = new CExclamationMark();
	mpExclamationMark->SetCeneterRatio(CVector2(0.3f, 0.5f));


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

	// フィールドとの当たり判定を取るコライダー
	mpColliderLine = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, ENEMY_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eField });

	// 一時的な当たり判定を取るコライダー
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eEnemy,
		7.0f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::eFieldWall ,ELayer::eField, ELayer::eFieldEnemyWall });
	mpColliderSphere->Position(0.0f, 5.0f, 1.0f);

	// ダメージを受けるコライダー
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.5f
	);
	// ダメージを受けるコライダーと
	// 衝突判定を行うコライダーのレイヤーとタグを設定
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol, ELayer::eDamageCol,ELayer::eEnemy });
	mpDamageCol->SetCollisionTags({ ETag::eWeapon, ETag::eEnemy });
	// ダメージを受けるコライダーを少し下へずらす
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx);

	// ダメージを与えるコライダー
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eKickCol,
		0.3f
	);
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });
	mpAttackCol->SetEnable(false);
	// 右足
	const CMatrix* spineMtxK = GetFrameMtx("Armature_mixamorig_RightToeBase");
	mpAttackCol->SetAttachMtx(spineMtxK);

	// 銃を作成して持たせる
	mpGun = new CGun();
	// 右手
	const CMatrix* gun = GetFrameMtx("Armature_mixamorig_RightHand");
	mpGun->AttachMtx(gun);

	mKickTimeEnd = false;
	mBackStep = false;

	// 最初に1レベルに設定
	ChangeLevel(1);
}

// デストラクタ
CSoldier::~CSoldier()
{
	// 作成したタスクを取り除く
	CStageManager::RemoveTask(this);

	// コライダー関連の破棄
	SAFE_DELETE(mpColliderLine);
	SAFE_DELETE(mpColliderSphere);
	SAFE_DELETE(mpDamageCol);
	SAFE_DELETE(mpAttackCol);
	
	// 銃の破棄
	mpGun->Kill();

	// ソルジャーのカウントを破棄
	CEnemyManager::DecrementSoldierCount();

	// UI周りを破棄
	mpGauge->Kill();
	mpFrame->Kill();
	mpExclamationMark->Kill();
}

// 衝突処理
void CSoldier::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// 乗れるコライダー
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

	// カプセルコライダができるまでのコライダー
	if (self == mpColliderSphere)
	{
		if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust); //+ hit.adjust * hit.weight

			 // 移動方向を反転
			mTargetDir = -mTargetDir;

			// 反転した方向に向けて回転を設定
			CVector current = VectorZ();
			CVector target = mTargetDir;
			CVector forward = CVector::Slerp(current, target, 0.125f);
			Rotation(CQuaternion::LookRotation(forward));

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
		else if (other->Layer() == ELayer::eField)
		{
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eFieldEnemyWall)
		{
			Position(Position() + hit.adjust);
		}
	}

	// ダメージを受けるコライダー
	if (self == mpDamageCol)
	{
		if (other->Layer() == ELayer::eAttackCol)
		{
			if (mState != EState::eKick)
			{
				ChangeState(EState::eHit);
			}
		}

		// 敵と当たるコライダー
		if (other->Layer() == ELayer::eDamageCol)
		{
			(other->Tag() == ETag::eEnemy);
			{
				Position(Position() + hit.adjust);
			}
		}
	}
}

// 状態変更
void CSoldier::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// 被ダメージ処理
void CSoldier::TakeDamage(int damage)
{
	mCharaStatus.hp -= damage;

	// HPが0になったら
	if (mCharaStatus.hp <= 0)
	{
		ChangeState(EState::eDeth);
	}
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

// ソルジャーの方向をランダムに変更する処理
void CSoldier::ChangeDerection()
{
	// ランダムな方向に変更
	// ランダムな角度を求める
	float randomAngle = Math::Rand(0.0f, 1.0f) * 360.0f;
	// 方向の計算を角度に代入
	mTargetDir = CalculateDirection(randomAngle);
}

// フレームとHPゲージの表示の確認をする処理
void CSoldier::UpdateGaugeAndFrame()
{
	if (mDiscovery)
	{
		mpGauge->SetShow(false);
		mpFrame->SetShow(false);
	}
	else
	{
		// HPゲージの座標を更新 (敵の座標の少し上の座標)
		CVector gaugePos = Position() + CVector(0.0f, 45.0f, 0.0f);
		mpGauge->SetWorldPos(gaugePos);
		CVector framePos = Position() + CVector(0.0f, 45.0f, 0.0f);
		mpFrame->SetWorldPos(framePos);
	}
}

// ビックリマークの表示の確認をする処理
void CSoldier::UpdateExclamation()
{
	if (mDiscovery)
	{
		// ビックリマーク画像の座標を更新
		CVector exclamationMardPos = Position() + CVector(0.0f, 45.0f, 0.0f);
		mpExclamationMark->SetWorldPos(exclamationMardPos);
	}
	else
	{
		mpExclamationMark->SetShow(false);
	}
}

// 待機状態遷移する条件
bool CSoldier::ShouldTransitionWander()
{
	float randomValue = Math::Rand(0.0f, 1.0f) * M_PI;
	return randomValue < 0.01f;  // 0.01%の確率で待機に遷移
}

// 徘徊状態に遷移する条件
bool CSoldier::ShouldTransition()
{
	float randomValue = Math::Rand(0.0f, 1.0f) * M_PI;
	return randomValue < 0.1f;  // 0.1%の確率で徘徊状態に遷移
}

// 360度の角度を求めて、x軸とy軸から計算する
CVector CSoldier::CalculateDirection(float angleDegrees)
{
	// 初期角度にランダムなオフセットを追加
	float randomOffset = Math::Rand(0.0f, 1.0f);  // 0から1のランダムな値
	float randomAngle = angleDegrees + 2.0f * M_PI * randomOffset;

	// 角度からラジアンに変換
	float angleRadians = randomAngle * M_PI / 180.0f;

	// ベクトルの計算
	float x = cos(angleRadians);
	float y = 0.0f;					// Y軸方向に移動させる場合は必要に応じて変更
	float z = sin(angleRadians);

	return CVector(x, y, z);
}

// 移動処理
void CSoldier::Move()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	// mMoveSpeedは敵の速度ベクトル、mMoveSpeed.X()がX軸方向の速度
	// 適切な速度を設定し、mMoveSpeedをmTargetDirにスケーリングして移動。
	// 速度を設定
	float moveSpeed = MOVE_AUTOMATIC_SPEED;

	// mTargetDir に速度を掛けて移動ベクトルを得る
	CVector moveVector = mTargetDir * moveSpeed;

	// deltaTime を考慮して移動量を計算
	moveVector *= Time::DeltaTime();

	// 現在の座標を更新
	Position(Position() + moveVector + mMoveSpeed);
}

// アニメーション切り替え
void CSoldier::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// 準備中の状態
void CSoldier::UpdateReady()
{
	// ステップごとに処理を切り替える
	switch (mStateStep)
	{
		// ステップ0 初期化処理
	case 0:
		ChangeAnimation(EAnimType::eIdle);
		// 全ての衝突判定をオフにする
		SetEnableCol(false);
		// プレイヤーの移動速度を0にする
		mMoveSpeed = CVector::zero;
		mCharaStatus.stamina = mCharaMaxStatus.stamina;
		mCharaStatus.hp = mCharaMaxStatus.hp;
		// 次のステップへ
		mStateStep++;
		break;
		// ステップ1 ステージの読み込みから
	case 1:
		// ゲームが開始したら
		if (CGameManager::GameState() == EGameState::eGame)
		{
			mElapsedTime = 0.0f;
			// プレイヤーの衝突判定をオンにする
			SetEnableCol(true);
			// 現在の状態を待機に切り替え
			mCharaStatus.hp = mCharaMaxStatus.hp;
			ChangeState(EState::eIdle);
		}
		break;
	}
}

// 待機
void CSoldier::UpdateIdle()
{
	mDiscovery = false;
	mDiscoveryEnd = false;
	mpAttackCol->SetEnable(false);
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	//プレイヤーを見つけたら、敵発見状態へ移行
	if (IsFoundPlayer())
	{
		if (mDiscoveryTimeEnd <= DISCOVERY_END && !mDiscovery)
		{
			ChangeState(EState::eDiscovery);
		}
		else
		{
			ChangeState(EState::eChase);
		}
	}
	else
	{
		ChangeAnimation(EAnimType::eIdle);

		// 確率で徘徊状態に移行
		if (ShouldTransition())
		{
			ChangeState(EState::eWander);
		}
	}
}

// 攻撃
void CSoldier::UpdateAttack()
{
	mDiscovery = false;
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
		if (distancePlayer <= BACKSTEP_RANGE && !mBackStep)
		{
			ChangeState(EState::eBackStep);
			mBackStep = true;
			return;
		}
		else if (distancePlayer <= ATTACK_RANGE_KICK && !mKickTimeEnd)
		{
			ChangeState(EState::eKick);
			mKickTimeEnd = true;
			return;
		}
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

			// 弾丸を生成
			new CBullet
			(
				// 発射位置
				Position() + CVector(0.0f, 13.0f, 0.0f) + VectorZ() * 20.0f,
				VectorZ(),	// 発射方向
				1000.0f,	// 移動距離
				1000.0f		// 飛距離
			);

			// 全弾発射したら、攻撃終了
			mTimeShot++;
			if (mTimeShot >= mTimeShotEnd)
			{
				// 攻撃終了後の待機状態に遷移
				ChangeState(EState::eAttackWait);
				mTimeShot = 0;
				mElapsedTime = 0.0f;
				mDiscoveryTime = 0.0f;
			}
		}
	}
	else
	{
		ChangeState(EState::eChase);
		mElapsedTime_End = 0.0f;
		mDiscoveryTime = 0.0f;
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
			ChangeState(EState::eAttack);
		}
		else
		{
			ChangeState(EState::eAimDwon);
			mElapsedTime_End = 0.0f;
			mDiscoveryTime = 0.0f;
		}
	}
}

// プレイヤー発見
void CSoldier::UpdateDiscovery()
{
	mDiscovery = true;
	mMoveSpeed.Y(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eRifleIdle);

	// プレイヤーまでのベクトルを求める
	CPlayer* player = CPlayer::Instance();
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();
	
	mDiscoveryTime += Time::DeltaTime();
	if (mDiscoveryTime >= DISCOVERY)
	{
		if (IsFoundPlayer())
		{
			mDiscoveryEnd = true;
			ChangeState(EState::eChase);
		}
		else
		{
			mDiscoveryTime = 0.0f;
			ChangeState(EState::eAimDwon);
		}
	}
	//CDebugPrint::Print("discovery:%f\n", mDiscoveryTime);
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
		//CDebugPrint::Print("TimeEnd%f\n", mElapsedTime_End);
		if (mElapsedTime_End >= PLAYER_LOST)
		{
			ChangeState(EState::eAimDwon);
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
			ChangeState(EState::eAttack);
		}
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
	if (mAnimationFrame >= 45.0f)
	{
		mpAttackCol->SetEnable(true);
		ChangeState(EState::eKickWait);
	}
}

// キック終了
void CSoldier::UpdateKickWait()
{
	if (mAnimationFrame >= 70.0f)
	{
		mpAttackCol->SetEnable(false);
		if (IsAnimationFinished())
		{
			ChangeState(EState::eChase);
			ChangeAnimation(EAnimType::eIdle);
		}
		
	}
}

// エイム解除
void CSoldier::UpdateAimDwon()
{
	ChangeAnimation(EAnimType::eAimDwou);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
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
		// プレイヤーのポインタが0以外の時
		CPlayer* player = CPlayer::Instance();

		// プレイヤーまでのベクトルを求める
		CVector vp = player->Position() - Position();
		float distancePlayer = vp.Length();
		vp.Y(0.0f);
		mTargetDir = vp.Normalized();

		if (mCharaStatus.hp >= 1)
		{
			ChangeState(EState::eChase);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeth);
		}
	}
}

// 死亡
void CSoldier::UpdateDeth()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eDeth);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eDethEnd);
	}
}

// 死亡処理終了
void CSoldier::UpdateDethEnd()
{
	if (IsAnimationFinished())
	{
		Kill();
	}
}

// 徘徊処理
void CSoldier::UpdateWander()
{
	mpAttackCol->SetEnable(false);
	ChangeAnimation(EAnimType::eWalk);

	// 一定時間ごとに方向転換
	mElapsedTime += Time::DeltaTime();
	if (mElapsedTime >= mTimeToChange)
	{
		ChangeDerection();
		mElapsedTime = 0.0f;
	}

	Move();

	if (IsFoundPlayer())
	{
		if (mDiscoveryTimeEnd <= DISCOVERY_END)
		{
			ChangeState(EState::eDiscovery);
		}
		else
		{
			ChangeState(EState::eChase);
		}
	}
	else
	{
		if (ShouldTransitionWander())
		{
			ChangeState(EState::eIdle);
		}
	}
}

// バックステップ
void CSoldier::UpdateBackStep()
{
	mMoveSpeed.X(0.0f);

	ChangeAnimation(EAnimType::eBackStep);

	// プレイヤーのポインタが0以外の時
	CPlayer* player = CPlayer::Instance();

	// プレイヤーまでのベクトルを求める
	CVector vp = player->Position() - Position();
	float distancePlayer = vp.Length();
	vp.Y(0.0f);
	mTargetDir = vp.Normalized();


	// バックステップする距離
	const float backStepDistance = 15.0f;

	CVector playerPos = CPlayer::Instance()->Position();
	CVector soldierPos = Position();
	CVector toPlayer = (playerPos - soldierPos).Normalized();

	Position(Position() - toPlayer * backStepDistance * Time::DeltaTime());
	if (IsAnimationFinished())
	{
		ChangeState(EState::eChase);
	}
}

// ジャンプ開始
void CSoldier::UpdateJumpStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eJump);

	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
	mIsGrounded = false;
}

// ジャンプ中
void CSoldier::UpdateJump()
{
	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		ChangeState(EState::eJumpEnd);
	}
}

// ジャンプ終了
void CSoldier::UpdateJumpEnd()
{
	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
	}
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

// 更新
void CSoldier::Update()
{
	SetParent(mpRideObject);
	mpRideObject = nullptr;

	// キックの待ち時間
	if (mKickTimeEnd)
	{
		mKickTime += Time::DeltaTime();
		if (mKickTime >= KICKCOL)
		{
			mKickTimeEnd = false;
			mKickTime = 0.0f;
		}
	}
	//CDebugPrint::Print("kickTime%f\n", mKickTime);

	// バックステップの待ち時間
	if (mBackStep)
	{
		mBackStepTime += Time::DeltaTime();
		if (mBackStepTime >= BACKSTEP_WEIT_TIME)
		{
			mBackStep = false;
			mBackStepTime = 0.0f;
		}
	}

	// プレイヤーを発見した後の時間の計測
	if (mDiscoveryTimeEnd <= DISCOVERY_END && mDiscoveryEnd)
	{
		mDiscoveryTimeEnd += Time::DeltaTime();
		if (mDiscoveryTimeEnd >= DISCOVERY_END)
		{
			mDiscovery = false;
			mDiscoveryEnd = false;
			mDiscoveryTimeEnd = 0.0f;
		}
	}
	CDebugPrint::Print("mDiscovery:%s\n", mDiscovery ? "true" : "false");
	//CDebugPrint::Print("discoveryTimeEnd:%f\n", mDiscoveryTimeEnd);

	// 状態に合わせて、更新処理を切り替える
	switch (mState)
	{
		// 準備状態
	case EState::eReady:
		UpdateReady();
		break;
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
		// プレイヤー発見
	case EState::eDiscovery:
		UpdateDiscovery();
		break;
		// 追跡状態
	case EState::eChase:
		UpdateChase();
		break;
		// プレイヤーの攻撃Hit
	case EState::eHit:
		UpdateHit();
		break;
		// 死亡
	case EState::eDeth:
		UpdateDeth();
		break;
		// 死亡処理終了
	case EState::eDethEnd:
		UpdateDethEnd();
		break;
		// 徘徊処理
	case EState::eWander:
		UpdateWander();
		break;
		// バックステップ
	case EState::eBackStep:
		UpdateBackStep();
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

	if (mState != EState::eReady)
	{
		mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

		// 移動
		Position(Position() + mMoveSpeed * 60.0f * Time::DeltaTime());

		CVector PlayerPosition;

		// CSoldierを移動方向へ向ける
		CVector current = VectorZ();
		CVector target = mTargetDir;
		CVector forward = CVector::Slerp(current, target, 0.125f);
		Rotation(CQuaternion::LookRotation(forward));
	}

	//// CSoldierのデバッグ表示
	//static bool debug = false;
	//if (CInput::PushKey('F'))
	//{
	//	debug = !debug;
	//}
	//if (debug)
	//{
	//	//CDebugPrint::Print(" レベル %d\n", mCharaMaxStatus.level);
	//	CDebugPrint::Print(" HP%d / %d\n", mCharaStatus.hp, mCharaMaxStatus.hp);
	//	CDebugPrint::Print(" 攻撃値%d\n", mCharaStatus.power);
	//	CDebugPrint::Print(" ST%d / %d\n", mCharaStatus.stamina, mCharaMaxStatus.stamina);
	//}
	//// 1キーを押しながら、↑ ↓ でHP増減
	//if (CInput::Key('3'))
	//{
	//	if (CInput::PushKey(VK_UP)) mCharaStatus.hp++;
	//	else if (CInput::PushKey(VK_DOWN)) mCharaStatus.hp--;
	//}
	//else if (CInput::Key('2'))
	//{
	//	LevelUp();
	//}

	// フレームとゲージの表示処理
	UpdateGaugeAndFrame();
	// ビックリマークの表示処理
	UpdateExclamation();

	// 現在のHpを設定
	mpGauge->SetValue(mCharaStatus.hp);


	// CSoldierの更新
	CXCharacter::Update();
	mpDamageCol->Update();
	mpAttackCol->Update();
	mpGun->UpdateAttachMtx();

	mIsGrounded = false;

	//// 弾の開始値を監視
	//CDebugPrint::Print("Shot%d\n", mTimeShot);
	//// 弾の終了値を監視
	//CDebugPrint::Print("Shotend%d\n", mTimeShotEnd);
	//// 前フレームのFPSを監視
	//CDebugPrint::Print("FPS:%f\n", Time::FPS());
	
}

// 描画
void CSoldier::Render()
{
	CXCharacter::Render();
}