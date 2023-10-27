//プレイヤークラスのインクルード
#include "CPlayer.h"
#include "CInput.h"
#include "CCamera.h"

// プレイヤーのモデルデータのパス
#define MODEL_PATH "Character\\Monster1\\Monster_1.x"

// プレイヤー関連
#define PLAYER_HEIGHT 16.0f		// 高さ
#define MOVE_SPEED 1.0f			// スピード
#define JUMP_SPEED 1.5f			// ジャンプ
#define GRAVITY 0.0625f			// 重力
#define JUMP_END_Y 1.0f			// ジャンプ終了時

// 画像関連
#define GAUGE_HEIGHT 30.0f		// 高さ
#define GAUGE_WIDTH 800.0f		// 幅
#define GAUGE_X_POS 200.0f		// 横軸
#define GAUGE_Y_POS 100.0f		// 縦軸

// プレイヤーのインスタンス
CPlayer* CPlayer::spInstance = nullptr;


// プレイヤーのアニメーションデータのテーブル
const CPlayer::AnimData CPlayer::ANIM_DATA[] =
{
	{ "",												true,	0.0f	},	// Tポーズ
	{ "Character\\Player\\anim\\idle.x",				true,	153.0f	},	// 待機
	{ "Character\\Player\\anim\\walk.x",				true,	66.0f	},	// 歩行
	{ "Character\\Player\\anim\\attack.x",				false,	91.0f	},	// 攻撃
	{ "Character\\Player\\anim\\Attack_Strong.x",		false,	161.0f	},	// 強攻撃
	{ "Character\\Player\\anim\\jump_start.x",			false,	25.0f	},	// ジャンプ開始
	{ "Character\\Player\\anim\\jump.x",				true,	1.0f	},	// ジャンプ中
	{ "Character\\Player\\anim\\jump_end.x",			false,	26.0f	},	// ジャンプ終了
	{ "Character\\Player\\anim\\Dash.x",				true,	23.0f	},	// ダッシュ
	{ "Character\\Player\\anim\\Dash_Stop.x",			false,	27.0f	},	// ダッシュ終了
	{ "Character\\Player\\anim\\Rotate.x",				false,	71.0f	},	// 回避
};

// コンストラクタ
CPlayer::CPlayer()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eIdle)
	, mpRideObject(nullptr)
	, mGauguSitaji(nullptr)
	, mGaugu(nullptr)
	, mRemainTime(50)
	, mInvincible(0)
	, mHP(4000)
	, mMaxHP(4000)
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

	// 画像読み込み
	mGauguSitaji = new CImage("UI\\Image_Gauge_Frame.png");
	mGaugu = new CImage("UI\\Gauge.png");
}

CPlayer::~CPlayer()
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

	if (mGauguSitaji != nullptr)
	{
		delete mGauguSitaji;
		mGauguSitaji = nullptr;
	}

	if (mGaugu != nullptr)
	{
		delete mGaugu;
		mGaugu = nullptr;
	}
}

CPlayer* CPlayer::Instance()
{
	return spInstance;
}

int CPlayer::GetHP() const
{
	return mHP;
}

void CPlayer::SetHP(int hp)
{
	mHP = hp;
}

int CPlayer::MaxHP() const
{
	return mMaxHP;
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
	bool KeyPush = (CInput::Key('W') || CInput::Key('A') || CInput::Key('S') || CInput::Key('D'));

	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	
	if (mIsGrounded)
	{
		// 移動処理
		// キーの入力ベクトルを取得
		CVector input;
		if (CInput::Key('W'))		input.Z(1.0f);
		else if (CInput::Key('S'))	input.Z(-1.0f);
		if (CInput::Key('A'))		input.X(-1.0f);
		else if (CInput::Key('D'))	input.X(1.0f);

		// 入力ベクトルの長さで入力されているか判定
		if (input.LengthSqr() > 0.0f)
		{
			// カメラの向きに合わせた移動ベクトルに変換
			CVector move = CCamera::MainCamera()->Rotation() * input;
			move.Y(0.0f);
			move.Normalize();

			mMoveSpeed += move * MOVE_SPEED;

			// 歩行アニメーションに切り替え
			ChangeAnimation(EAnimType::eWalk);
		}
		// 移動キーを入力していない
		else
		{
			// 待機アニメーションに切り替え
			ChangeAnimation(EAnimType::eIdle);
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
			mState = EState::eJumpStart;
			// スペースキーが押された場合、プレイヤーのHPを減少させる
			int currentHP = spInstance->GetHP();

			int newHP = currentHP - 500;

			// HPが0未満にならないように確認
			if (newHP < 0) {
				newHP = 0;
				if (newHP == 0)
				{
					newHP = 4000;
				}
			}

			spInstance->SetHP(newHP);
			
		}
		// SHIFTキーでダッシュ開始へ移行
		else if (CInput::Key(VK_SHIFT) && KeyPush)
		{
			mMoveSpeed.Y(0.0f);
			mState = EState::eDashStart;
		}
		// Q,Eキーで回避へ移行
		else if ((CInput::PushKey('Q') || CInput::PushKey('E') && KeyPush) || mState == EState::eDash)
		{
			mState = EState::eRotate;
		}
	}
	else
	{
		// 待機アニメーションに切り替え
		ChangeAnimation(EAnimType::eIdle);
	}
}

