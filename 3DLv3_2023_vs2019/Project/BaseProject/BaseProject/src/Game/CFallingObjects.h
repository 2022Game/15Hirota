#ifndef CFALLINGOBJECTS_H
#define CFALLINGOBJECTS_H


#include "CRideableObject.h"
#include "CModel.h"
#include "CColliderMesh.h"

// 消える床
class CFallingObjects : public CRideableObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">初期位置</param>
	/// <param name="scale">床のスケール値</param>
	/// <param name="reactionTag">触れると反応するオブジェクトのタグ</param>
	/// <param name="reactionLayer">触れると反応するコライダーのレイヤー</param>
	CFallingObjects(const CVector& pos, const CVector& scale,
		ETag reactionTag, ELayer reactionLayer);

	// デストラクタ
	~CFallingObjects();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	void SetStartPosition(const CVector& pos);

	// 更新
	void Update() override;

	// 描画
	void Render() override;

private:
	// 消える床の状態
	enum class EState
	{
		Idle,		// 待機状態
		Falling,	// 落下状態
	};
	// 状態を切り替える
	void ChangeState(EState state);
	// 待機状態の更新処理
	void UpdateIdle();
	// 現れている状態の更新処理
	void UpdateFalling();

	CModel* mpModel;	// 消える床のモデル
	CColliderMesh* mpColliderMesh;	// 消える床のコライダー

	EState mState;	// 現在の状態
	int mStateStep;	// 状態内のステップ

	ETag mReactionTag;	// 触れた時に反応するオブジェクトのタグ
	ELayer mReactionLayer;	// 触れた時に反応するレイヤー

	float mFadeTime;	// フェード時間
	float mWaitTime;	// 待ち時間
	bool mIsCollision;	// 衝突しているか

	CVector mMoveSpeed;
	CVector mPosition;
	CVector mStartPos;
};
#endif