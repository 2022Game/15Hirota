#ifndef CCLIMBWALL_H
#define CCLIMBWALL_H
#include "CObjectBase.h"
#include "CColliderMesh.h"

// 登れる壁
class CClimbWall : public CObjectBase
{
public:
	// コンストラクタ
	CClimbWall();
	// デストラクタ
	~CClimbWall();

	// 更新
	void Update() override;
	// 描画
	void Render() override;

private:
	CModel* mpWallModel;	// 登れる壁のモデルデータ
	CColliderMesh* mpWallCol;	// 登れる壁のコライダー
};
#endif