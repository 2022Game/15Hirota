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
	CCollider mColspherSword0;	//剣
	CCollider mColspherSword1;	//剣
	CCollider mColspherSword2;	//剣
};
#endif
