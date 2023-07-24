#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy :public CXCharacter {
public:
	CXEnemy();

	void Init(CModelX *model);
private:
	//ƒRƒ‰ƒCƒ_éŒ¾
	CCollider mColSpherBody;	//‘Ì
	CCollider mColSpherHead;	//“ª
	CCollider mColspherSword;	//Œ•
};
#endif
