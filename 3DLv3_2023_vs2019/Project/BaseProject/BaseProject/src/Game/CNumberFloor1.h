//#ifndef CNUMBERFLOOR1_H
//#define CNUMBERFLOOR1_H
//
//#include "CRideableObject.h"
//#include "CModel.h"
//#include "CColliderMesh.h"
//
//// 回数で落ちる床(3回)クラス
//class CNumberFloor1 : public CRideableObject
//{
//public:
//	/// <summary>
//	/// コンストラクタ
//	/// </summary>
//	/// <param name="pos">初期位置</param>
//	/// <param name="scale">スケール値</param>
//	/// <param name="reactionTag">触れると反応するオブジェクトのタグ</param>
//	/// <param name="reactionLayer">触れると反応するオブジェクトのレイヤー</param>
//	CNumberFloor1(const CVector& pos, const CVector& scale,
//		ETag reactionTag, ELayer reactionLayer);
//
//	// デストラクタ
//	~CNumberFloor1();
//
//	/// <summary>
//	/// 衝突処理
//	/// </summary>
//	/// <param name="self">衝突した自身のコライダー</param>
//	/// <param name="other">衝突した相手のコライダー</param>
//	/// <param name="hit">衝突したときの情報</param>
//	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
//
//	// 更新
//	void Update();
//	// 描画
//	void Render();
//
//private:
//	// モデル・素材関連
//	// 回数で落ちる床(3回)のモデル
//	CModel* mpModel;
//	// 回数で落ちる床(3回)のコライダー
//	CColliderMesh* mpColliderMesh;
//
//
//	// 状態関連
//	// 回数で落ちる床(3回)の状態
//	enum class EState
//	{
//		Idle,		// 待機状態
//		Waiting,	// 待ち状態
//		Falling,	// 落下状態
//	};
//	// 状態を切り替える
//	void ChangeState(EState state);
//	// 待機状態の更新処理
//	void UpdateIdle();
//	// 待ち状態の更新処理
//	void UpdateWaiting();
//	// 落下状態の更新処理
//	void UpdateFalling();
//	// 現在の状態
//	EState mState;
//
//	// 変数関連
//	// 状態内のステップ
//	int mStateStep;
//	// 回数の監視
//	int mNumberStep;
//	// フェード時間
//	float mFadeTime;
//	// 待ち時間
//	float mWaitTime;
//	// 触れた時に反応するオブジェクトのタグ
//	ETag mReactionTag;
//	// 触れた時に反応するオブジェクトのレイヤー
//	ELayer mReactionLayer;
//};
//#endif