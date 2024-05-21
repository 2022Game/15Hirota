#ifndef CNUMBERFIELD_H
#define CNUMBERFIELD_H

#include "CObjectBase.h"
#include "CColliderMesh.h"
#include "CColliderSphere.h"

// 「連続ジャンプステージ」
class CNumberField : public CObjectBase
{
public: 
	CNumberField();
	~CNumberField();

	  // 壁のコライダー取得
	 // CColliderMesh* GetWallCol() const;

	  void Update();
	  void Render();

private:

	CModel* mpStageModel;
	CModel* mpStageSkyModel;

	CColliderMesh* mpFallCol;
};
#endif