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
#include "CGameManager.h"
#include "CRecoveryObject.h"
#include "CClimbWall.h"

// プレイヤー関連
// 高さ
#define PLAYER_HEIGHT 16.0f
// スピード
#define MOVE_SPEED 0.9f
// 移動スピード
#define RUN_SPEED 1.3f
// ダッシュスピード
#define DASH_SPEED 2.5f
// ジャンプ
#define JUMP_SPEED 1.5f
// 大ジャンプ
#define JUMP_BOUNCE 2.0f
// 重力
#define GRAVITY 0.0625f
// ジャンプ終了時
#define JUMP_END_Y 1.0f

// 壁を登る速度
#define CLIMMB_SPEED 0.5f
// 壁の頂上へ上るのにかかる時間
#define CLIMBED_TOP_TIME 1.0f


//視野の角度(ー角度+角度も出)
#define FOV_ANGLE 45.0f
//視野の角度
#define FOV_LENGTH 5.0f


// HP関連
#define HP 100
// レベル関連
#define LEVEL 1
// スタミナ関連
#define STAMINA 109


// その他
// 色を描画する時間
#define COLORSET 0.5f
// ダメージコライダーの計測時間
#define DAMAGECOL 2.0f

// プレイヤーのインスタンス
CPlayer* CPlayer::spInstance = nullptr;

CPlayer* CPlayer::Instance()
{
	return spInstance;
}

// プレイヤーのアニメーションデータのテーブル
const CPlayer::AnimData CPlayer::ANIM_DATA[] =
{
	{ "",															true,	0.0f	},	// Tポーズ
	{ "Character\\Monster1\\anim\\Warrok_Idle.x",					true,	854.0f	},	// 待機
	{ "Character\\Monster1\\anim\\Warrok_Walking.x",				true,	86.0f	},	// 歩行
	{ "Character\\Monster1\\anim\\Warrok_Punchi.x",				false,	50.0f	},		// 攻撃
	{ "Character\\Monster1\\anim\\Warrok_StrongAttack.x",		false,	161.0f	},		// 強攻撃
	{ "Character\\Monster1\\anim\\jump_start1.x",				false,	25.0f	},		// ジャンプ開始
	{ "Character\\Monster1\\anim\\jump1.x",							true,	1.0f	},	// ジャンプ中
	{ "Character\\Monster1\\anim\\jump_end1.x",					false,	26.0f	},		// ジャンプ終了
	{ "Character\\Monster1\\anim\\Dash1_53.x",					true,	43.0f	},		// ダッシュ開始
	{ "Character\\Monster1\\anim\\Warrok_Run.x",					true,	43.0f	},	// ダッシュ
	{ "Character\\Monster1\\anim\\Warrok_RunStop.x",			false,	40.0f	},		// ダッシュ終了
	{ "Character\\Monster1\\anim\\Rotate.x",					false,	50.0f	},		// 回避
	{ "Character\\Monster1\\anim\\Guts pose_325.x",				false,	325.0f	},		// ガッツポーズ
	{ "Character\\Monster1\\anim\\Hit_63.x",					false,	63.0f	},		// 敵の攻撃Hit
	{ "Character\\Monster1\\anim\\Death_276.x",					false,	276.0f	},		// 死亡Hit_107
	{ "Character\\Monster1\\anim\\Hit_107.x",					false,	107.0f	},		// 敵の弾Hit
	{ "Character\\Monster1\\anim\\Climb_121.x",						true,	121.0f	},	// 壁を登る
	{ "Character\\Monster1\\anim\\Climb_to Top_241.x",				true,	241.0f	},	// 頂上へ登った

};

