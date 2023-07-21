#ifndef CFIELD_H
#define CFIELD_H

#include "CTask.h"
#include "CModel.h"
#include "CColliderMesh.h"
#include"CCharacter3.h"

//Fieldクラス
class CField :public CCharacter3
{
public:
	//コンストラクタ
	CField();
	//デストラクタ
	~CField();

	//更新処理
	void Update();

private:
	CColliderMesh mColliderMesh;	//Fieldの当たり判定用コライダ
};
#endif