#pragma once

//キャラクタクラスのインクルード
#include "CXCharacter.h"
#include "CColliderLine.h"
#include "CRideableObject.h"
#include "CColliderSphere.h"
#include "CCutInDeath.h"
#include "CCutInClear.h"
#include <map>

class CUIGauge;
class CStaminaGauge;
class CMajicSword;
class CBullet;
class CClimbWall;
class CWireMeshClimbWall;
class CWireMeshMoveClimbWall;
class CFlamethrower;
class CStage3;
class CImage;
class CSound;
class CCutInDeath;
class CCutInClear;
class CCutInResult;
class CScreenItem;

#define DEFOLT_CAMERA CVector(0.0f,50.0f,75.0f);

/*
プレイヤークラス
キャラクタクラスを継承
*/
class CPlayer : public CXCharacter
{
public:
	// プレイヤーが持っているアイテムのリスト
	enum class ItemType
	{
		NONE,		// なにも保持していない

		INVINCIBLE,	// 無敵アイテム
		HEALING,	// 回復アイテム
		ATTACK_UP,	// 攻撃力アップアイテム
		DEFENSE,	// 防御力アップアイテム
	};
	// インベントリを管理
	std::map<ItemType, int> mInventory;
	// アイテムを取得
	void AddItem(ItemType item);
	// 取得したアイテムを判定
	bool HasItem(ItemType item);
	// プレイヤーのアイテムを一括削除
	void ClearItems();
	// アイテムの取得の条件付けを今後行うための処理
	void PickUpItem(ItemType item);
	// 無敵アイテムの使用
	void UseInvincibleItem();
	// 回復薬アイテムの使用
	void UseHealingItem();
	// 攻撃力アップアイテムの使用
	void UseAttackPotion();
	// インベントリから特定のアイテムを削除
	void RemoveItem(ItemType item);

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

	// attack == 攻撃力
	void TakeAttackPotion(int attack) override;


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

	// ジャンプをしたかどうか
	bool IsJumping();
	// 攻撃したかどうか
	bool IsAttack();

	// ステージ1をクリアしたかどうか
	bool IsStage1Clear();
	// ステージ2をクリアしたかどうか
	bool IsStage2Clear();
	// ステージ3をクリアしたかどうか
	bool IsStage3Clear();
	// ステージをクリアしたかどうか
	bool IsStageClear();


	// 敵を見つけたかどうか
	// 使わないかも
	bool IsFoundVanguard();

	// 他のクラスで使っている為publicに置いておく
	// ジャンプ開始1
	void UpdateJumpStart();
	// ジャンプ中1
	void UpdateJump();
	// ジャンプ終了1
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
	// モデル・ポインター・素材関連
	// カメラ関連
	// 状態関連
	// アニメーション関連
	// ベクトル関連
	// キー入力関連
	// 変数関連

	// プレイヤーのインスタンス
	static CPlayer* spInstance;

	//// モデル・ポインター・素材関連 /////////////////////////////////
	
	// 縦のコライダーライン
	CColliderLine* mpColliderLine;
	// 一時的な当たり判定を取るコライダー
	// カプセルコライダーが完成したら変更
	CColliderSphere* mpColliderSphere;
	//ダメージを受けるコライダ
	CColliderSphere* mpDamageCol;
	// 登れるコライダーとの当たり判定を取るコライダー
	CColliderLine* mpClimbCol;

	// マジックソードモデル
	CMajicSword* mpSword;
	
	// HPゲージ
	CUIGauge* mpHpGauge;
	// スタミナゲージ
	CStaminaGauge* mpStaminaGauge;
	// スクリーンアイテム画像
	CScreenItem* mpScreenItem;

	// 剣の振りかざし攻撃時のSE
	CSound* mpSlashSE;
	// 敵の攻撃が当たった時のSE
	CSound* mpHitDamageSE;

	// 火炎放射エフェクト
	CFlamethrower* mpFlamethrower;

	// 登っている壁のポインター
	CClimbWall* mpClimbWall;
	// 登っている金網のポインター
	CWireMeshClimbWall* mpWireWall;
	// 登っている動く金網のポインター
	CWireMeshMoveClimbWall* mpWireMoveWall;

