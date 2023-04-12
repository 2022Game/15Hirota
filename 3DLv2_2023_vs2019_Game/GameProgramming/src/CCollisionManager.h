#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"
#include "CCollider.h"

//衝突処理派によりはなれているコライダは衝突処理しない
#define COLLISIONRANGE 30

class CCollisionManager : public CTaskManager
{
public:
	//インスタンスの取得
	static CCollisionManager* Instance();
	//衝突処理
	void Collision();
	void Collision(CCollider* c, int range);
private:
	//マネージャのインスタンス
	static CCollisionManager* mpInstance;
};

#endif
