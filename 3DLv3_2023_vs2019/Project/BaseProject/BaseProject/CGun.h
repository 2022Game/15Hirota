#ifndef CGUN_H
#define CGUN_H
#include "CItem.h"
#include "CColliderLine.h"
#include "CModel.h"

class CGun :public CItem
{
	CGun();
	~CGun();

	void Update();
	void Render();

/// <summary>
/// 衝突処理
/// </summary>
/// <param name="self">衝突した自身のコライダー</param>
/// <param name="other">衝突した自身のコライダー</param>
/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

private:

	CModel* mpGun;
	// 攻撃判定用のコライダー
	CColliderLine* mpAttackCol;
};
#endif