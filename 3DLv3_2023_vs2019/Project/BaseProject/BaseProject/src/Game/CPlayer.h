#pragma once
//キャラクタクラスのインクルード
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CRideableObject.h"
#include "CColliderSphere.h"
#include "CImage.h"

class CUIGauge;
class CStaminaGauge;
class CMajicSword;
class CBullet;

#define DEFOLT_CAMERA CVector(0.0f,50.0f,75.0f);

/*
プレイヤークラス
キャラクタクラスを継承
*/
class CPlayer : public CXCharacter
{
public:
	//インスタンスのポインタの取得
	static CPlayer* Instance();

	// コンストラクタ
	CPlayer();
	// デストラクタ
	~CPlayer();

	//	乗ることができるオブジェクトが削除されたときの処理
	void DeleteRideableObject(CTransform* rideObj);

	// ステージ開始時の位置を設定
	void SetStartPosition(const CVector& pos);

	// 準備中の状態
	void UpdateReady();
	// 待機状態
	void UpdateIdle();
	// 攻撃
	void UpdateAttack();
	// 強攻撃
	void UpdateAttackStrong();
	// 攻撃終了待ち1
	void UpdateAttackWait();
	// 攻撃終了待ち2
	void UpdateAttackWait2();
	// ジャンプ開始
	void UpdateJumpStart();
	// ジャンプ中
	void UpdateJump();
	// ジャンプ終了
	void UpdateJumpEnd();
	//ダッシュ終了
	void UpdateDashEnd();
	// 跳ねる
	void UpdateJumpingStart();
	// 跳ねてる途中
	void UpdateJumping();
	// 跳ねるの終了
	void UpdateJumpingEnd();
	//回避開始
	void UpdateRotate();
	//回避終了
	void UpdateRotateEnd();
	// クリア
	void UpdateClear();
	// クリア終了
	void UpdateClearEnd();
	// 死亡
	void UpdateDeth();
	// 死亡処理終了
	void UpdateDethEnd();
	// 再起
	void UpdateReStart();
	// 敵の攻撃Hit
	void UpdateHit();
	// 敵の弾Hit
	void UpdateHitJ();


	bool CanEvade();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// レベル処理
	void LevelUp();	//	レベルアップ
	void ChangeLevel(int level);	// レベル変更

	// hp取得
	int GetHp();
	int GetMaxHp();

	// damage == 受けるダメージ
	void TakeDamage(int damage) override;

	// recovery == 回復
	void TakeRecovery(int recovery) override;

	// 更新
	void Update();

	// 描画
	void Render();

private:
	// アニメーションの種類
	enum class EAnimType
	{
		None = -1,

		eTPose,			// Tポーズ
		eIdle,			// 休憩
		eWalk,			// 歩行
		eAttack,		// 攻撃
		eAttackStrong,	// 強攻撃
		eJumpStart,		// ジャンプ開始
		eJump,			// ジャンプ中
		eJumpEnd,		// ジャンプ終了
		eDash,			// ダッシュ
		eDashStop,		// ダッシュ終了
		eRotate,		// 回避
		eGuts,			// ガッツポーズ
		eHit,			// 敵の攻撃Hit
		eDeth,			// 死亡
		eHitJ,			// 敵の弾Hit

		Num
	};

	// アニメーション切り替え
	void ChangeAnimation(EAnimType type);

	// プレイヤーのインスタンス
	static CPlayer* spInstance;

	// アニメーションデータ
	struct AnimData
	{
		std::string path;	// アニメーションデータのパス
		bool loop;			// ループするかどうか
		float frameLength;	// アニメーションのフレーム数
	};
	// アニメーションデータのテーブル
	static const AnimData ANIM_DATA[];

	// プレイヤーの状態
	enum class EState
	{
		eReady,			// 準備中
		eIdle,			// 待機
		eAttack,		// 攻撃
		eAttackStrong,	// 強攻撃
		eAttackWait,	// 攻撃終了待ち
		eAttackWait2,	// 攻撃終了待ち2
		eJumpStart,		// ジャンプ開始
		eJump,			// ジャンプ中
		eJumpEnd,		// ジャンプ終了
		eJumpingStart,	// 跳ねる開始
		eJumping,		// 跳ねる
		eJumpingEnd,	// 跳ねる終了
		eRotate,		// 回避開始
		eRotateEnd,		// 回避終了待ち
		eDashEnd,		// ダッシュ終了
		eClear,			// クリア状態
		eClearEnd,		// クリア終了
		eDeth,			// 死亡
		eDethEnd,		// 死亡終了
		eReStart,		// 再起
		eHit,			// ダメージヒット
		eHitJ,			// 敵の弾ヒット

	};
	// 現在の状態を切り替え
	void ChangeState(EState state);
	EState mState;		// プレイヤーの状態
	int mStateStep;		// 状態内のステップ

	CVector mMoveSpeed;	// 移動速度
	CVector mPosition;
	CVector mStartPos;	// プレイヤーの位置
	CImage* image;
	bool mIsGrounded;	// 接地しているかどうか

	// コライダーライン
	CColliderLine* mpColliderLine;
	/*CColliderLine* mpColliderLine_2;
	CColliderLine* mpColliderLine_3;*/

	CColliderSphere* mpColliderSphere;

	CTransform* mpRideObject;

	int mInvincible;			// 無敵カウンタ
	bool staminaDepleted;		// スタミナが上限値に到達した場合のフラグ
	bool staminaLowerLimit;		// スタミナが下限値に到達した場合のフラグ
	bool damageObject;			// ダメージを与えるフラグ
	bool damageEnemy;			// ダメージを与えるフラグ(敵)
	bool JumpObject;			// ジャンプオブジェクトのフラグ


	CColliderSphere* mpDamageCol;	//ダメージを受けるコライダ
	CMajicSword* mpSword;
	CBullet* mpBullet;

	// 弾生存時間
	int mLife;

	CUIGauge* mpHpGauge;			// HPゲージ
	CStaminaGauge* mpStaminaGauge;	// スタミナゲージ


	float mElapsedTime;	// 計測時間
	float mElapsedTimeEnd;	// 計測時間終了
	float mElapsedTimeCol;	// コライダーの計測時間
	float JumpCoolDownTime;
};
