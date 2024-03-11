#ifndef CCLIMBWALL_H
#define CCLIMBWALL_H
#include "CObjectBase.h"
#include "CColliderMesh.h"

// 登れる壁
class CClimbWall : public CObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="climbName">登れる壁のモデルデータのリソース名</param>
	/// <param name="TopName">登れる壁の頂上のモデルのデータのリソース名</param>
	/// <param name="moveVec">頂上へ上った時の移動量</param>
	CClimbWall(std::string climbName, std::string TopName, const CVector& moveVec);
	// デストラクタ
	~CClimbWall();

	// 頂上へ上り切った時の移動量を取得
	const CVector& GetClimbedMoveVec() const;

	// 更新
	void Update() override;
	// 描画
	void Render() override;

private:
	CModel* mpWallModel;		// 登れる壁のモデルデータ
	CColliderMesh* mpWallCol;	// 登れる壁のコライダー
	CColliderMesh* mpWallTopCol;// 登れる壁の頂上コライダー
	CVector mClimbedMoveVec;	// 頂上へ上り切った時の移動量
};
#endif