	///////////////////////////////////////////////////////

	//// カメラ関連 ///////////////////////////////////////

	// 死亡時のカメラ
	CCutInDeath* mpCutInDeath;
	// ステージクリア時のカメラ
	CCutInClear* mpCutInClear;
	// リザルト時のカメラ
	CCutInResult* mpCutInResult;

	///////////////////////////////////////////////////////
	

	//// 状態関連 /////////////////////////////////////////
	
	// 準備中の状態
	void UpdateReady();
	// 待機状態
	void UpdateIdle();
	// 停止状態
	void UpdateStop();
	// 移動状態
	void UpdateMove();
	// ダッシュ終了
	void UpdateDashEnd();
	// 攻撃
	void UpdateAttack();
	// 強攻撃
	void UpdateAttackStrong();
	// 攻撃終了待ち
	void UpdateAttackWait();
	// 強攻撃終了待ち
	void UpdateAttackStrongWait();
	// ダッシュアタック
	void UpdateDashAttack();
	// ダッシュアタック終了
	void UpdateDashAttackWait();
	//回避開始
	void UpdateRotate();
	//回避終了待ち
	void UpdateRotateEnd();
	// クリア
	void UpdateClear();
	// クリア終了
	void UpdateClearEnd();
	// リザルト状態
	void UpdateResult();
	// リザルト終了状態
	void UpdateResultEnd();
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
	// ダメージを受ける(オブジェクト)
	void UpdateHitObj();
	// 落下ダメージオブジェクト
	void UpdateFallDamage();
	// 登る状態
	void UpdateClimb();
	// 頂上まで登った
	void UpdateClimbedTop();
	// 金網に登る状態
	void UpdateWireClimb();
	// 金網の頂上に登った状態
	void UpdateWireClimbedTop();
	// 落下状態
	void UpdateFalling();
	// 立ち上がる
	void UpdateStandUp();
	// リザルト前のジャンプ開始
	void UpdateResultJumpStart();
	// リザルト前のジャンプ
	void UpdateResultJump();
	// リザルト前のジャンプ終了
	void UpdateResultJumpEnd();
	// ダッシュジャンプスタート
	void UpdateDashJumpStart();
	// ダッシュジャンプ
	void UpdateDashJump();
	// ダッシュジャンプ終了
	void UpdateDashJumpEnd();

	// プレイヤーの状態
	enum class EState
	{
		eReady,				// 準備中
		eIdle,				// 待機
		eStop,				// 停止
		eClearJump,			// リザルト前のアニメーション
		eAttack,			// 攻撃
		eAttackStrong,		// 強攻撃
		eAttackDash,		// ダッシュアタック
		eAttackWait,		// 攻撃終了待ち
		eAttackStrongWait,	// 強攻撃終了待ち
		eAttackDashWait,	// ダッシュアタック終了待ち
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
		eResult,			// リザルト状態	
		eResultEnd,			// リザルト終了状態
		eDeath,				// 死亡
		eDeathEnd,			// 死亡終了
		eReStart,			// 再起
		eHit,				// ダメージヒット
		eHitBullet,			// 敵の弾ヒット
		eHitSword,			// 敵の剣ヒット
		eHitObj,			// ダメージを受ける(オブジェクト)
		eFallDamege,		// 落下ダメージ
		eClimb,				// 登る状態
		eClimbedTop,		// 頂上まで登った
		eWireClimb,			// 金網に登る状態
		eWireClimbedTop,	// 金網の頂上まで登った
		eFalling,			// 落下状態
		eStandUp,			// 立ち上がる
		eResultJumpStart,	// リザルト前のジャンプ開始
		eResultJump,		// リザルト前のジャンプ
		eResultJumpEnd,		// リザルト前のジャンプ終了
		eDashJumpStart,		// ダッシュジャンプ開始
		eDashJump,			// ダッシュジャンプ
		eDashJumpEnd,		// ダッシュジャンプ終了
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
		eAttackDash,	// ダッシュアタック
		eJumpStart,		// ジャンプ開始
		eJump,			// ジャンプ中
		eJumpEnd,		// ジャンプ終了
		eDashJumpStart,	// ダッシュジャンプ開始
		eDashJump,		// ダッシュジャンプ
		eDashJumpEnd,	// ダッシュジャンプ終了
		eDash,			// ダッシュ
		eDashStop,		// ダッシュ終了
		eRotate,		// 回避
		eGuts,			// ガッツポーズ
		eHit,			// 敵の攻撃Hit
		eHitJ,			// 敵の弾Hit
		eDeath,			// 死亡
		eClimb,			// 壁を登る
		eClimbedTop,	// 壁を登り切った時
		eFalling,		// 落下状態
		eFallingFlat,	// 落下状態から着地した
		eStandUp,		// 立ち上がる

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