// コンストラクタ
CPlayer::CPlayer()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eReady)
	, mInventory(std::map<ItemType, int>())
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mElapsedTimeEnd(0.0f)
	, mElapsedTimeCol(0.0f)
	, mInvincibleStartTime(10.0f)
	, mMoveSpeedY(0.0f)
	, mDashTime(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mGroundNormal(0.0f, 1.0f, 0.0f)
	, mClimbNormal(0.0f, 0.0f, 0.0f)
	, mClimbedStartPos(0.0f, 0.0f, 0.0f)
	, mClimbedEndPos(0.0f, 0.0f, 0.0f)
	, mHpHit(false)
	, damageEnemy(false)
	, mInvincible(false)
	, damageObject(false)
	, staminaDepleted(false)
	, mIsPlayedSlashSE(false)
	, staminaLowerLimit(false)
	, mIsPlayedHitDamageSE(false)
	, mQuickDash(false)
	, mDashStamina(false)
	, mDash(false)
	, mClimb(false)
	, mClimbWall(false)
	, mClimbWallTop(false)
	, mIsJumping(false)
	, mpRideObject(nullptr)
{
	ClearItems();
	//, mInventory(std::vector<ItemType>())
	// インスタンスの設定
	spInstance = this;
	Position(0.0f, 60.0f, -30.0f);
	mStartPos = Position();

	// モデルデータ取得
	CModelX* model = CResourceManager::Get<CModelX>("Player");

	// スラッシュSE取得
	mpSlashSE = CResourceManager::Get<CSound>("SlashSound");
	// ダメージ時のボイス取得
	mpHitDamageSE = CResourceManager::Get<CSound>("CreatureGrowl1");

	// HPゲージを作成
	mpHpGauge = new CUIGauge();
	mpHpGauge->SetShow(true);
	// スタミナゲージを作成
	mpStaminaGauge = new CStaminaGauge();
	mpStaminaGauge->SetShow(true);

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
		this, ELayer::ePlayer,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, PLAYER_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eField,ELayer::eDamageObject, ELayer::eJumpingCol,
		ELayer::eBlockCol });


	// 一時的な当たり判定を取るコライダー
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::ePlayer,
		0.5f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::eFieldWall ,ELayer::eField, ELayer::eRecoverCol, 
		ELayer::eInvincbleCol, ELayer::eEnemy, ELayer::eClimb});
	//mpColliderSphere->Position(0.0f, 5.0f, 1.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpColliderSphere->SetAttachMtx(spineMtx);

	// ダメージを受けるコライダーを作成
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.9f
	);
	// ダメージを受けるコライダーと
	// 衝突判定を行うコライダーのレイヤーとタグを設定
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol,ELayer::eGoalCol, ELayer::eKickCol, ELayer::eBulletCol,
		ELayer::eNeedleCol });
	mpDamageCol->SetCollisionTags({ ETag::eEnemyWeapon,ETag::eGoalObject, ETag::eEnemy, ETag::eBullet,
		ETag::eRideableObject });
	// ダメージを受けるコライダーを少し上へずらす
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx1 = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx1);


	// 登れるコライダーとの当たり判定を取るコライダー
	mpClimbCol = new CColliderLine
	(
		this, ELayer::ePlayer,
		CVector(0.0f, PLAYER_HEIGHT, 12.5f),
		CVector(0.0f, PLAYER_HEIGHT, 0.0f)
	);
	mpClimbCol->SetCollisionLayers({ ELayer::eClimb,ELayer::eClimbedTop });


	// マジックソード作成
	mpSword = new CMajicSword();
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHand"));
	mpSword->SetOwner(this);


	// 最初に1レベルに設定
	ChangeLevel(1);
}

CPlayer::~CPlayer()
{
	spInstance = nullptr;
	// コライダー関連の破棄
	SAFE_DELETE(mpColliderLine);
	SAFE_DELETE(mpColliderSphere);
	SAFE_DELETE(mpDamageCol);
	SAFE_DELETE(mpClimbCol);

	// マジックソードを破棄
	mpSword->Kill();
}

// 衝突処理
void CPlayer::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// 乗れるコライダー
	if (self == mpColliderLine)
	{
		if (other->Layer() == ELayer::eField)
		{
			mMoveSpeedY = 0.0f;
			CVector adjust = hit.adjust;
			adjust.X(0.0f);
			adjust.Z(0.0f);
			Position(Position() + adjust * hit.weight);

			// 接地した
			mIsGrounded = true;
			// 接地した地面の法線を記憶しておく
			mGroundNormal = hit.adjust.Normalized();

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
		// プレイヤーにダメージを与えるコライダー
		else if (other->Layer() == ELayer::eDamageObject)
		{
			mMoveSpeedY = 0.0f;
			Position(Position() + hit.adjust);

			// 接地した
			mIsGrounded = true;
			// 接地した地面の法線を記憶しておく
			mGroundNormal = hit.adjust.Normalized();

			if (other->Tag() == ETag::eRideableObject)
			{
				if (!damageObject)
				{
					TakeDamage(1);

					if (mCharaStatus.hp > 0)
					{
						damageObject = true;
						ChangeAnimation(EAnimType::eHit);
						ChangeState(EState::eReStart);
					}
					else
					{
						damageObject = true;
						ChangeState(EState::eDeath);
					}
				}
				mpRideObject = other->Owner();
			}
		}
		// プレイヤーが触れたらジャンプするコライダー
		else if (other->Layer() == ELayer::eJumpingCol)
		{
			if (mState == EState::eJumpEnd)
			{
				//mMoveSpeedY = 0.0f;
				Position(Position() + hit.adjust);
				mpRideObject = other->Owner();
			}
			else
			{
				Position(Position() + hit.adjust);
			}
		}
		// ブロックのコライダー
		else if (other->Layer() == ELayer::eBlockCol)
		{
			if (mState == EState::eJump)
			{
				mMoveSpeedY = 0.0f;
				Position(Position() + hit.adjust);
				mpRideObject = other->Owner();
			}
			else
			{
				Position(Position() + hit.adjust);
			}
		}
	}

	// 一時的な当たり判定を取るコライダー
	// カプセルコライダーが完成したら変更
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
		// 回復アイテム
		else if (other->Layer() == ELayer::eRecoverCol)
		{
			if (other->Tag() == ETag::eItemRecover)
			{
				AddItem(ItemType::HEALING);
			}
		}
		// 無敵アイテム
		else if (other->Layer() == ELayer::eInvincbleCol)
		{
			if (other->Tag() == ETag::eItemInvincible)
			{
				AddItem(ItemType::INVINCIBLE);
			}
		}
		else if (other->Layer() == ELayer::eEnemy)
		{
			Position(Position() + hit.adjust);
		}

		// 登れるオブジェクト
		if (other->Layer() == ELayer::eClimb)
		{
			// Climb状態の場合は位置を調整する
			Position(Position() + hit.adjust);
		}
	}

	// ダメージを受けるコライダー
	if (self == mpDamageCol)
	{
		if (other->Layer() == ELayer::eGoalCol)
		{
			/*CDebugPrint::Print("Player hit GoalObject!\n");*/
			mpDamageCol->SetEnable(false);
			if (CGameManager::StageNo() == 0 || CGameManager::StageNo() == 1 || CGameManager::StageNo() == 2)
			{
				ChangeState(EState::eClear);
			}
		}
		// 敵のキックコライダー
		else if (other->Layer() == ELayer::eKickCol)
		{
			ChangeState(EState::eHit);
		}
		// 敵の弾のコライダー
		else if (other->Layer() == ELayer::eBulletCol)
		{
			ChangeState(EState::eHitBullet);
		}
		else if (other->Layer() == ELayer::eAttackCol)
		{
			ChangeState(EState::eHitSword);
		}
		// 針ブロックのコライダー
		else if (other->Layer() == ELayer::eNeedleCol)
		{
			ChangeState(EState::eHitObj);
			mpRideObject = other->Owner();
		}
	}

	// 登れるコライダーとの当たり判定を取るコライダー
	if (self == mpClimbCol)
	{
		// 登れる壁のコライダー
		if (other->Layer() == ELayer::eClimb)
		{
			mClimbWall = true;
			if (mState == EState::eIdle && mIsGrounded)
			{
				if (CInput::PushKey('E'))
				{
					// Climb状態に移行する
					ChangeState(EState::eClimb);
					// 今から登る壁を記憶しておく
					mpClimbWall = dynamic_cast<CClimbWall*>(other->Owner());
				}
			}

			// 現在壁を登っている最中であれば、
			if (mState == EState::eClimb)
			{
				// 登っている壁の法線を取得
				mClimbNormal = hit.adjust.Normalized();
			}
		}
		// 登れる壁の頂上コライダー
		else if (other->Layer() == ELayer::eClimbedTop)
		{
			mClimbWallTop = true;
		}
	}
}

