#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy :public CXCharacter {
public:
	CXEnemy();

	void Init(CModelX *model);
private:
	//�R���C�_�錾
	CCollider mColSpherBody;	//��
	CCollider mColSpherHead;	//��
	CCollider mColspherSword;	//��
};
#endif
