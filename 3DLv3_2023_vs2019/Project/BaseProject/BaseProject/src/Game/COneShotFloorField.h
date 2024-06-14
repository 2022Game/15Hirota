#ifndef CONESHOTFLOORFIELD_H
#define CONESHOTFLOORFIELD_H

#include "CObjectBase.h"
#include "CColliderMesh.h"
#include "CColliderSphere.h"

// 「連続ジャンプステージ」
class COneShotFloorField : public CObjectBase
{
public: 
	COneShotFloorField();
	~COneShotFloorField();

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