// アイテムを取得
void CPlayer::AddItem(ItemType item)
{
	mInventory[item]++;
}

// 取得したアイテムを判定
bool CPlayer::HasItem(ItemType item)
{	
	if (mInventory.empty()) {
		return ItemType::NONE == item;
	}
	return mInventory.find(item) != mInventory.end() && mInventory[item] > 0;
}

// 取得したアイテムを判定
void CPlayer::ClearItems()
{
	mInventory.clear();
	//AddItem(ItemType::NONE);
}

// アイテムの取得の条件付けを今後行うための処理
void CPlayer::PickUpItem(ItemType item)
{
	AddItem(item);
}

// 無敵アイテムの使用
void CPlayer::UseInvincibleItem()
{
	if (HasItem(ItemType::INVINCIBLE)) {
		TakeInvincible();
		RemoveItem(ItemType::INVINCIBLE);
	}
}

// 回復薬の使用
void CPlayer::UseHealingItem()
{
	if (HasItem(ItemType::HEALING)) {
		TakeRecovery(1);
		RemoveItem(ItemType::HEALING);
	}
}

// 攻撃力アップアイテムの使用
void CPlayer::UseAttackPotion()
{
	if (HasItem(ItemType::ATTACK_UP)) {
		// 攻撃ポーションを使った時の処理を考える↓

		RemoveItem(ItemType::ATTACK_UP);
	}
}

// インベントリから特定のアイテムを削除
void CPlayer::RemoveItem(ItemType item)
{
	if (mInventory[item] > 0) {
		mInventory[item]--;
		if (mInventory[item] == 0) {
			mInventory.erase(item);	 // アイテムが0になったらインベントリから削除する
		}
	}
}

// 被ダメージ処理
void CPlayer::TakeDamage(int damage)
{
	// SEを再生するとたまにエラーが発生する
	// 一旦保留
	mIsPlayedHitDamageSE = false;
	if (!mIsPlayedHitDamageSE)
	{
		mpHitDamageSE->Play(1.0f, false, 0.0f);
		mIsPlayedHitDamageSE = true;
	}
	//// 死亡していたら、ダメージは受けない
	//if (mCharaStatus.hp <= 0)return;

	//// HPからダメージを引く
	//mCharaStatus.hp = max(mCharaStatus.hp - damage, 0);
	mCharaStatus.hp -= damage;
	// HPが0になったら
	if (mCharaStatus.hp <= 0)
	{
		ChangeState(EState::eDeath);
	}
}

// 回復処理
void CPlayer::TakeRecovery(int recovery)
{
	// ごり押し、多分他の方法がある
	if (mCharaStatus.hp < mCharaMaxStatus.hp && !mHpHit)
	{
		mHpHit = true;
		mCharaStatus.hp += recovery;
	}
}

