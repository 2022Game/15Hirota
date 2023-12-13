//プレイヤークラスのインクルード
#include "CPlayer.h"
#include "CInput.h"
#include "CCamera.h"
#include "CUiGauge.h"
#include "CStaminaGauge.h"
#include "Maths.h"
#include "CSceneManager.h"
#include "CMajicSword.h"
#include "CBullet.h"

//// プレイヤーのモデルデータのパス
//#define MODEL_PATH "Character\\Monster1\\Monster_1.x"

// プレイヤー関連
#define PLAYER_HEIGHT 16.0f		// 高さ
#define MOVE_SPEED 0.9f			// スピード
#define RUN_SPEED 1.3f			// 移動スピード
#define JUMP_SPEED 1.5f			// ジャンプ
#define GRAVITY 0.0625f			// 重力
#define JUMP_END_Y 1.0f			// ジャンプ終了時

#define FOV_ANGLE 45.0f			//視野の角度(ー角度+角度も出)
#define FOV_LENGTH 5.0f			//視野の角度

// HP関連
#define HP 100

// レベル関連
#define LEVEL 1

// スタミナ関連
#define STAMINA 109

// プレイヤーのインスタンス
CPlayer* CPlayer::spInstance = nullptr;


// プレイヤーのアニメーションデータのテーブル
const CPlayer::AnimData CPlayer::ANIM_DATA[] =
{
	{ "",														true,	0.0f	},	// Tポーズ
	{ "Character\\Monster1\\anim\\Warrok_Idle.x",				true,	854.0f	},	// 待機
	{ "Character\\Monster1\\anim\\Warrok_Walking.x",			true,	86.0f	},	// ダッシュ
	{ "Character\\Monster1\\anim\\Warrok_Punchi.x",				false,	67.0f	},	// 攻撃
	{ "Character\\Monster1\\anim\\Warrok_StrongAttack.x",		false,	161.0f	},	// 強攻撃
	{ "Character\\Monster1\\anim\\jump_start.x",				false,	25.0f	},	// ジャンプ開始
	{ "Character\\Monster1\\anim\\jump.x",						true,	1.0f	},	// ジャンプ中
	{ "Character\\Monster1\\anim\\jump_end.x",					false,	26.0f	},	// ジャンプ終了
	{ "Character\\Monster1\\anim\\Warrok_Run.x",				true,	53.0f	},	// 歩行
	{ "Character\\Monster1\\anim\\Warrok_RunStop.x",			false,	90.0f	},	// ダッシュ終了
	{ "Character\\Monster1\\anim\\Rotate.x",					false,	71.0f	},	// 回避
	{ "Character\\Monster1\\anim\\Guts pose_325.x",				false,	325.0f	},	// ガッツポーズ
	{ "Character\\Monster1\\anim\\Deth_276.x",					false,	276.0f	},	// 死亡

};

// コンストラクタ
CPlayer::CPlayer()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eIdle)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mPosition(0.0f,0.0f,0.0f)//0.0f, 60.0f, -30.0f
	, mpRideObject(nullptr)
	, staminaDepleted(false)
	, staminaLowerLimit(false)
	, damageObject(false)
	, mLife(50)
{
	SetColor(CColor(1.0, 0.0, 0.0, 1.0));
	// HPゲージを作成
	mpHpGauge = new CUIGauge();
	// スタミナゲージを作成
	mpStaminaGauge = new CStaminaGauge();

	// インスタンスの設定
	spInstance = this;

	// モデルデータ取得
	CModelX* model = CResourceManager::Get<CModelX>("Player");

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

	// 縦のコライダーライン
	mpColliderLine = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, PLAYER_HEIGHT, 0.0f)
	);
	/*const CMatrix* speneMtxL = GetFrameMtx("Armature_mixamorig_Spine1");
	mpColliderLine->SetAttachMtx(speneMtxL);*/
	mpColliderLine->SetCollisionLayers({ ELayer::eField,ELayer::eDamageObject });


	// 前後のコライダーライン
	mpColliderLine_2 = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 8.0f, -8.0f),
		CVector(0.0f, 8.0f, 8.0f)
	);
	mpColliderLine_2->SetCollisionLayers({ ELayer::eFieldWall });


	// 横のコライダーライン
	mpColliderLine_3 = new CColliderLine
	(
		this, ELayer::eField,
		CVector(8.0f, 8.0f, 0.0f),
		CVector(-8.0f, 8.0f, 0.0f)
	);
	mpColliderLine_3->SetCollisionLayers({ ELayer::eFieldWall });


	// ダメージを受けるコライダーを作成
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.5f//0.5f
	);
	// ダメージを受けるコライダーと
	// 衝突判定を行うコライダーのレイヤーとタグを設定
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol,ELayer::eGoalCol });
	mpDamageCol->SetCollisionTags({ ETag::eEnemyWeapon,ETag::eGoalObject });
	// ダメージを受けるコライダーを少し上へずらす
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx);


	mpSword = new CMajicSword();
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHand"));
	mpSword->SetOwner(this);

	// 最初に1レベルに設定
	ChangeLevel(1);
}

