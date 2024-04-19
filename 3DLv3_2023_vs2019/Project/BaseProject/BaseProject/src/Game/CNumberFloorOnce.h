#ifndef CNUMBERFLOORONCE_H
#define CNUMBERFLOORONCE_H

#include "CRideableObject.h"
#include "CModel.h"
#include "CColliderMesh.h"

// 一回で消滅する床クラス
class CNumberFloorOnce : public CRideableObject
{
public:

	CNumberFloorOnce(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CNumberFloorOnce();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// 更新
	void Update();
	// 描画
	void Render();

private:
	// モデル・素材関連
	CModel* mpModel;
	// 1回で消滅する床のモデル
	CModel* mpNumberOnce;
	// 1回で消滅する床のモデル
	CColliderMesh* mpColliderMesh;

	
	// 待機状態
	// 1回で消滅する床のモデル
	enum class EState
	{
		Idle,
		Waiting,
		Falling,
	};
	void ChangeState(EState state);
	void UpdateIdle();
	void UpdateWaiting();
	void UpdateFalling();
	EState mState;


	// ベクトル関連
	// 移動速度
	CVector mMoveSpeed;
	// 初期位置
	CVector mStartPos;

	// 変数関連
	// 状態内のステップ
	int mStateStep;
	// 点滅回数
	int mSwitchCount;
	// 落下状態のステップ
	int mFallingSwitch;
	// フェード時間
	float mFadeTime;
	// 待ち時間
	float mWaitTime;
	// 計測時間
	float mElapsedTime;
	// 衝突しているか
	bool mIsCollision;
	// 触れた時に反応するオブジェクトのタグ
	ETag mReactionTag;
	// 触れた時に反応するオブジェクトのレイヤー
	ELayer mReactionLayer;
};
#endif