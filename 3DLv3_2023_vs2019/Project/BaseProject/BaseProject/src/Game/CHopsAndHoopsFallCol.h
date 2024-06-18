#ifndef CHOPSANDHOOPSFALLCOL_H
#define CHOPSANDHOOPSFALLCOL_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

// 「ホップ＆フープス」の落下コライダー
class CHopsAndHoopsFallCol : public CObjectBase
{
public:
	CHopsAndHoopsFallCol();
	~CHopsAndHoopsFallCol();

	void Update() override;
	void Render() override;
private:
	CColliderMesh* mpFallCol;
};
#endif