// 無敵状態処理(コライダーを一定時間オフにする)
void CPlayer::TakeInvincible()
{
	mInvincibleStartTime = 10.0f;
	if (!mInvincible)
	{
		mpDamageCol->SetEnable(false);
		mInvincible = true;
	}
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

// 乗ることができるオブジェクトが削除されたときの処理
void CPlayer::DeleteRideableObject(CTransform* rideObj)
{
	// 削除されるのが現在乗っているオブジェクトであれば、
	// 乗っているオブジェクトを削除
	if (mpRideObject == rideObj)
	{
		mpRideObject = nullptr;
	}
}

// ステージ開始時の位置を設定
void CPlayer::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// 現在の状態を切り替え
void CPlayer::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	// アニメーションの再生速度をもとに戻す
	SetAnimationSpeed(1.0f);
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

// ジャンプをしたかどうか取得
bool CPlayer::IsJumping()
{
	return mIsJumping;
}

// アニメーション切り替え
void CPlayer::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// キーの入力情報から移動ベクトルを求める
CVector CPlayer::CalcMoveVec() const
{
	CVector move = CVector::zero;

	// キーの入力ベクトルを取得
	CVector input = CVector::zero;
	if (CInput::Key('W'))		input.Z(-1.0f);
	else if (CInput::Key('S'))	input.Z(1.0f);
	if (CInput::Key('A'))		input.X(-1.0f);
	else if (CInput::Key('D'))	input.X(1.0f);

	// 入力ベクトルの長さで入力されているか判定
	if (input.LengthSqr() > 0.0f)
	{
		// 上方向ベクトル(設置している場合は、地面の法線)
		CVector up = mIsGrounded ? mGroundNormal : CVector::up;
		// カメラの向きに合わせた移動ベクトルに変換
		CCamera* mainCamera = CCamera::MainCamera();
		CVector camForward = mainCamera->VectorZ();
		camForward.Y(0.0f);
		camForward.Normalize();
		// カメラの正面方向ベクトルと上方向ベクトルの外積から
		// 横方向の移動ベクトルを求める
		CVector moveSide = CVector::Cross(up, camForward);
		// 横方向の移動ベクトルと上方向ベクトルの外積から
		// 正面方向の移動ベクトルを求める
		CVector moveForward = CVector::Cross(moveSide, up);

		// 求めた各方向の移動ベクトルから、
		// 最終的なプレイヤーの移動ベクトルを求める
		move = moveForward * input.Z() + moveSide * input.X();
		move.Normalize();
	}
	return move;
}

// キーの入力情報から移動ベクトルを求める
CVector CPlayer::ClimbMoveVec() const
{
	CVector move = CVector::zero;

	// キーの入力ベクトルを取得
	CVector input = CVector::zero;
	if (CInput::Key('W'))		input.Y(-1.0f);
	else if (CInput::Key('S'))	input.Y(1.0f);
	if (CInput::Key('A'))		input.X(-1.0f);
	else if (CInput::Key('D'))	input.X(1.0f);

	// 入力されている場合のみ、左右方向の移動ベクトルを設定
	if (input.LengthSqr() > 0.0f)
	{
		// ワールドの上方向ベクトルと登っている壁の法線の外積から、
		// 横方向の移動ベクトルを求める
		CVector moveSide = CVector::Cross(CVector::up, mClimbNormal);
		// 求めた横方向の移動ベクトルと登っている壁の法線の外積から、
		// 上下移動ベクトルを求める
		CVector moveUp = CVector::Cross(moveSide, mClimbNormal);

		// プレイヤーの移動ベクトル =
		// 横移動ベクトル×横入力　＋　上下移動ベクトル×上下入力
		move = moveSide * input.X() + moveUp * input.Y();
		move.Normalize();
	}

	return move;
}

// 準備中の状態
void CPlayer::UpdateReady()
{
	// ステップごとに処理を切り替える
	switch (mStateStep)
	{
		// ステップ0 初期化処理
	case 0:
		// 全ての衝突判定をオフにする
		SetEnableCol(false);
		// プレイヤーの移動速度を0にする
		mMoveSpeed = CVector::zero;
		mMoveSpeedY = 0.0f;
		// 次のステップへ
		mStateStep++;
		break;
		// ステップ1 ステージの読み込みから
	case 1:
		// ゲームが開始したら
		if (CGameManager::GameState() == EGameState::eGame)
		{
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
void CPlayer::UpdateIdle()
{
	// 剣に攻撃終了を伝える
	mpSword->AttackEnd();

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	damageEnemy = false;

	mMoveSpeed = CVector::zero;

	if (mIsGrounded)
	{
		mStateStep = 0;

		// プレイヤーの移動ベクトルを求める
		CVector move = CalcMoveVec();
		// 求めた移動ベクトルの長さで入力されているか判定
		if (move.LengthSqr() > 0.0f)
		{
			float speed = MOVE_SPEED;
			if (CInput::Key(VK_SHIFT))
			{
				if ((mCharaStatus.stamina > 0 && !staminaLowerLimit))
				{
					// 最初のダッシュをしたか
					if (!mQuickDash)
					{
						ChangeAnimation(EAnimType::eDashStart);
						//mCharaStatus.stamina -= 1;
						// 通常のダッシュよりも速いダッシュを開始
						speed = DASH_SPEED;

						// スタミナを-10消費
						if (!mDashStamina)
						{
							if (mCharaStatus.stamina >= 10)
							{
								mCharaStatus.stamina -= 15;
								mDashStamina = true;
							}
						}

						// 速いダッシュを1秒間計測
						mDashTime += Time::DeltaTime();
						if (mDashTime >= 0.4f)
						{
							mQuickDash = true;
						}
					}
					else
					{
						ChangeAnimation(EAnimType::eDash);
						speed = RUN_SPEED;
						mDash = true;
						mDashStamina = false;
						mDashTime = 0.0f;
						mCharaStatus.stamina -= 0.001;
					}

					if (mCharaStatus.stamina <= 0)
					{
						mDash = false;
						staminaLowerLimit = true;
						mQuickDash = false;
						mDashStamina = false;
						mDashTime = 0.0f;
						ChangeState(EState::eDashEnd);
					}
				}
				else
				{
					if (staminaLowerLimit && mCharaStatus.stamina == mCharaMaxStatus.stamina)
					{
						staminaLowerLimit = false; // スタミナが再びMAXになったらリセット
						mQuickDash = false;
						mDashTime = 0.0f;
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
					if (mDash)
					{
						mDash = false;
						ChangeState(EState::eDashEnd);
					}
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
		if (CInput::PushKey(VK_LBUTTON))
		{
			mMoveSpeed = CVector::zero;
			ChangeState(EState::eAttack);
		}
		// Kキーで強攻撃
		else if (CInput::PushKey(VK_RBUTTON))
		{
			mMoveSpeed = CVector::zero;
			ChangeState(EState::eAttackStrong);
		}
		// SPACEキーでジャンプ開始へ移行
		else if (CInput::PushKey(VK_SPACE))
		{
			if (mCharaStatus.stamina - 20 >= 0)
			{
				ChangeState(EState::eJumpStart);
				// スタミナが0以下にならない場合はジャンプを実行
				mCharaStatus.stamina -= 20;
			}
			else
			{
			}
		}
		// CTRLキーで回避へ移行
		else if (((CInput::PushKey(VK_CONTROL))) && (mCharaStatus.stamina <= mCharaMaxStatus.stamina))
		{
			// 回避行動前にスタミナが0以下になるかどうかを確認
			if (mCharaStatus.stamina - 50 >= 0) {

				mMoveSpeed = CVector::zero;
				ChangeState(EState::eRotate);
				// スタミナが0以下にならない場合は回避行動を実行
				mCharaStatus.stamina -= 50;
			}
			else
			{
			}
		}
	}
	// プレイヤーが接地していない
	else
	{
		if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
		{
			mCharaStatus.stamina += 1;
		}

		// 空中に飛び出したときに待機モーションへ切り替えるのを
		// 数フレーム待つ
		if (mStateStep <= 5)
		{
			mStateStep++;
		}
		else
		{
			// 待機アニメーションに切り替え
			ChangeAnimation(EAnimType::eIdle);
		}
	}
	CDebugPrint::Print("stamina:%d\n", mCharaStatus.stamina);
	CDebugPrint::Print("mDashTime:%f\n", mDashTime);
}

// ダッシュ終了
void CPlayer::UpdateDashEnd()
{
	mDashStamina = false;
	mQuickDash = false;
	mDashTime = 0.0f;
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	mMoveSpeed = CVector::zero;
	ChangeAnimation(EAnimType::eDashStop);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
		ChangeAnimation(EAnimType::eIdle);
	}
}

// 攻撃
void CPlayer::UpdateAttack()
{
	// 攻撃アニメーションを開始
	ChangeAnimation(EAnimType::eAttack);
	if (GetAnimationFrame() >= 10.0f)
	{
		// 剣に攻撃開始を伝える
		mpSword->AttackStart();
		ChangeState(EState::eAttackWait);
	}

	// 斬撃SEの再生済みフラグを初期化
	mIsPlayedSlashSE = false;
}

// 強攻撃
void CPlayer::UpdateAttackStrong()
{
	// 強攻撃アニメーションを開始
	ChangeAnimation(EAnimType::eAttackStrong);
	// 攻撃終了待ち状態へ移行
	ChangeState(EState::eAttackStrongWait);
}

// 攻撃終了待ち
void CPlayer::UpdateAttackWait()
{
	bool KeyPush = (CInput::Key('W') || CInput::Key('A') || CInput::Key('S') || CInput::Key('D'));
	if (mAnimationFrame >= 10.0f)
	{
		// 攻撃終了待ち状態へ移行
		// CTRLキーで回避へ移行
		if (((CInput::PushKey(VK_CONTROL)) && KeyPush) && (mCharaStatus.stamina <= mCharaMaxStatus.stamina))
		{
			// 回避行動前にスタミナが0以下になるかどうかを確認
			if (mCharaStatus.stamina - 50 >= 0)
			{
				ChangeState(EState::eRotate);
				// スタミナが0以下にならない場合は回避行動を実行
				mCharaStatus.stamina -= 50;
				mpSword->AttackEnd();

			}
			else
			{
			}
		}

		if (CInput::PushKey(VK_SPACE))
		{
			mpSword->AttackEnd();
			if (mCharaStatus.stamina - 20 >= 0)
			{
				ChangeState(EState::eJumpStart);
				// スタミナが0以下にならない場合はジャンプを実行
				mCharaStatus.stamina -= 20;
			}
			else
			{
			}
		}

		// SE
		if (!mIsPlayedSlashSE && GetAnimationFrame() >= 10.0f)
		{
			// 斬撃SEを再生
			mpSlashSE->Play(1.0f, false, 0.0f);
			mIsPlayedSlashSE = true;
		}

		if (GetAnimationFrame() >= 50.0f)
		{
			// 剣に攻撃終了を伝える
			mpSword->AttackEnd();
		}
	}
	else
	{

	}
	// 攻撃アニメーションが終了したら、
	if (IsAnimationFinished())
	{
		// 待機状態へ移行
		ChangeState(EState::eIdle);
		ChangeAnimation(EAnimType::eIdle);
	}
}

// 強攻撃終了待ち
void CPlayer::UpdateAttackStrongWait()
{
	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
		ChangeAnimation(EAnimType::eIdle);
	}
}

//回避開始
void CPlayer::UpdateRotate()
{
	mpDamageCol->SetEnable(false);

	// 移動処理
	CVector move = CalcMoveVec();

	// 入力ベクトルの長さで入力されているか判定
	if (move.LengthSqr() > 0.0f)
	{
		float speed = MOVE_SPEED;
		mMoveSpeed += move * speed * MOVE_SPEED * mCharaStatus.moveSpeed;
	}
	ChangeAnimation(EAnimType::eRotate);
	ChangeState(EState::eRotateEnd);
}

//回避終了待ち
void CPlayer::UpdateRotateEnd()
{
	if (IsAnimationFinished())
	{
		mpDamageCol->SetEnable(true);

		if (mElapsedTimeCol <= DAMAGECOL)
		{
			mElapsedTimeCol += Time::DeltaTime();
			if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
			{
				mElapsedTimeCol = DAMAGECOL;
				mpDamageCol->SetEnable(true);
			}
		}

		ChangeState(EState::eIdle);
		ChangeAnimation(EAnimType::eIdle);
	}
}

// クリア
void CPlayer::UpdateClear()
{
	mMoveSpeed = CVector::zero;
	ChangeAnimation(EAnimType::eGuts);
	ChangeState(EState::eClearEnd);
}

// クリア終了
void CPlayer::UpdateClearEnd()
{
	if (IsAnimationFinished())
	{
		if (CGameManager::StageNo() == 0)
		{
			// ステージをクリア
			CGameManager::StageClear();
			// ステージをクリアしたら、次のステージ開始まで準備中の状態に変更
			ChangeState(EState::eReady);
			Position(mStartPos);
		}
	}
}

// 死亡
void CPlayer::UpdateDeath()
{
	mpDamageCol->SetEnable(false);
	mpSword->AttackEnd();
	mMoveSpeed = CVector::zero;
	ChangeAnimation(EAnimType::eDeath);
	if (IsAnimationFinished())
	{
		ChangeState(EState::eDeathEnd);
	}
}

// 死亡処理終了
void CPlayer::UpdateDeathEnd()
{
	if (IsAnimationFinished())
	{
		damageObject = false;
		mCharaStatus = mCharaMaxStatus;
		Position(0.0f, 20.0f, -30.0f);
		ChangeState(EState::eIdle);
	}
}

// 再起
void CPlayer::UpdateReStart()
{
	if (IsAnimationFinished())
	{
		damageObject = false;
		Position(0.0f, 10.0f, -30.0f);
		ChangeState(EState::eIdle);
	}
}

// 敵の攻撃を受けた時
void CPlayer::UpdateHit()
{
	mMoveSpeed = CVector::zero;
	SetColor(CColor(1.0, 0.0, 0.0, 1.0));
	if (!damageEnemy)
	{
		TakeDamage(3);
		damageEnemy = true;
	}

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	ChangeAnimation(EAnimType::eHitJ);
	if (IsAnimationFinished())
	{
		if (mCharaStatus.hp > 0)
		{
			mIsPlayedHitDamageSE = false;
			damageEnemy = false;
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eIdle);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
		}
	}
}

// 敵の弾の攻撃を受けた時
void CPlayer::UpdateHitBullet()
{
	ChangeAnimation(EAnimType::eHit);

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	mMoveSpeed = CVector::zero;
	mElapsedTime += Time::DeltaTime();
	SetColor(CColor(1.0, 0.0, 0.0, 1.0));

	if (!damageEnemy)
	{
		TakeDamage(1);
		damageEnemy = true;
		mpDamageCol->SetEnable(true);
	}

	if (mElapsedTime >= COLORSET)
	{
		if (mCharaStatus.hp > 0)
		{
			mIsPlayedHitDamageSE = false;
			damageEnemy = true;
			mElapsedTime = 0.0f;
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eIdle);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mElapsedTime = 0.0f;
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
		}
	}

	//CDebugPrint::Print("Time%f\n", mElapsedTime);
}

// 敵の剣の攻撃を受けた時
void CPlayer::UpdateHitSword()
{
	ChangeAnimation(EAnimType::eHit);

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	mMoveSpeed = CVector::zero;
	mElapsedTime += Time::DeltaTime();
	SetColor(CColor(1.0, 0.0, 0.0, 1.0));

	if (!damageEnemy)
	{
		damageEnemy = true;
		mpDamageCol->SetEnable(true);
	}

	if (mElapsedTime >= COLORSET)
	{
		if (mCharaStatus.hp > 0)
		{
			mIsPlayedHitDamageSE = false;
			damageEnemy = true;
			mElapsedTime = 0.0f;
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eIdle);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mElapsedTime = 0.0f;
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
		}
	}

	//CDebugPrint::Print("Time%f\n", mElapsedTime);
}

// ダメージを受ける(オブジェクト)
void CPlayer::UpdateHitObj()
{
	ChangeAnimation(EAnimType::eHit);

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	mMoveSpeed = CVector::zero;
	mElapsedTime += Time::DeltaTime();
	SetColor(CColor(1.0, 0.0, 0.0, 1.0));

	if (!damageEnemy)
	{
		damageEnemy = true;
		mpDamageCol->SetEnable(true);
	}

	if (mElapsedTime >= COLORSET)
	{
		if (mCharaStatus.hp > 0)
		{
			mIsPlayedHitDamageSE = false;
			damageEnemy = true;
			mElapsedTime = 0.0f;
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eIdle);
		}
		else if (mCharaStatus.hp <= 0)
		{
			mElapsedTime = 0.0f;
			mElapsedTimeCol = 0.0f;
			mpDamageCol->SetEnable(false);
			ChangeState(EState::eDeath);
		}
	}
}

// 登る状態
void CPlayer::UpdateClimb()
{
	mClimb = true;
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;
	// プレイヤーの移動ベクトルを求める
	CVector move = ClimbMoveVec();

	ChangeAnimation(EAnimType::eClimb);

	// 求めた移動ベクトルの長さで入力されているか判定
	if (move.LengthSqr() > 0.0f)
	{
		// 上下キーが入力されている場合
		if (move.Y() != 0.0f)
		{
			// 壁を登っている時は、アニメーションを通常再生し、
			// 壁を降りているときはアニメーションを逆再生する
			SetAnimationSpeed(move.Y() > 0.0f ? 1.0f : -1.0f);
		}
		// 左右キーのみが入力されている場合
		else
		{
			SetAnimationSpeed(1.0f);
		}
	}
	// 移動キーが入力されていない場合
	else
	{
		// アニメーションを停止する
		SetAnimationSpeed(0.0f);
	}
	mMoveSpeed = move * CLIMMB_SPEED;

	if (CInput::PushKey('E'))
	{
		mClimb = false;
		ChangeState(EState::eJumpStart);
	}

	// 登れる壁の範囲外に出た場合
	if (!mClimbWall)
	{
		// 登れる壁の頂上に触れていた場合
		if (mClimbWallTop)
		{
			// 頂上へ上る状態へ移行
			ChangeState(EState::eClimbedTop);
		}
		// 登れる壁の頂上に触れていなかった場合
		else
		{
			// 登っている状態を解除して、待機状態へ移行
			mClimb = false;
			ChangeState(EState::eIdle);
		}
	}
	CDebugPrint::Print("mClimbWall: %s\n", mClimbWall ? "true" : "false");
	CDebugPrint::Print("mClimbWallTop: %s\n", mClimbWallTop ? "true" : "false");
}

// 頂上まで登った
void CPlayer::UpdateClimbedTop()
{
	mClimb = true;
	mMoveSpeed = CVector::zero;
	mMoveSpeedY = 0.0f;

	// ステップ管理
	switch (mStateStep)
	{
		// ステップ0: 初期化処理
	case 0:
	{
		// 頂上へ上り切った時の移動前の座標と移動後の座標を設定
		mClimbedStartPos = Position();
		CVector move = Rotation() * mpClimbWall->GetClimbedMoveVec();
		mClimbedEndPos = mClimbedStartPos + move;

		mElapsedTime = 0.0f;
		// 頂上へ上り切った時のアニメーションを再生
		ChangeAnimation(EAnimType::eClimbedTop);

		// 次のステップへ
		mStateStep++;
		break;
	}
	// ステップ1: 登り切った時のアニメーションの経過待ち
	case 1:
		// 登り切った時のアニメーションの半分を超えたら、次のステップへ
		if (GetAnimationFrameRatio() >= 0.5f)
		{
			mStateStep++;
		}
		break;
		// ステップ2: 頂上へ上り切った後の移動処理
	case 2:
		// 経過時間に合わせて移動
		if (mElapsedTime < CLIMBED_TOP_TIME)
		{
			float per = mElapsedTime / CLIMBED_TOP_TIME;
			CVector pos = CVector::Lerp(mClimbedStartPos, mClimbedEndPos, per);
			Position(pos);
			mElapsedTime += Time::DeltaTime();
		}
		// 移動が終わった
		else
		{
			Position(mClimbedEndPos);
			// 壁を登っている状態を解除
			mClimb = false;
			ChangeState(EState::eIdle);
		}
		break;
	}
}

// ジャンプ開始
void CPlayer::UpdateJumpStart()
{
	mIsJumping = true;
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eJump);

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	// 移動処理
	CVector move = CalcMoveVec();

	// 入力ベクトルの長さで入力されているか判定
	if (move.LengthSqr() > 0.0f)
	{
		mMoveSpeed = move;
	}
	mMoveSpeedY += JUMP_SPEED;
	mIsGrounded = false;
}

// ジャンプ中
void CPlayer::UpdateJump()
{
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	if (mMoveSpeedY <= 0.0f)
	{
		mIsJumping = false;
		ChangeAnimation(EAnimType::eJumpEnd);
		ChangeState(EState::eJumpEnd);
	}
}

// ジャンプ終了
void CPlayer::UpdateJumpEnd()
{
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
	}
}

