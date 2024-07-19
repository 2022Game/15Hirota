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
	// 更新処理
	void Update() override; 
	// 描画処理
	void Render() override;

private:

	CModel* mpStageModel;
	CModel* mpStageSkyModel;

	CColliderMesh* mpFallCol;
};
#endif