// 攻撃
void CPlayer::UpdateAttack()
{
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
	mState = EState::eAttackWait;
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
	}
}

//ダッシュ開始
void CPlayer::UpdateDashStart()
{
	ChangeAnimation(EAnimType::eDash);
	mState = EState::eDash;
}

//ダッシュ中
void CPlayer::UpdateDash()
{
	//簡略
	bool KeyPush = CInput::Key('W') || CInput::Key('A') || CInput::Key('S') || CInput::Key('D');
	// ダッシュの速度倍率を設定
	const float dashSpeed = 0.5f; // ダッシュ速度

	// ダッシュ中の速度適用
	// 移動処理
	CVector input;
	if (mState == EState::eDash) {
		// WASDキーの入力を監視し、速度倍率を適用
		if (CInput::Key('W')) {
			input.Z(-1.0f);
		}
		if (CInput::Key('A')) {
			input.X(-1.0f);
		}
		if (CInput::Key('S')) {
			input.Z(1.0f);
		}
		if (CInput::Key('D')) {
			input.X(1.0f);
		}

		// 入力ベクトルを正規化
		if (input.Length() > 0.0f) {
			input.Normalize();
			input *= dashSpeed;
		}
	}

	// 移動処理
	Position(Position() + mMoveSpeed + input);

	// ダッシュタイム減少
	mRemainTime--;

	// 条件
	if (mRemainTime <= 0 || !CInput::Key(VK_SHIFT) || input.Length() == 0.0f)
	{
		// ダッシュ終了アニメーション
		ChangeAnimation(EAnimType::eDashStop);
		mState = EState::eDashEnd;
	}
}

//ダッシュ終了
void CPlayer::UpdateDashEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
		mRemainTime = 50;
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
		//ダッシュ開始
		case EState::eDashStart:
			UpdateDashStart();
			break;
		//ダッシュ状態
		case EState::eDash:
			UpdateDash();
			break;
		//ダッシュ終了
		case EState::eDashEnd:
			UpdateDashEnd();
			break;
		//回避開始
		case EState::eRotate:
			UpdateRotate();
			break;
		//回避終了
		case EState::eRotateEnd:
			UpdateRotateEnd();
			break;
	}

	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	// 移動
	Position(Position() + mMoveSpeed);

	// プレイヤーを移動方向へ向ける
	CVector current = VectorZ();
	CVector target = mMoveSpeed;
	target.Y(0.0f);
	target.Normalize();
	CVector forward = CVector::Slerp(current, target, 0.125f);
	Rotation(CQuaternion::LookRotation(forward));

	mIsGrounded = false;

	// 無敵中はカウントを減少させる
	if (mInvincible > 0)
	{
		// 減算
		mInvincible--;
	}

	// キャラクターの更新
	CXCharacter::Update();
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
	}
}

// 描画
void CPlayer::Render()
{
	// ↓HPゲージ処理
	// HPの取得処理
	int playerHP = spInstance->GetHP();
	int maxHP = spInstance->MaxHP();
	// HPをintからfloat型にしている
	float gaugeWidth = static_cast<float>(playerHP) / static_cast<float>(maxHP) * GAUGE_WIDTH; // HPに応じたゲージの幅

	mGauguSitaji->SetPos(GAUGE_X_POS, GAUGE_Y_POS);
	mGauguSitaji->SetSize(GAUGE_WIDTH, GAUGE_HEIGHT);
	mGauguSitaji->SetUV(0, 0, 426, 63);
	mGauguSitaji->Render();

	mGaugu->SetPos(GAUGE_X_POS, GAUGE_Y_POS);
	mGaugu->SetSize(gaugeWidth, GAUGE_HEIGHT);
	mGaugu->SetUV(434, 426, 0, 63);
	mGaugu->Render();

	// デバッグ情報
	/*CDebugPrint::Print("Player HP: %d\n", playerHP);
	CDebugPrint::Print("Setting Gauge Size: %f x %f\n", gaugeWidth, GAUGE_HEIGHT);*/

	// キャラ描画
	CXCharacter::Render();
}