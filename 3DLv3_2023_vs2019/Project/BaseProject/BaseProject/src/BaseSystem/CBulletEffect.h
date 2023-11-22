#ifndef CBulletEffectEFFECT_H
#define CBulletEffectEFFECT_H

#include "CObjectBase.h"
#include "CEnemyWeapon.h"
#include "CEffect.h"
#include "CBillBoard.h"

class CBulletEffect :public CBillBoard
{
public:
	CBulletEffect();
	~CBulletEffect();

	//CMatrix Matrix() const override;

	void Update();
	void Render();
private:
	// 弾丸の移動距離
	float mMoveDistance;
	// 弾のエフェクト
	static CEffect* mpBulletEffect;

	const CMatrix* mpAttachMtx;

	CVector mPos;
};
#endif