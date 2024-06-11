#ifndef CSEESAW_H
#define CSEESAW_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

class CModel;

// シーソー
class CSeesaw : public CObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="scale">大きさ</param>
	/// <param name="rot">回転</param>
	/// <param name="reactionTag">触れると反応するオブジェクト</param>
	/// <param name="reactionLayer">触れると反応するレイヤー</param>
	CSeesaw(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);

	// デストラクタ
	~CSeesaw();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した相手のコライダー</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
	/// <summary>
	/// レイとの衝突判定
	/// </summary>
	/// <param name="start">レイの開始位置</param>
	/// <param name="end">レイの終了位置</param>
	/// <param name="hit">衝突位置返却用</param>
	/// <returns></returns>
	bool CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit) override;

	// 更新
	void Update() override;

	// 描画
	void Render() override;

private:

	// モデル・素材関連
	// シーソーモデル
	CModel* mpSeesawModel;
	// シーソーコライダー
	CColliderMesh* mpSeesawCol;

	// 状態関連
	// シーソーの状態
	enum class EState
	{
		eIdle,	// 待機状態
	};
	// 状態を切り替える
	void ChangeState(EState state);
	// 待機状態の更新処理
	void UpdateIdle();
	// 現在の状態
	EState mState;

	// ベクトル関連
	// 位置を設定する
	CVector mStartPos;
	// 初期回転値
	CQuaternion mDeafaultRot;

	// 変数関連
	// 状態内のステップ
	int mStateStep;
	// 回転した角度を保持する変数
	float mRotationAngle;
	// 回転開始時の角度
	float mRotateStartAngle;
	// 回転終了時の角度
	float mRotateEndAngle;
	// 経過時間計測用
	float mElapsedTime;
	// プレイヤーがシーソー上のどちらに触れているか
	float mHitDir;
	// プレイヤーがシーソーに触れているかどうか
	bool mIsHitCol;

	// 触れた時に反応するオブジェクトのタグ
	ETag mReactionTag;
	// 触れた時に反応するレイヤー
	ELayer mReactionLayer;
};
#endif