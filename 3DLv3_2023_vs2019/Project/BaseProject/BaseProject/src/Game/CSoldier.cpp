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

#define _USE_MATH_DEFINES

// CSoldierのインスタンス
CSoldier* CSoldier::spInstance = nullptr;

int CSoldier::enemyCount = 0;


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
	{ "Character\\Gas mask soldier\\anim\\Death_Fall down1_157.x",					false,	157.0f	},		// 死亡

};


#define ENEMY_HEIGHT 8.0f
#define ENEMY_HEIGHT2 20.0f
#define MOVE_SPEED 0.5f
#define RUN_SPEED 25.0f
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
#define SHOT_INTERVAL 2.0f

// 敵を見失った後の時間
#define PLAYER_LOST 10.0f


// コンストラクタ
CSoldier::CSoldier()
	: CXCharacter(ETag::eEnemy, ETaskPriority::eEnemy)
	, mState(EState::eIdle)
	, mTargetDir(0.0f, 0.0f, 1.0f)
	, mMoveSpeed(0.0f,0.0f,0.0f)
	, mpRideObject(nullptr)
	, mTimeShot(0)
	, mTimeShotEnd(5)
	, mElapsedTime(0.0f)
	, mElapsedTime_End(0.0f)
	, mTimeToChange(Math::Rand(2.0f,5.0f))
	, wanderRadius(0.0f)
	, initialPosition(0.0f,0.0f,0.0f)
{
	Position(initialPosition);

	enemyCount++;
	//インスタンスの設定
	spInstance = this;

	// モデルデータ取得
	CModelX* model = CResourceManager::Get<CModelX>("Soldier");


	mpFrame = new CSoldierFrame();
	// 0~1の値を設定
	mpFrame->SetCenterRatio(CVector2(0.5f, 0.0f));
	mpGauge = new CSoldierGauge();
	mpGauge->SetCenterRatio(CVector2(0.3f, 0.0f));

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

	
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eEnemy,
		7.0f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::eFieldWall ,ELayer::eField });
	mpColliderSphere->Position(0.0f, 5.0f, 1.0f);


	// ダメージを受けるコライダーを作成
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.5f //後で変更
	);
	// ダメージを受けるコライダーと
	// 衝突判定を行うコライダーのレイヤーとタグを設定
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol, ELayer::eDamageCol,ELayer::eEnemy });
	mpDamageCol->SetCollisionTags({ ETag::eWeapon, ETag::eEnemy });
	// ダメージを受けるコライダーを少し下へずらす
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx);


	// 右足にダメージコライダーを設定
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eKickCol,
		0.3f
	);
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });
	mpAttackCol->SetEnable(false);
	const CMatrix* spineMtxK = GetFrameMtx("Armature_mixamorig_RightToeBase");
	mpAttackCol->SetAttachMtx(spineMtxK);


	// 銃を作成して持たせる
	mpGun = new CGun();
	const CMatrix* gun = GetFrameMtx("Armature_mixamorig_RightHand");
	mpGun->AttachMtx(gun);


	// 最初に1レベルに設定
	ChangeLevel(1);
}


CSoldier::~CSoldier()
{
	CStageManager::RemoveTask(this);

	if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}

	if (mpColliderSphere != nullptr)
	{
		delete mpColliderSphere;
		mpColliderSphere = nullptr;
	}

	// ダメージを受けるコライダーを削除
	if (mpDamageCol != nullptr)
	{
		delete mpDamageCol;
		mpDamageCol = nullptr;
	}

	if (mpAttackCol != nullptr)
	{
		delete mpAttackCol;
		mpAttackCol = nullptr;
	}

	mpGun->Kill();

	enemyCount--;

	// UI周りを消す
	mpGauge->Kill();
	mpFrame->Kill();
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
	mpAttackCol->SetEnable(false);
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

		// 確率で徘徊状態に移行
		if (ShouldTransition())
		{
			mState = EState::eWander;
		}
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

			// 弾丸を生成
			new CBullet
			(
				// 発射位置
				Position() + CVector(0.0f, 10.0f, 0.0f) + VectorZ() * 20.0f,
				VectorZ(),	// 発射方向
				1000.0f,	// 移動距離
				1000.0f		// 飛距離
			);

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
	if (mAnimationFrame >= 45.0f)
	{
		mpAttackCol->SetEnable(true);
		mState = EState::eKickWait;
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
			mState = EState::eChase;
			ChangeAnimation(EAnimType::eIdle);
		}
		
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
		// プレイヤーのポインタが0以外の時
		CPlayer* player = CPlayer::Instance();

		// プレイヤーまでのベクトルを求める
		CVector vp = player->Position() - Position();
		float distancePlayer = vp.Length();
		vp.Y(0.0f);
		mTargetDir = vp.Normalized();

		if (mCharaStatus.hp > 1)
		{
			mState = EState::eChase;
		}
		else if (mCharaStatus.hp <= 0)
		{
			mpDamageCol->SetEnable(false);
			mState = EState::eDeth;
		}
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

