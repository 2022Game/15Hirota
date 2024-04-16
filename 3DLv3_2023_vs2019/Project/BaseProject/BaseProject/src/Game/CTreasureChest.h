#ifndef CTREASURECHEST_H
#define CTREASURECHEST_H
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"

class CTreasureChest : public CObjectBase
{
public:
	CTreasureChest(const CVector& pos,const CVector&scale,const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CTreasureChest();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	void Update() override;
	void Render() override;
private:
	enum class EState
	{
		Idle,
		GetItem,
	};
	void UpdateIdle();
	void UpdateGetItem();
	EState mState;
	void ChangeState(EState state);


	CModel* mpChest;
	CColliderSphere* mpChestSphere;
	CColliderMesh* mpChestCol;


	// ベクトル関連
	// 宝箱モデルの初期位置
	CVector mStartPos;

	// 変数関連
	// 状態内のステップ
	int mStateStep;
	// 待ち時間
	float mWaitTime;
	ETag mReactionTag;
	ELayer mReactionLayer;

};

class CTreasureChestTwo : public CObjectBase
{
public:
	CTreasureChestTwo(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CTreasureChestTwo();

	void Update();
	void Render();

private:
	enum class EState
	{
		Idle,
		Two,
	};
	void UpdateIdle();
	void UpdateTwo();
	EState mState;
	void ChangeState(EState state);


	CModel* mpChestTwo;
	CColliderSphere* mpChestSphere;
	CColliderMesh* mpChestTwoCol;


	// ベクトル関連
	// 宝箱モデルの初期位置
	CVector mStartPos;

	// 変数関連
	// 状態内のステップ
	int mStateStep;
	// 待ち時間
	float mWaitTime;
	// 回転開始時の角度
	float mRotateStartAngle;
	// 回転終了時の角度
	float mRotateEndAngle;
	ETag mReactionTag;
	ELayer mReactionLayer;
};
#endif