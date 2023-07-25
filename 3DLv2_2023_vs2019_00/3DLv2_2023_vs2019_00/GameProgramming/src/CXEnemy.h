#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy :public CXCharacter {
public:
	CXEnemy();

	void Init(CModelX *model);

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//更新処理
	void Update();
private:
	//コライダ宣言
	CCollider mColSpherBody;	//体
	CCollider mColSpherHead;	//頭
	CCollider mColspherSword;	//剣
};
#endif
