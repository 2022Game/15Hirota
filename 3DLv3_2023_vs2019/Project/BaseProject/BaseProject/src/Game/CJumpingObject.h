#ifndef CJUMPINGOBJECT_H
#define CJUMPINGOBJECT_H

#include "CModel.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"
#include "CObjectBase.h"

// プレイヤーを跳ねさせる床
class CJumpingObject : public CObjectBase
{
public:
	// コンストラクタ
	CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	// デストラクタ
	~CJumpingObject();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// 更新処理
	void Update();
	// 描画処理
	void Render();

private:
	// モデル・素材関連
	// 跳ねる床モデル
	CModel* mpModel;
	// 跳ねる床モデルのコライダー
	CColliderMesh* mpColliderMesh;


	// 状態関連
	// 跳ねさせる床の状態
	enum class EState
	{
		eIdle,			// 待機状態
		eBounce,		// 跳ねさせる状態
	};
	// 状態を切り替える
	void ChangeState(EState state);
	// 待機状態の更新処理
	void UpdateIdle();
	// 跳ねさせる状態の更新処理
	void UpdateBounce();
	// 現在の状態
	EState mState;

	// ベクトル関連
	// 初期の大きさ
	CVector mStartScale;
	// 縮む大きさ
	CVector mShrinkScale;


	// 変数関連
	// 状態内のステップ
	int mStateStep;
	// フェード時間
	float mFadeTime;
	// 待ち時間
	float mWaitTime;
	// 経過時間計測用
	float mElapsedTime;
	// 衝突しているか
	bool mIsCollisionPlayer;

	// 触れた時に反応するオブジェクトのタグ
	ETag mReactionTag;
	// 触れた時に反応するレイヤー
	ELayer mReactionLayer;
};
#endif