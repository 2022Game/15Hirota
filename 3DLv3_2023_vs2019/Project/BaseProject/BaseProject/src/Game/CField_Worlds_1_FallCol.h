#ifndef CFIELD_WORLDS_1_FALLCOL
#define CFIELD_WORLDS_1_FALLCOL

#include "CObjectBase.h"
#include "CColliderMesh.h"

// 「連続ジャンプステージ」の落下コライダー
class CField_Worlds_1_FallCol : public CObjectBase
{
public:
	CField_Worlds_1_FallCol();
	~CField_Worlds_1_FallCol();

	void Update() override;
	void Render() override;
private:
	CColliderMesh* mpFallCol;
};
#endif