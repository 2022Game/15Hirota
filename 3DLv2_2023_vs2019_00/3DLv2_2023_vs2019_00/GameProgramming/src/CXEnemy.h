#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy :public CXCharacter {
public:
	CXEnemy();

	void Init(CModelX *model);

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//�X�V����
	void Update();
private:
	//�R���C�_�錾
	CCollider mColSpherBody;	//��
	CCollider mColSpherHead;	//��
	CCollider mColspherSword0;	//��
	CCollider mColspherSword1;	//��
	CCollider mColspherSword2;	//��
};
#endif