CPlayer::~CPlayer()
{
	if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}

	if (mpColliderLine_2 != nullptr)
	{
		delete mpColliderLine_2;
		mpColliderLine_2 = nullptr;
	}

	if (mpColliderLine_3 != nullptr)
	{
		delete mpColliderLine_3;
		mpColliderLine_3 = nullptr;
	}

	if (mpDamageCol != nullptr)
	{
		delete mpDamageCol;
		mpDamageCol = nullptr;
	}
}

CPlayer* CPlayer::Instance()
{
	return spInstance;
}

// hp取得
int CPlayer::GetHp()
{
	return mCharaStatus.hp;
}

// 最大hp取得
int CPlayer::GetMaxHp()
{
	return mCharaMaxStatus.hp;
}

// レベルアップ
void CPlayer::LevelUp()
{
	int level = mCharaStatus.level;
	ChangeLevel(level + 1);
}

// レベルを変更
void CPlayer::ChangeLevel(int level)
{
	// ステータスのテーブルのインデックス値に変換
	int index = Math::Clamp(level - 1, 0, PLAYER_LEVEL_MAX);
	// 最大ステータスに設定
	mCharaMaxStatus = PLAYER_STATUS[index];
	// 現在のステータスを最大値にすることで、HPも回復
	mCharaStatus = mCharaMaxStatus;

	// 最大HPと現在HPをHPゲージに反映
	mpHpGauge->SetMaxValue(mCharaMaxStatus.hp);
	mpHpGauge->SetValue(mCharaStatus.hp);

	// 最大スタミナと現在スタミナをスタミナゲージに反映
	mpStaminaGauge->SetSutaminaMaxValue(mCharaMaxStatus.stamina);
	mpStaminaGauge->SetSutaminaValue(mCharaStatus.stamina);
}