// 死亡
void CSoldier::UpdateDeth()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eDeth);
	if (IsAnimationFinished())
	{
		mState = EState::eDethEnd;
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
		mState = EState::eChase;
	}
	else
	{
		if (ShouldTransitionWander())
		{
			mState = EState::eIdle;
		}
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
	CDebugPrint::Print("FPS:%f\n", Time::FPS());
	

	// HPゲージの座標を更新 (敵の座標の少し上の座標)
	CVector gaugePos = Position() + CVector(0.0f, 25.0f, 0.0f);
	mpGauge->SetWorldPos(gaugePos);
	CVector framePos = Position() + CVector(0.0f, 25.0f, 0.0f);
	mpFrame->SetWorldPos(framePos);


	// 現在のHpを設定
	mpGauge->SetValue(mCharaStatus.hp);

	// CSoldierの更新
	CXCharacter::Update();
	mpDamageCol->Update();
	mpAttackCol->Update();
	mpGun->UpdateAttachMtx();

	mIsGrounded = false;
	
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

	if (self == mpColliderSphere)
	{
		if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust); //+ hit.adjust * hit.weight

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
		if (other->Layer() == ELayer::eField)
		{
			Position(Position() + hit.adjust);
		}
	}

	if (self == mpDamageCol)
	{
		if (other->Layer() == ELayer::eAttackCol)
		{
			if (mState != EState::eKick)
			{
				mState = EState::eHit;
			}
		}

		if (other->Layer() == ELayer::eDamageCol)
		{
			(other->Tag() == ETag::eEnemy);
			{
				Position(Position() + hit.adjust);
			}
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
		mState = EState::eDeth;
	}
}

int CSoldier::GetEnemyCount()
{
	return enemyCount;
}


// 徘徊に遷移する条件
bool CSoldier::ShouldTransitionWander()
{
	float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return randomValue < 0.01f;  // 1%の確率で徘徊に遷移
}

bool CSoldier::ShouldTransition()
{
	float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return randomValue < 0.01f;  // 0.1%の確率で徘徊に遷移
}


// 1%の確率で移行する為の処理
void CSoldier::ChangeDerection()
{
	// ランダムな方向に変更
	float randomAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 360.0f;
	mTargetDir = CalculateDirection(randomAngle);
}


// 360度の角度を求めて、x軸とy軸から計算する
CVector CSoldier::CalculateDirection(float angleDegrees)
{
	// 角度からラジアンに変換
	float angleRadians = angleDegrees * M_PI / 180.0f;

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
	// mMoveSpeed は敵の速度ベクトルでmMoveSpeed.X() が X 軸方向の速度を表します。
	// 適切な速度を設定し、mMoveSpeedをmTargetDirにスケーリングして移動。

	// 速度を設定
	float moveSpeed = RUN_SPEED;

	// mTargetDir に速度を掛けて移動ベクトルを得る
	CVector moveVector = mTargetDir * moveSpeed;

	// deltaTime を考慮して移動量を計算
	moveVector *= Time::DeltaTime();

	// 現在の座標を更新
	Position(Position() + moveVector + mMoveSpeed);
}
