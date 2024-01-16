#ifndef CINVINCIBLE_H
#define CINVINCIBLE_H

#include "CObjectBase.h"
#include "CItemObjectBase.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CModel.h"

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

	//// 回復開始
	//void RecoverStart();

	//void RecoverEnd();

	// 無敵オブジェの行列を取得
	//CMatrix Matrix() const override;

	void Update();
	void Render();

	void Move();	// 手前
	void MoveZ();	// 奥
	void MoveX();	// 右
	void MoveY();	// 左

private:
	CModel* mpRecoverModel;
	// 無敵オブジェのコライダー
	CColliderSphere* mpRecoverCol;

	CVector moveVector;
	CVector mMoveSpeed;
	CVector mTargetDir;

	float mElapsedTime;

	bool mIsGround;

	int mSwitchCounter;

	bool mIsEnabled;

	bool mRecoveryUsed;
};
#endif