	CVector mMoveSpeed;			// 移動速度(X,Z)
	CVector mStartPos;			// プレイヤーの初期位置
	CVector mGroundNormal;		// 設置している地面の法線
	CVector mClimbNormal;		// 登っている壁の法線
	CVector mClimbedStartPos;	// 頂上まで登り切った時の座標
	CVector mClimbedMovedUpPos;	// 頂上まで登り切った後の上方向移動後の座標
	CVector mClimbedMovedPos;	// 頂上まで登り切った後の移動後の座標

	///////////////////////////////////////////////////////


	//// キー入力関連 /////////////////////////////////////

	/// <summary>
	/// キーの入力情報から移動ベクトルを求める
	/// </summary>
	/// <returns></returns>
	CVector CalcMoveVec() const;
	/// <summary>
	/// キーの入力情報から壁移動ベクトルを求める
	/// </summary>
	/// <returns></returns>
	CVector ClimbMoveVec() const;

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
	// 壁のぼり中のスタミナ計測時間
	float mClimbStaminaTime;
	// 最初のダッシュの計測時間
	float mStartDashTime;
	// 武器をしまう時間
	float mWeaponTime;
	// 重力やジャンプによるY軸の移動速度
	float mMoveSpeedY;
	// プレイヤーの大きさ変更計測時間
	float mScaleTime;

	// 接地しているかどうか
	bool mIsGrounded;
	// 無敵かどうか
	bool mInvincible;
	// スタミナが上限値に到達した場合のフラグ
	bool mStaminaDepleted;
	// スタミナが下限値に到達した場合のフラグ
	bool mStaminaLowerLimit;
	// ダメージを与えるフラグ
	bool mDamageObject;
	// ダメージを与えるフラグ(敵)
	bool mDamageEnemy;
	// 回復したか
	bool mHpHit;
	// スラッシュのSEを再生したか
	bool mIsPlayedSlashSE;
	// 攻撃が当たったか
	bool mIsPlayedHitDamageSE;
	// 攻撃中か
	bool mIsAttack;
	// ダッシュ状態か
	bool mDash;
	// 壁を登っているか
	bool mClimb;
	// 登れる壁に触れているか
	bool mClimbWall;
	// 登れる壁の頂上に触れているか
	bool mClimbWallTop;
	// ジャンプをしたか
	bool mIsJumping;
	// 中間地点
	bool mSavePoint;
	// スラッシュエフェクトを鳴らしたか
	bool mIsSpawnedSlashEffect;
	// 落下ダメージを受けたか
	bool mFallDamage;
	// ステージ1をクリアしたか
	bool mStage1Clear;
	// マネージャークラスに伝える用
	bool mIsStage1Clear;
	// ステージ2をクリアしたか
	bool mStage2Clear;
	// マネージャークラスに伝える用
	bool mIsStage2Clear;
	// ステージ3をクリアしたか
	bool mStage3Clear;
	// マネージャークラスに伝える用
	bool mIsStage3Clear;
	// (全てのステージ)クリアしたかマネージャークラスに伝えるよう
	bool mIsStageClear;
	// ダッシュジャンプに移行できるかどうか
	bool mIsDashJump;

	///////////////////////////////////////////////////////
};
