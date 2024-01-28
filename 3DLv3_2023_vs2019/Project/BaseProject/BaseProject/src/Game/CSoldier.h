#ifndef CSOLDIER_H
#define CSOLDIER_H

//キャラクタクラスのインクルード
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CRideableObject.h"
#include "CEffect.h"

class CGun;
class CBullet;
class CPlayer;
class CSoldierFrame;
class CSoldierGauge;
class CExclamationMark;

/*
ソルジャークラス
キャラクタクラスを継承
*/

class CSoldier : public CXCharacter
{
public:

	//インスタンスのポインタの取得
	CSoldier* Instance();

	// コンストラクタ
	CSoldier();
	// デストラクタ
	~CSoldier();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="damage">受けるダメージ</param>
	void TakeDamage(int damage) override;

	// レベル処理
	// レベルアップ
	void LevelUp();
	/// <summary>
	/// レベル変更
	/// </summary>
	/// <param name="level">ソルジャーレベル</param>
	void ChangeLevel(int level);

	// ソルジャーの方向をランダムに変更する処理
	void ChangeDerection();

	// フレームとHPゲージの表示の確認をする処理
	void UpdateGaugeAndFrame();

	// ビックリマークの表示の確認をする処理
	void UpdateExclamation();

	// 1%の確率を求める処理
	bool ShouldTransitionWander();
	// 上記と同様
	bool ShouldTransition();

	/// <summary>
	/// 360度の角度を求めて、x軸とy軸から計算する
	/// </summary>
	/// <param name="angleDegrees">角度</param>
	/// <returns></returns>
	CVector CalculateDirection(float angleDegrees);

	// ソルジャーを勝手に移動させる処理
	void Move();

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
	static CSoldier* spInstance;


	//// モデル・素材関連 /////////////////////////////////

	// フィールドとの当たり判定を取るコライダー
	CColliderLine* mpColliderLine;
	// 一時的な当たり判定を取るコライダー
	// カプセルコライダが完成したら変更
	CColliderSphere* mpColliderSphere;
	// ダメージを受けるコライダー
	CColliderSphere* mpDamageCol;
	// ダメージを与えるコライダー
	CColliderSphere* mpAttackCol;

	// 銃モデル
	CGun* mpGun;

	// フレーム
	CSoldierFrame* mpFrame;
	// ゲージ
	CSoldierGauge* mpGauge;
	// ビックリマーク
	CExclamationMark* mpExclamationMark;

	///////////////////////////////////////////////////////


	//// 状態関連 /////////////////////////////////////////
	
	// 待機状態
	void UpdateIdle();
	// 攻撃
	void UpdateAttack();
	// 攻撃終了待ち
	void UpdateAttackWait();
	// ジャンプ開始
	void UpdateJumpStart();
	// ジャンプ中
	void UpdateJump();
	// ジャンプ終了
	void UpdateJumpEnd();
	// プレイヤー発見
	void UpdateDiscovery();
	// 追跡
	void UpdateChase();
	// キック
	void UpdateKick();
	// キック終了
	void UpdateKickWait();
	// エイム解除
	void UpdateAimDwon();
	// プレイヤーの攻撃Hit
	void UpdateHit();
	// 死亡
	void UpdateDeth();
	// 死亡処理終了
	void UpdateDethEnd();
	// 徘徊処理
	void UpdateWander();
	// バックステップ
	void UpdateBackStep();

	// 状態
	enum class EState
	{
		eIdle,		// 待機
		eAttack,	// 攻撃
		eAttackWait,// 攻撃終了待ち
		eDiscovery,	// プレイヤー発見
		eChase,		// 追跡
		eKick,		// キック
		eKickWait,	// キック終了
		eAimDwon,	// エイム解除
		eHit,		// ダメージHit
		eDeth,		// 死亡
		eDethEnd,	// 死亡終了
		eWander,	// 徘徊処理
		eBackStep,	// バックステップ
		eJumpStart,	// ジャンプ開始
		eJump,		// ジャンプ中
		eJumpEnd,	// ジャンプ終了
	};
	// 状態変更
	void ChangeState(EState state);
	// プレイヤーの状態
	EState mState;
	// 乗れるオブジェクトに乗っているか
	CTransform* mpRideObject;

	//////////////////////////////////////////////////////////


	//// アニメーション関連 //////////////////////////////////
	
	// アニメーションの種類
	enum class EAnimType
	{
		None = -1,

		eTpose,		// Tポーズ
		eIdle,		// Idle時
		eRifleIdle,	// ライフルIdle時
		eWalk,		// 移動
		eAlert,		// 警戒
		eAttack,	// プレイヤー発見時攻撃
		eKick,		// 格闘
		eReload,	// リロード
		eAimDwou,	// エイム解除
		eHit,		// ダメージHit
		eDeth,		// 死亡
		eBackStep,	// バックステップ
		eJumpEnd,	// ジャンプ終了
		eJumpStart,	// ジャンプ開始
		eJump,		// ジャンプ中

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

	//////////////////////////////////////////////////////////


	//// ベクトル関連 ////////////////////////////////////////

	// ソルジャーの見る方向
	CVector mTargetDir;
	// 移動速度
	CVector mMoveSpeed;
	// 初期位置の保存
	CVector mInitialPosition;

	//////////////////////////////////////////////////////////
	

	//// 変数関連 ////////////////////////////////////////////
	
	// 銃の弾の開始値
	int mTimeShot;
	// 銃の弾の終わり値
	int mTimeShotEnd;
	// 状態内のステップ
	int mStateStep;
	// 経過時間計測用
	float mElapsedTime;
	// 解除時間計測用
	float mElapsedTime_End;
	// ランダム時間計算
	float mTimeToChange;
	// キックの時間計測用
	float mKickTime;
	// バックステップの時間計測
	float mBackStepTime;
	// プレイヤー発見時の時間計測
	float mDiscoveryTime;
	// プレイヤー発見時の終了時間計測
	float mDiscoveryTimeEnd;
	// 接地しているかどうか
	bool mIsGrounded;
	// キックの待ち時間が終わったかどうか
	bool mKickTimeEnd;
	// プレイヤーを発見して一定時間経ったかどうか
	bool mDiscovery;
	// プレイヤーを発見し終わった後の時間がどれくらい経ったか
	bool mDiscoveryEnd;
	// バックステップをするか
	bool mBackStep;

	// プレイヤーを見つけたか
	bool IsFoundPlayer() const;

	//////////////////////////////////////////////////////////
};
#endif