#ifndef CJUMPINGOBJECT_H
#define CJUMPINGOBJECT_H

#include "CModel.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"
#include "CJumpingBase.h"

class CJumpingObject : public CJumpingBase
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


	void Update();
	void Render();

private:
	// 跳ねる床の状態
	enum class EState
	{
		Idle,		// 待機状態
		Bounce,		// 跳ねる状態
	};
	// 状態を切り替える
	void ChangeState(EState state);
	// 待機状態の更新処理
	void UpdateIdle();
	// 現れている状態の更新処理
	void UpdateBounce();

	EState mState;	// 現在の状態
	int mStateStep;	// 状態内のステップ

	ETag mReactionTag;	// 触れた時に反応するオブジェクトのタグ
	ELayer mReactionLayer;	// 触れた時に反応するレイヤー

	float mFadeTime;	// フェード時間
	float mWaitTime;	// 待ち時間
	bool mIsCollision;	// 衝突しているか


	CModel* mpModel;

	CColliderMesh* mpColliderMesh;
};
#endif