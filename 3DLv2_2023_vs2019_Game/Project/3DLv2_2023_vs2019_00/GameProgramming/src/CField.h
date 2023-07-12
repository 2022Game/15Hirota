#ifndef CFIELD_H
#define CFIELD_H

#include "CTask.h"
#include "CModel.h"
#include "CColliderMesh.h"

//Fieldクラス
class CField :public CTask
{
public:
	//コンストラクタ
	CField();
	//デストラクタ
	~CField();

	//更新処理
	void Update();
	//描画処理
	void Render();

private:
	CModel* mModel;	//Fieldのモデルデータ	
	CColliderMesh mColliderMesh;	//Fieldの当たり判定用コライダ
};
#endif