#ifndef CJUMPINGKINOKOUPDOWN_H
#define CJUMPINGKINOKOUPDOWN_H

#include "CModel.h"
#include "CColliderMesh.h"
#include "CObjectBase.h"

// プレイヤーを跳ねさせるキノコ(上下)
class CJumpingKinokoUpDown : public CObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">大きさ</param>
	/// <param name="move">移動距離</param>
	/// <param name="moveTime">移動時間</param>
	CJumpingKinokoUpDown(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime, ETag reactionTag, ELayer reactionLayer);
	// デストラクタ
	~CJumpingKinokoUpDown();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">自身</param>
	/// <param name="other">相手</param>
	/// <param name="hit">衝突情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
	
	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;

private:
	// モデル・素材関連
	// 跳ねるキノコモデル
	CModel* mpKinoko;
	// 跳ねるキノコモデルのコライダー
	CColliderMesh* mpColliderMesh;

	// 状態関連
	// 跳ねるキノコの状態
	enum class EState
	{
		eIdle,	// 待機状態
		eBounce,// 跳ねさせる状態
	};
	// 待機状態を切り替える
	void ChangeState(EState state);
	// 待機状態の更新処理
	void UpdateIdle();
	// 跳ねさせる状態の湖心処理
	void UpdateBounce();
	// 現在の状態
	EState mState;

	// ベクトル関連
	// 初期の大きさ
	CVector mStartScale;
	// 縮む大きさ
	CVector mShrinkScale;
	// 移動距離
	CVector mMoveVec;
	// 元の位置
	CVector mDefaultPos;

	// 変数関連
	// 状態内のステップ
	int mStateStep;
	// 経過時間計測用
	float mElapsedTime;
	// 移動時間計測用
	float mMoveElapsedTime;
	// 移動時間
	float mMoveTime;
	// 衝突しているか
	bool mIsCollisionPlayer;

	// 触れた時に反応するオブジェクトのタグ
	ETag mReactionTag;
	// 触れた時に反応するレイヤー
	ELayer mReactionLayer;
};
#endif