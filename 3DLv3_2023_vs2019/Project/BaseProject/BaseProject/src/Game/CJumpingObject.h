#ifndef CJUMPINGOBJECT_H
#define CJUMPINGOBJECT_H

#include "CModel.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"
#include "CRideableObject.h"

// 跳ねさせる床クラス
class CJumpingObject : public CRideableObject
{
public:
	CJumpingObject(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
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
	CModel* mpModel;
	// 跳ねるモデルのコライダー
	CColliderMesh* mpColliderMesh;


	// 状態関連
	// 跳ねさせる床の状態
	enum class EState
	{
		Idle,		// 待機状態
		Bounce,		// 跳ねさせる状態
	};
	// 状態を切り替える
	void ChangeState(EState state);
	// 待機状態の更新処理
	void UpdateIdle();
	// 跳ねさせる状態の更新処理
	void UpdateBounce();
	EState mState;	// 現在の状態


	// 変数関連
	// 状態内のステップ
	int mStateStep;
	// フェード時間
	float mFadeTime;
	// 待ち時間
	float mWaitTime;
	// 衝突しているか
	bool mIsCollision;
	// 触れた時に反応するオブジェクトのタグ
	ETag mReactionTag;
	// 触れた時に反応するレイヤー
	ELayer mReactionLayer;
};
#endif