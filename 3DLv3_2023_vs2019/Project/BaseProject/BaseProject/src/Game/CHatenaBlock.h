#ifndef CHATENABLOCK_H
#define CHATENABLOCK_H

#include "CRideableObject.h"
#include "CModel.h"
#include "CColliderSphere.h"

class CRecoveryObject;
class CInvincible;

// ハテナブロック
class CHatenaBlock : public CRideableObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="scale">スケール</param>
	/// <param name="reactionTag">反応するオブジェクトタグ</param>
	/// <param name="reactionLayer">反応するオブジェクトレイヤー</param>
	CHatenaBlock(const CVector& pos, const CVector& scale,
		ETag reactionTag, ELayer reactionLayer);

	// デストラクタ
	~CHatenaBlock();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">自身</param>
	/// <param name="other">相手</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	void SetStartPosition(const CVector& pos);

	// 更新
	void Update() override;

	// 描画
	void Render();

private:
	// ハテナブロックの状態
	enum class EState
	{
		Idle,	// 待機状態
		Hit,	// プレイヤーが触れた状態
		After,	// 当たった後
	};
	// 状態を切り替える
	void ChangeState(EState state);
	// 待機状態の更新処理
	void UpdateIdle();
	// 当たった時の更新処理
	void UpdateHit();
	// 当たった後の更新処理
	void UpdateAfter();

	CModel* mpModel;		// ハテナブロックのモデル
	CModel* mpModelAfter;	// ハテナブロック使用後モデル
	CColliderSphere* mpColliderSphere;	// ハテナブロックのコライダー

	EState mState;	// 現在の状態
	int mStateStep;	// 状態内のステップ

	ETag mReactionTag;		// 触れた時に反応するオブジェクトのタグ
	ELayer mReactionLayer;	// 触れた時に反応するオブジェクトのレイヤー

	float mFadeTime;	// フェード時間
	float mWaitTime;	// 待ち時間
	bool mIsCollision;	// 衝突しているか

	CVector mMoveSpeed;
	CVector mStartPos;

	CRecoveryObject* mpHeart;
	CInvincible* mpStar;
};
#endif