// アニメーション切り替え
void CPlayer::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// 待機
void CPlayer::UpdateIdle()
{
	mpDamageCol->SetEnable(true);
	bool KeyPush = (CInput::Key('W') || CInput::Key('A') || CInput::Key('S') || CInput::Key('D'));

	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	
	if (mIsGrounded)
	{
		// 移動処理
		// キーの入力ベクトルを取得
		CVector input;
		if (CInput::Key('W'))		input.Z(-1.0f);
		else if (CInput::Key('S'))	input.Z(1.0f);
		if (CInput::Key('A'))		input.X(-1.0f);
		else if (CInput::Key('D'))	input.X(1.0f);

		// 入力ベクトルの長さで入力されているか判定
		if (input.LengthSqr() > 0.0f)
		{
			// カメラの向きに合わせた移動ベクトルに変換
			CVector move = CCamera::MainCamera()->Rotation() * input;
			move.Y(0.0f);
			move.Normalize();

			float speed = MOVE_SPEED;
			if (CInput::Key(VK_SHIFT) && KeyPush)
			{
				if ((mCharaStatus.stamina > 0 && !staminaLowerLimit))
				{
					// 速度を走行速度に変更
					speed = RUN_SPEED;
					mCharaStatus.stamina -= 1;
					ChangeAnimation(EAnimType::eDash);

					if (mCharaStatus.stamina == 0)
					{
						staminaLowerLimit = true;
						mState = EState::eDashEnd;
					}
				}
				else
				{
					if (staminaLowerLimit && mCharaStatus.stamina == mCharaMaxStatus.stamina)
					{
						staminaLowerLimit = false; // スタミナが再びMAXになったらリセット
					}
					mCharaStatus.stamina += 1;
					ChangeAnimation(EAnimType::eWalk);
				}
			}
			else
			{
				if (mCharaStatus.stamina < mCharaMaxStatus.stamina && !staminaDepleted)
				{
					mCharaStatus.stamina += 1;
				}
				else if (mCharaStatus.stamina >= mCharaMaxStatus.stamina)
				{
					staminaDepleted = false;  // スタミナが上限値より上になったらリセット
				}

				ChangeAnimation(EAnimType::eWalk);
			}
			mMoveSpeed += move * speed * MOVE_SPEED * mCharaStatus.moveSpeed;
		}
		// 移動キーを入力していない
		else
		{
			// 待機アニメーションに切り替え
			ChangeAnimation(EAnimType::eIdle);
			if (mCharaStatus.stamina < mCharaMaxStatus.stamina && !staminaDepleted)
			{
				mCharaStatus.stamina += 1;
			}
			else if (mCharaStatus.stamina >= mCharaMaxStatus.stamina)
			{
				staminaDepleted = false;  //  スタミナが上限値より上になったらリセット
			}
		}

		// Jキーで攻撃状態へ移行
		if (CInput::PushKey('J'))
		{
			mMoveSpeed.X(0.0f);
			mMoveSpeed.Z(0.0f);
			mState = EState::eAttack;
		}
		// Kキーで強攻撃
		else if (CInput::PushKey('K'))
		{
			mMoveSpeed.X(0.0f);
			mMoveSpeed.Z(0.0f);
			mState = EState::eAttackStrong;
		}
		// SPACEキーでジャンプ開始へ移行
		else if (CInput::PushKey(VK_SPACE))
		{
			if (mCharaStatus.stamina - 20 >= 0)
			{
				mState = EState::eJumpStart;
				// スタミナが0以下にならない場合はジャンプを実行
				mCharaStatus.stamina -= 20;
			}
			else
			{
			}
		}
		// Q,Eキーで回避へ移行
		else if (((CInput::PushKey('Q') || CInput::PushKey('E')) && KeyPush) && (mCharaStatus.stamina <= mCharaMaxStatus.stamina))
		{
			// 回避行動前にスタミナが0以下になるかどうかを確認
			if (mCharaStatus.stamina - 50 >= 0) {

				mState = EState::eRotate;
				// スタミナが0以下にならない場合は回避行動を実行
				mCharaStatus.stamina -= 50;
			}
			else 
			{
			}
		}
	}
	else
	{
		if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
		{
			mCharaStatus.stamina += 1;
		}

		// 待機アニメーションに切り替え
		ChangeAnimation(EAnimType::eIdle);
	}
}

// 攻撃
void CPlayer::UpdateAttack()
{
	// 剣に攻撃開始を伝える
	mpSword->AttackStart();
	// 攻撃アニメーションを開始
	ChangeAnimation(EAnimType::eAttack);
	// 攻撃終了待ち状態へ移行
	mState = EState::eAttackWait;
}

// 強攻撃
void CPlayer::UpdateAttackStrong()
{
	// 強攻撃アニメーションを開始
	ChangeAnimation(EAnimType::eAttackStrong);
	// 攻撃終了待ち状態へ移行
	mState = EState::eAttackWait2;
}

// 攻撃終了待ち
void CPlayer::UpdateAttackWait()
{
	// 攻撃アニメーションが終了したら、
	if (IsAnimationFinished())
	{
		// 待機状態へ移行
		mState = EState::eIdle;
		ChangeAnimation(EAnimType::eIdle);

		// 剣に攻撃終了を伝える
		mpSword->AttackEnd();
	}
}

// 攻撃終了待ち2
void CPlayer::UpdateAttackWait2()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
		ChangeAnimation(EAnimType::eIdle);
	}
}

// ジャンプ開始
void CPlayer::UpdateJumpStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	mState = EState::eJump;

	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
	mIsGrounded = false;
}

// ジャンプ中
void CPlayer::UpdateJump()
{
	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		mState = EState::eJumpEnd;
	}
}

// ジャンプ終了
void CPlayer::UpdateJumpEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
	}
}

//回避開始
void CPlayer::UpdateRotate()
{
	ChangeAnimation(EAnimType::eRotate);
	mState = EState::eRotateEnd;
}

//回避終了待ち
void CPlayer::UpdateRotateEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
		ChangeAnimation(EAnimType::eIdle);
	}
}

// ダッシュ終了
void CPlayer::UpdateDashEnd()
{
	mMoveSpeed.Z(0.0f);
	mMoveSpeed.X(0.0f);
	ChangeAnimation(EAnimType::eDashStop);
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
		ChangeAnimation(EAnimType::eIdle);
	}
}

// クリア
void CPlayer::UpdateClear()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eGuts);
	mState = EState::eClearEnd;
}

