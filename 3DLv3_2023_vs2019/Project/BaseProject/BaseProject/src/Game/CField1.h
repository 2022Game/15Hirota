#ifndef CFIELD1_H
#define CFIELD1_H
#include "CObjectBase.h"
#include "CColliderMesh.h"

class CField1 : public CObjectBase
{
public:
	// コンストラクタ
	CField1();
	// デストラクタ
	~CField1();

	// 壁のコライダー取得
	CColliderMesh* GetWallCol() const;

	// 更新処理
	void Update();
	// 描画処理
	void Render();

private:
	void CreateFieldObjects();

	CModel* mpModel;
	CModel* mpTree;
	CModel* mpClimb;
	CColliderMesh* mpColliderMesh;
	CColliderMesh* mpColliderMeshClimb;
	CColliderMesh* mpWallCol;
	//CColliderMesh* mpEnemyWallCol;
};
#endif