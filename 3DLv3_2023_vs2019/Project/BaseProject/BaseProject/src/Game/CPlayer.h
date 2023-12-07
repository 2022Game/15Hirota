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
	//回避開始
	void UpdateRotate();
	//回避終了
	void UpdateRotateEnd();

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

	// 死亡処理
	void Deth();

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
		eIdle,			// 待機
		eAttack,		// 攻撃
		eAttackStrong,	// 強攻撃
		eAttackWait,	// 攻撃終了待ち
		eAttackWait2,	// 攻撃終了待ち2
		eJumpStart,		// ジャンプ開始
		eJump,			// ジャンプ中
		eJumpEnd,		// ジャンプ終了
		eRotate,		// 回避開始
		eRotateEnd,		// 回避終了待ち
		eDashEnd,		// ダッシュ終了
		eClear,			// クリア状態
		eDeth,			// 死亡
	};
	EState mState;		// プレイヤーの状態

	CVector mMoveSpeed;	// 移動速度
	CImage* image;
	bool mIsGrounded;	// 接地しているかどうか

	// コライダーライン
	CColliderLine* mpColliderLine;
	CColliderLine* mpColliderLine_2;
	CColliderLine* mpColliderLine_3;

	CTransform* mpRideObject;
	int mInvincible;			// 無敵カウンタ
	bool staminaDepleted;		// スタミナが上限値に到達した場合のフラグ
	bool staminaLowerLimit;		// スタミナが下限値に到達した場合のフラグ

	CColliderSphere* mpDamageCol;	//ダメージを受けるコライダ
	CMajicSword* mpSword;
	CBullet* mpBullet;

	// 弾生存時間
	int mLife;

	CUIGauge* mpHpGauge;			// HPゲージ
	CStaminaGauge* mpStaminaGauge;	// スタミナゲージ
};
