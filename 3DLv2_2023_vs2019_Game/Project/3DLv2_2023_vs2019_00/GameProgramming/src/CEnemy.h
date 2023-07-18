#ifndef CENEMY_H
#define CENEMY_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"

/*
エネミークラス
キャラクタクラスを継承
*/
class CEnemy : public CCharacter3
{
public:
	//コンストラクタ
	CEnemy();
	//デストラクタ
	virtual ~CEnemy();
};

#endif
