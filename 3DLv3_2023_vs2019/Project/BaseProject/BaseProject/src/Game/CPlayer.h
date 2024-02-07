#pragma once

//キャラクタクラスのインクルード
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CRideableObject.h"
#include "CColliderSphere.h"
#include "CImage.h"
#include "CSound.h"

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

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// damage == 受けるダメージ
	void TakeDamage(int damage) override;

	// recovery == 回復
	void TakeRecovery(int recovery) override;

	// 無敵状態にする(コライダーをオフにする)
	void TakeInvincible() override;

	// レベル処理
	// レベルアップ
	void LevelUp();
	// レベル変更
	void ChangeLevel(int level);

	//	乗ることができるオブジェクトが削除されたときの処理
	void DeleteRideableObject(CTransform* rideObj);

	// ステージ開始時の位置を設定
	void SetStartPosition(const CVector& pos);

	// hp取得
	int GetHp();
	int GetMaxHp();

	// 他のクラスで使っている為publicに置いておく
	// ジャンプ開始
	void UpdateJumpStart();
	// ジャンプ中
	void UpdateJump();
	// ジャンプ終了
	void UpdateJumpEnd();
	// 跳ねる
	void UpdateJumpingStart();
	// 跳ねてる途中
	void UpdateJumping();
	// 跳ねるの終了
	void UpdateJumpingEnd();

	// 更新
	void Update();
	// 描画
	void Render();
	
private:
	// モデル・素材関連
	// 状態関連
	// アニメーション関連
	// ベクトル関連
	// 変数関連

	// プレイヤーのインスタンス
	static CPlayer* spInstance;


	//// モデル・素材関連 /////////////////////////////////
	
	// 縦のコライダーライン
	CColliderLine* mpColliderLine;
	// 一時的な当たり判定を取るコライダー
	// カプセルコライダーが完成したら変更
	CColliderSphere* mpColliderSphere;
	//ダメージを受けるコライダ
	CColliderSphere* mpDamageCol;

	// マジックソードモデル
	CMajicSword* mpSword;
	
	// HPゲージ
	CUIGauge* mpHpGauge;
	// スタミナゲージ
	CStaminaGauge* mpStaminaGauge;

	// 剣の振りかざし攻撃時のSE
	CSound* mpSlashSE;
	// 敵の攻撃が当たった時のSE
	CSound* mpHitDamageSE;

	///////////////////////////////////////////////////////
	

	//// 状態関連 /////////////////////////////////////////
	
	// 準備中の状態
	void UpdateReady();
	// 待機状態
	void UpdateIdle();
	//ダッシュ終了
	void UpdateDashEnd();
	// 攻撃
	void UpdateAttack();
	// 強攻撃
	void UpdateAttackStrong();
	// 攻撃終了待ち
	void UpdateAttackWait();
	// 強攻撃終了待ち
	void UpdateAttackStrongWait();
	//回避開始
	void UpdateRotate();
	//回避終了待ち
	void UpdateRotateEnd();
	// クリア
	void UpdateClear();
	// クリア終了
	void UpdateClearEnd();
	// 死亡
	void UpdateDeath();
	// 死亡処理終了
	void UpdateDeathEnd();
	// 再起
	void UpdateReStart();
	// 敵の攻撃Hit
	void UpdateHit();
	// 敵の弾Hit
	void UpdateHitBullet();
	// 敵の剣攻撃hit
	void UpdateHitSword();
	// プレイヤーの状態
	enum class EState
	{
		eReady,				// 準備中
		eIdle,				// 待機
		eAttack,			// 攻撃
		eAttackStrong,		// 強攻撃
		eAttackWait,		// 攻撃終了待ち
		eAttackStrongWait,	// 攻撃終了待ち2
		eJumpStart,			// ジャンプ開始
		eJump,				// ジャンプ中
		eJumpEnd,			// ジャンプ終了
		eJumpingStart,		// 跳ねる開始
		eJumping,			// 跳ねる
		eJumpingEnd,		// 跳ねる終了
		eRotate,			// 回避開始
		eRotateEnd,			// 回避終了待ち
		eDashEnd,			// ダッシュ終了
		eClear,				// クリア状態
		eClearEnd,			// クリア終了
		eDeath,				// 死亡
		eDeathEnd,			// 死亡終了
		eReStart,			// 再起
		eHit,				// ダメージヒット
		eHitBullet,			// 敵の弾ヒット
		eHitSword,			// 敵の剣ヒット
	};
	// 現在の状態を切り替え
	void ChangeState(EState state);
	// プレイヤーの状態
	EState mState;
	CTransform* mpRideObject;

	///////////////////////////////////////////////////////
	
	
	//// アニメーション関連 ///////////////////////////////
	

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
		eDeath,			// 死亡
		eHitJ,			// 敵の弾Hit

		Num
	};

	// アニメーション切り替え
	void ChangeAnimation(EAnimType type);

	// アニメーションデータ
	struct AnimData
	{
		std::string path;	// アニメーションデータのパス
		bool loop;			// ループするかどうか
		float frameLength;	// アニメーションのフレーム数
	};
	// アニメーションデータのテーブル
	static const AnimData ANIM_DATA[];

	///////////////////////////////////////////////////////


	//// ベクトル関連 /////////////////////////////////////

	CVector mMoveSpeed;		// 移動速度(X,Z)
	CVector mStartPos;		// プレイヤーの初期位置
	CVector mGroundNormal;	// 設置している地面の法線

	///////////////////////////////////////////////////////


	//// キー入力関連 /////////////////////////////////////

	/// <summary>
	/// キーの入力情報から移動ベクトルを求める
	/// </summary>
	/// <returns></returns>
	CVector CalcMoveVec() const;

	///////////////////////////////////////////////////////


	//// 変数関連 /////////////////////////////////////////

	// 状態内のステップ
	int mStateStep;
	// 計測時間
	float mElapsedTime;
	// 計測時間終了
	float mElapsedTimeEnd;
	// コライダーの計測時間
	float mElapsedTimeCol;
	// 無敵状態用の計測時間
	float mInvincibleStartTime;
	// 重力やジャンプによるY軸の移動速度
	float mMoveSpeedY;
	// 接地しているかどうか
	bool mIsGrounded;
	// 無敵かどうか
	bool mInvincible;
	// スタミナが上限値に到達した場合のフラグ
	bool staminaDepleted;
	// スタミナが下限値に到達した場合のフラグ
	bool staminaLowerLimit;
	// ダメージを与えるフラグ
	bool damageObject;
	// ダメージを与えるフラグ(敵)
	bool damageEnemy;
	// 回復したか
	bool mHpHit;
	// スラッシュのSEを再生したか
	bool mIsPlayedSlashSE;
	// 攻撃が当たったか
	bool mIsPlayedHitDamageSE;

	///////////////////////////////////////////////////////
};
