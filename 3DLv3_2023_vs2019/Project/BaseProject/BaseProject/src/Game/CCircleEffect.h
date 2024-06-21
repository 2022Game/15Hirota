#ifndef CCIRCLEEFFECT_H
#define CCIRCLEEFFECT_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CWeapon.h"

// サークル状のエフェクト
class CCircleEffect : public CWeapon
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="angle"></param>
	/// <param name="dist"></param>
	CCircleEffect(float angle, float dist);
	~CCircleEffect();

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;
private:
	// エフェクトのモデル
	CModel* mpModel;
	// 経過時間観測用
	float mElapsedTime;
	float mAngle;
	float mDistance;
};
#endif