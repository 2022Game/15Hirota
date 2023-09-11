#ifndef CXPLAYER_H
#define CXCPLAYER_H

#include "CXCharacter.h"
#include "CInput.h"
#include "CCollider.h"
#include "CActionCamera.h"

class CXPlayer :public CXCharacter {
public:
	//更新処理
	void Update();
	//デフォルトコンストラクタ
	CXPlayer();

	void Init(CModelX* model);
private:
	CInput mInput;
	//コライダ宣言
	CCollider mColSpherBody;	//体
	CCollider mColSpherHead;	//頭
	CCollider mColspherSword;	//剣
};
#endif