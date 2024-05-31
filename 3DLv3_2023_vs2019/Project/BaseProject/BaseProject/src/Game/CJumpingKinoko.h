#ifndef CJUMPINGKINOKO_H
#define CJUMPINGKINOKO_H

#include "CModel.h"
#include "CColliderMesh.h"
#include "CObjectBase.h"

// プレイヤーを跳ねさせるキノコ
class CJumpingKinoko : public CObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="scale">大きさ</param>
	/// <param name="rot">回転</param>
	/// <param name="reactionTag">リアクションタグ</param>
	/// <param name="reactionLayer">リアクションレイヤー</param>
	CJumpingKinoko(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);

	// デストラクタ
	~CJumpingKinoko();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突したときの自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突したときの情報</param>
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

	// 変数関連
	// 状態内のステップ
	int mStateStep;
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