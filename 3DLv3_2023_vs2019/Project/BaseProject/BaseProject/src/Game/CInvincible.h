#ifndef CINVINCIBLE_H
#define CINVINCIBLE_H

#include "CObjectBase.h"
#include "CItemObjectBase.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CModel.h"

// 無敵アイテム
class CInvincible : public CItemObjectBase
{
public:
	CInvincible();
	~CInvincible();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突したときの情報</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// 移動処理
	// 手前
	void MoveFront();
	// 奥
	void MoveBack();
	// 右
	void MoveLight();
	// 左
	void MoveReft();

	// 更新処理
	void Update();
	// 描画処理
	void Render();


	// 無敵オブジェの行列を取得
	//CMatrix Matrix() const override;

private:
	//// モデル関連/////////////////////////////
	
	// 無敵アイテムのモデル
	CModel* mpRecoverModel;
	// 無敵アイテムのコライダー
	CColliderSphere* mpRecoverCol;

	////////////////////////////////////////////


	//// ベクトル関連 //////////////////////////

	// 移動方向
	CVector mMoveVector;
	// 移動速度
	CVector mMoveSpeed;
	// 見る方向
	CVector mTargetDir;

	/////////////////////////////////////////////


	//// 変数関連 ///////////////////////////////

	// カウント
	int mSwitchCounter;
	// 計測時間処理
	float mElapsedTime;
	// 床に接地しているか
	bool mIsGround;
	// 無敵になったかどうか
	bool mRecoveryUsed;

	/////////////////////////////////////////////
};
#endif