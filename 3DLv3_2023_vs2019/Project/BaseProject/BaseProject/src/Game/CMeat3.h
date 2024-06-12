#ifndef CMEAT3_H
#define CMEAT3_H

#include "CObjectBase.h"
#include "CMeatObjectBase.h"
#include "CColliderSphere.h"
#include "CModel.h"

// 骨付き肉クラス
class CMeat3 : public CMeatObjectBase
{
public:
	CMeat3(const CVector& pos, const CVector& rot, const CVector& scale);
	~CMeat3();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	//インスタンスのポインタの取得
	static CMeat3* Instance();

	bool IsMeat3() const;

	void Update() override;
	void Render() override;

private:
	// インスタンス
	static CMeat3* spInstance;

	// モデル関連
	// 肉のモデル
	CModel* mpMeat;
	// 肉のコライダーモデル
	CColliderSphere* mpMeatSphere;

	// 状態関連
	// 肉の状態
	enum class EState
	{
		eIdle,	// 待機状態
		eGet,	// 取得状態
	};
	EState mState;
	// 状態を変化させる処理
	void ChangeState(EState state);
	// 待機状態更新処理
	void UpdateIdle();
	// 取得状態更新処理
	void UpdateGet();

	// ベクトル関連
	// 取得開始時のアイテムの座標
	CVector mGetStartPos;
	// 取得時のアイテムの移動先の座標
	CVector mGetTargetPos;
	// 移動方向
	CVector mMoveVector;
	// 見る方向
	CVector mTargetDir;
	CVector mMoveSpeed;
	CVector mStartPos;
	CVector mTotalMovement;

	CVector2 mPosition;

	// 変数
	// 状態内のステップ
	int mStateStep;
	// 計測時間
	float mElapsedTime;
	// 取得時のカメラからの距離
	float mGetCameraDist;
	// 三つ目の肉
	bool mMeat3;
	// 床に接地しているか
	bool mIsGround;
};
#endif