// クリア終了
void CPlayer::UpdateClearEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
		Position(0.0f,0.0f,-30.0f);
	}
}

// 死亡
void CPlayer::UpdateDeth()
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
void CPlayer::UpdateDethEnd()
{
	if (IsAnimationFinished())
	{
		mCharaStatus = mCharaMaxStatus;
		Position(0.0f, 0.0f, -30.0f);
		mState = EState::eIdle;
	}
}

// 再起
void CPlayer::UpdateReStart()
{
	if (IsAnimationFinished())
	{
		damageObject = false;
		Position(0.0f, 10.0f, -30.0f);
		mState = EState::eIdle;
	}
}

// 更新
void CPlayer::Update()
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
		// 強攻撃
		case EState::eAttackStrong:
			UpdateAttackStrong();
			break;
		// 攻撃終了待ち
		case EState::eAttackWait:
			UpdateAttackWait();
			break;
		// 攻撃終了待ち2
		case EState::eAttackWait2:
			UpdateAttackWait2();
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
		// 回避開始
		case EState::eRotate:
			UpdateRotate();
			break;
		// 回避終了
		case EState::eRotateEnd:
			UpdateRotateEnd();
			break;
		// ダッシュ終了
		case EState::eDashEnd:
			UpdateDashEnd();
			break;
		// クリア
		case EState::eClear:
			UpdateClear();
			break;
		// クリア終了
		case EState::eClearEnd:
			UpdateClearEnd();
			break;
		// 死亡
		case EState::eDeth:
			UpdateDeth();
			break;
		// 死亡処理終了
		case EState::eDethEnd:
			UpdateDethEnd();
			break;
		// 再起
		case EState::eReStart:
			UpdateReStart();
			break;
	}

	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	// 移動
	Position(Position() + mMoveSpeed * 60.0f * Time::DeltaTime());

	// プレイヤーを移動方向へ向ける
	CVector current = VectorZ();
	CVector target = mMoveSpeed;
	target.Y(0.0f);
	target.Normalize();
	CVector forward = CVector::Slerp(current, target, 0.125f);
	Rotation(CQuaternion::LookRotation(forward));

	// 無敵中はカウントを減少させる
	if (mInvincible > 0)
	{
		// 減算
		mInvincible--;
	}

	// キャラクターのデバッグ表示
	static bool debug = false;
	if (CInput::PushKey('R'))
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
	if (CInput::Key('1'))
	{
		if (CInput::PushKey(VK_UP)) mCharaStatus.hp++;
		else if (CInput::PushKey(VK_DOWN)) mCharaStatus.hp--;
	}
	else if (CInput::Key('2'))
	{
		LevelUp();
	}
	// 現在のHPを設定
	mpHpGauge->SetValue(mCharaStatus.hp);
	// 現在のスタミナを設定
	mpStaminaGauge->SetSutaminaValue(mCharaStatus.stamina);

	// キャラクターの更新
	CXCharacter::Update();
	mpDamageCol->Update();

	mIsGrounded = false;
}

// 衝突処理
void CPlayer::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
		else if (other->Layer() == ELayer::eDamageObject)
		{
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
			mIsGrounded = true;

			if (other->Tag() == ETag::eRideableObject)
			{
				if (!damageObject)
				{
					mCharaStatus.hp -= 1;
					damageObject = true;
				}
				ChangeAnimation(EAnimType::eDeth);
				mpRideObject = other->Owner();
				mState = EState::eReStart;
			}
		}
	}

	if (self == mpColliderLine_2)
	{
		if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust); //+ hit.adjust * hit.weight

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
	}

	if (self == mpColliderLine_3)
	{
		if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust); //+ hit.adjust * hit.weight

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
	}

	if (self == mpDamageCol)
	{
		if (other->Layer() == ELayer::eGoalCol)
		{
			CDebugPrint::Print("Player hit GoalObject!\n");
			mpDamageCol->SetEnable(false);
			mState = EState::eClear;
		}
	}
}

// 被ダメージ処理
void CPlayer::TakeDamage(int damage)
{
	//// 死亡していたら、ダメージは受けない
	//if (mCharaStatus.hp <= 0)return;

	//// HPからダメージを引く
	//mCharaStatus.hp = max(mCharaStatus.hp - damage, 0);
	//mCharaStatus.hp -= damage;
	// HPが0になったら
	if (mCharaStatus.hp <= 0)
	{
		mState = EState::eDeth;
	}
}

// 描画
void CPlayer::Render()
{
	// キャラ描画
	CXCharacter::Render();
}