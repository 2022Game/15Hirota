#pragma once
//キャラクタクラスのインクルード
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CRideableObject.h"
#include "CImage.h"

class CUIGauge;

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
	// 攻撃終了待ち
	void UpdateAttackWait();
	// ジャンプ開始
	void UpdateJumpStart();
	// ジャンプ中
	void UpdateJump();
	// ジャンプ終了
	void UpdateJumpEnd();
	//ダッシュ開始
	void UpdateDashStart();
	//ダッシュ中
	void UpdateDash();
	//ダッシュ終了
	void UpdateDashEnd();
	//回避開始
	void UpdateRotate();
	//回避終了
	void UpdateRotateEnd();

	// 更新
	void Update();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// 描画
	void Render();

	// レベル処理
	void LevelUp();
	void ChangeLevel(int level);

private:
	// アニメーションの種類
	enum class EAnimType
	{
		None = -1,

		eTPose,			// Tポーズ
		eIdle,			// 待機
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
		eJumpStart,		// ジャンプ開始
		eJump,			// ジャンプ中
		eJumpEnd,		// ジャンプ終了
		eDashStart,		// ダッシュ開始
		eDash,			// ダッシュ中
		eDashEnd,		// ダッシュ終了
		eRotate,		// 回避開始
		eRotateEnd,		// 回避終了待ち
		eClear,			// クリア状態
		eDeth,			// 死亡
	};
	EState mState;		// プレイヤーの状態

	CVector mMoveSpeed;	// 移動速度
	CImage* image;
	bool mIsGrounded;	// 接地しているかどうか

	CColliderLine* mpColliderLine;
	CTransform* mpRideObject;
	int mRemainTime;			// 残り時間
	int mInvincible;			// 無敵カウンタ

	CUIGauge* mpHpGauge;		// HPゲージ
};
