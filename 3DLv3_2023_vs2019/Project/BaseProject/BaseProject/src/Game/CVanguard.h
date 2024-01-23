#ifndef CVANGUAD_H
#define CVANGUAD_H

#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CRideableObject.h"

class CExclamationMark;

/*
ヴァンガードクラス
キャラクタクラスを継承
*/

class CVanguard : public CXCharacter
{
public:

	// インスタンスのポインタ取得
	static CVanguard* Instance();

	// コンストラクタ
	CVanguard();
	// デストラクタ
	~CVanguard();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突した情報</param>
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
	/// <param name="level">ヴァンガードレベル</param>
	void ChangeLevel(int level);

	// ヴァンガードの方向をランダムに変更する処理
	void ChangeDerection();

	//// フレームとHPゲージの表示の確認をする処理
	//void UpdateGaugeAndFrame();

	//// ビックリマークの表示の確認をする処理
	//void UpdateExclamation();

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

	// ヴァンガードを勝手に移動させる処理
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
	static CVanguard* spInstance;


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

	// ビックリマーク
	CExclamationMark* mpExclamationMark;

	///////////////////////////////////////////////////////


	//// 状態関連 /////////////////////////////////////////

	// 待機状態
	void UpdateIdle();
	// 攻撃
	void UpdateAttack();
	//// 攻撃終了待ち
	//void UpdateAttackWait();
	//// ジャンプ開始
	//void UpdateJumpStart();
	//// ジャンプ中
	//void UpdateJump();
	//// ジャンプ終了
	//void UpdateJumpEnd();
	//// プレイヤー発見
	//void UpdateDiscovery();
	//// 追跡
	//void UpdateChase();
	//// キック
	//void UpdateKick();
	//// キック終了
	//void UpdateKickWait();
	//// エイム解除
	//void UpdateDisarmament();
	//// プレイヤーの攻撃Hit
	//void UpdateHit();
	//// 死亡
	//void UpdateDeth();
	//// 死亡処理終了
	//void UpdateDethEnd();
	//// 徘徊処理
	//void UpdateWander();
	//// バックステップ
	//void UpdateBackStep();

	// 状態
	enum class EState
	{
		eIdle,			// 待機
		eWalk,			// 歩く
		eDash,			// ダッシュ
		eChase,			// 追跡
		eAttack,		// 攻撃
		eAttackEnd,		// 攻撃終了
		eDiscovery,		// プレイヤー発見
		eKick,			// キック
		eKickEnd,		// キック終了
		eDisarmament,	// 武装解除
		eHit,			// ダメージを受ける
		eAvoidance,		// 回避行動
		eDeth,			// 死亡
		eDethEnd,		// 死亡終了
		eWander,		// 徘徊処理
		eBackStep,		// バックステップ
		eJumpStart,		// ジャンプ開始
		eJump,			// ジャンプ中
		eJumpEnd,		// ジャンプ終了
	};
	// 状態変更
	void ChangeState(EState state);
	// ヴァンガードの状態
	EState mState;
	// 乗れるオブジェクトに乗っているか
	CTransform* mpRideObject;

	///////////////////////////////////////////////////////


	//// アニメーション関連 ///////////////////////////////

	enum class EAnimType
	{
		None = -1,

		eTpose,				// Tポーズ
		eIdle,				// 待機状態1
		eIdle1,				// 待機状態2
		eMove1,				// 移動状態1
		eMoveBack1,			// 後ろ移動1
		eMoveShield1,		// 盾歩き1
		eMoveBackShield1,	// 盾後ろ歩き1
		eDash1,				// 走る1
		eAttackSpin,		// スピン攻撃1
		eAAttackKick,		// キック攻撃1
		eGutsPose,			// ガッツポーズ1
		eJumpStart,			// ジャンプ開始
		eJump,				// ジャンプ中
		eJumpEnd,			// ジャンプ終了

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

	// ヴァンガードの見る方向
	CVector mTargetDir;
	// 移動速度
	CVector mMoveSpeed;
	// 初期位置の保存
	CVector mInitialPosition;

	///////////////////////////////////////////////////////


	//// 変数関連 /////////////////////////////////////////

	// 状態内のステップ
	int mStateStep;
	// 経過時間観測用
	float mElapsedTime;
	// 解除時間計測用
	float mElapsedTime_End;
	// キックの時間計測
	float mKickTime;
	// バックステップの時間計測
	float mBackStepTime;
	// プレイヤー発見時の時間計測
	float mDiscoveryTime;
	// プレイヤー発見時の終了時間計測
	float mDiscoveryTime_End;
	// ランダム時間計算
	float mTimeToChange;
	// 設置しているかどうか
	bool mIsGrounded;
	// キックの待ち時間が終了したかどうか
	bool mKickTimeEnd;
	// プレイヤを発見して一定時間経ったかどうか
	bool mDiscovery;
	// プレイヤーを発見し終わった後の時間が取れ倉至ったか
	bool mDiscoveryEnd;

	// プレイヤーを見つけたかどうか
	bool IsFoundPlayer() const;

	///////////////////////////////////////////////////////
};
#endif