// 跳ねる処理開始
void CPlayer::UpdateJumpingStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	ChangeState(EState::eJumping);

	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	// 移動処理
	CVector move = CalcMoveVec();

	// 入力ベクトルの長さで入力されているか判定
	if (move.LengthSqr() > 0.0f)
	{
		mMoveSpeed = move;
	}
	mMoveSpeedY = JUMP_BOUNCE;
	mIsGrounded = false;
}

// 跳ねる処理
void CPlayer::UpdateJumping()
{
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	if (mMoveSpeedY <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		ChangeState(EState::eJumpingEnd);
	}
}

// 跳ねる処理開始
void CPlayer::UpdateJumpingEnd()
{
	if (mElapsedTimeCol <= DAMAGECOL)
	{
		mElapsedTimeCol += Time::DeltaTime();
		if (mElapsedTimeCol >= DAMAGECOL && !mInvincible)
		{
			mElapsedTimeCol = DAMAGECOL;
			mpDamageCol->SetEnable(true);
		}
	}

	if (IsAnimationFinished())
	{
		ChangeState(EState::eIdle);
	}
}

// 更新
void CPlayer::Update()
{
	SetParent(mpRideObject);
	SetColor(CColor(1.0, 1.0, 1.0, 1.0));
	mpRideObject = nullptr;
	mHpHit = false;

	// 状態に合わせて、更新処理を切り替える
	switch (mState)
	{
		// 準備中の状態
	case EState::eReady:
		UpdateReady();
		break;
		// 待機状態
	case EState::eIdle:
		UpdateIdle();
		break;
		// ダッシュ終了
	case EState::eDashEnd:
		UpdateDashEnd();
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
		// 強攻撃終了待ち
	case EState::eAttackStrongWait:
		UpdateAttackStrongWait();
		break;
		// 回避開始
	case EState::eRotate:
		UpdateRotate();
		break;
		// 回避終了
	case EState::eRotateEnd:
		UpdateRotateEnd();
		break;
		// 敵のダメージHit
	case EState::eHit:
		UpdateHit();
		break;
		// 敵の弾Hit
	case EState::eHitBullet:
		UpdateHitBullet();
		break;
		// 敵の件Hit
	case EState::eHitSword:
		UpdateHitSword();
		break;
		// ダメージを受ける(オブジェクト)
	case EState::eHitObj:
		UpdateHitObj();
		break;
		// 登る状態
	case EState::eClimb:
		UpdateClimb();
		break;
		// 頂上まで登った
	case EState::eClimbedTop:
		UpdateClimbedTop();
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
	case EState::eDeath:
		UpdateDeath();
		break;
		// 死亡処理終了
	case EState::eDeathEnd:
		UpdateDeathEnd();
		break;
		// 再起
	case EState::eReStart:
		UpdateReStart();
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
		// 跳ねる開始
	case EState::eJumpingStart:
		UpdateJumpingStart();
		break;
		// 跳ねる
	case EState::eJumping:
		UpdateJumping();
		break;
		// 跳ねる終了
	case EState::eJumpingEnd:
		UpdateJumpingEnd();
		break;
	}

	// 準備中でなければ、移動処理などを行う
	if (mState != EState::eReady)
	{
		if (!mClimb)
		{
			mMoveSpeedY -= GRAVITY;
		}
		CVector moveSpeed = mMoveSpeed + CVector(0.0f, mMoveSpeedY, 0.0f * Time::DeltaTime());

		// 移動
		Position(Position() + moveSpeed * 60.0f * Time::DeltaTime());

		// プレイヤーの向きを調整
		CVector current = VectorZ();
		CVector target = moveSpeed;
		if (mState == EState::eClimb)
		{
			// 壁の法線の反対方向を向く
			target = -mClimbNormal;
		}
		// それ以外の時は、プレイヤーの移動方向へ向ける
		else
		{
			target = moveSpeed;
			target.Y(0.0f);
			target.Normalize();
		}
		CVector forward = CVector::Slerp(current, target, 0.125f);
		Rotation(CQuaternion::LookRotation(forward));
	}

	// 無敵状態だった場合の処理
	if (mInvincible)
	{
		SetColor(CColor(1.0, 1.0, 0.0, 1.0));
		mInvincibleStartTime -= Time::DeltaTime();

		if (mInvincibleStartTime <= 0.0f)
		{
			mpDamageCol->SetEnable(true);
			mInvincibleStartTime = 10.0f;
			mInvincible = false;
		}
	}

	// なんの処理か忘れたが、消しても問題が無かったため
	// コメントアウト
	// 恐らくジャンプコライダー関連
	/*if (JumpObject)
	{
		JumpCoolDownTime -= Time::DeltaTime();

		if (JumpCoolDownTime <= 0.0f)
		{
			JumpObject = false;
		}
	}*/

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


	///////////////////////////////////////////
	// 仮の落下ダメージ処理
	// 変更予定
	float minHeaight = -100.0f;
	if (Position().Y() < minHeaight)
	{
		ChangeAnimation(EAnimType::eHitJ);
		TakeDamage(1);
		Position(0.0f, 20.0f, -30.0f);
	}
	///////////////////////////////////////////

	// キャラクターの更新
	CXCharacter::Update();
	mpDamageCol->Update();
	mpColliderSphere->Update();
	mpSword->UpdateAttachMtx();

	mIsGrounded = false;
	mClimbWall = false;
	mClimbWallTop = false;

	//// 縦方向の移動速度監視
	//CDebugPrint::Print("mMoveSpeed%f\n", mMoveSpeed.Y());
	//// 無敵時間の時間監視
	//CDebugPrint::Print("mInvincible:%f\n", mInvincibleStartTime);
	//// 現在の縦方向のポジション監視
	//CDebugPrint::Print("Position.Y %f\n", Position().Y());
	//// コライダーの復活時間監視
	//CDebugPrint::Print("TimeCol%f\n", mElapsedTimeCol);
	CDebugPrint::Print("mMoveSpeedY%f\n", mMoveSpeedY);
}

// 描画
void CPlayer::Render()
{
	// キャラ描画
	CXCharacter::Render();
}