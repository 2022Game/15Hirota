#ifndef CBLUEMEDAL_H
#define CBLUEMEDAL_H

#include "CObjectBase.h"
#include "CMedalObjectBase.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CModel.h"
class CSoud;
class CPlayer;

// ブルーメダルアイテム
class CBlueMedal : public CMedalObjectBase
{
public:
	CBlueMedal(const CVector& pos, const CVector& scale);
	~CBlueMedal();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	static void SetScore(int score);
	static int GetScore();

	// 更新処理
	void Update();
	// 描画処理
	void Render();

private:
	static int sScore;

	CModel* mpBlueMedel;
	CColliderSphere* mpBlueMedalCol;

	// 移動速度
	CVector mMoveSpeed;

	bool mIsGround;
};
#endif