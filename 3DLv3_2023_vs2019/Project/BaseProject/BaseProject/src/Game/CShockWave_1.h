#ifndef CSHOCKWAVE_1
#define CSHOCKWAVE_1

#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderCapsule.h"

// 地面の衝撃波クラス
class CShockWave_1 : public CObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">エフェクトを発生させたオブジェクト</param>
	/// <param name="pos">発生位置</param>
	/// <param name="dir">移動方向</param>
	/// <param name="speed">移動速度</param>
	/// <param name="dist">移動したら消える距離</param>
	CShockWave_1(CObjectBase* owner, const CVector& pos, const CVector& startscale, const CVector& endscale, 
		const CVector& dir, float speed, float dist);
	// コンストラクタ
	~CShockWave_1();

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;

private:
	// エフェクトの持ち主
	CObjectBase* mpOwner;
	// エフェクトのモデル
	CModel* mpModel;
	// モデルのコライダー1
	CColliderCapsule* mpCapsule1;
	// モデルのコライダー2
	CColliderCapsule* mpCapsule2;
	// 移動速度
	CVector mMoveSpeed;
	// 移動したら消える距離
	float mKillMoveDist;
	// 現在移動した距離
	float mMovedDist;

	// 時間計測用
	float mElapsedTime;
	// 初期の大きさ
	CVector mStartScale;
	// 最大の大きさ
	CVector mEndScale;
	// 大きくなる時間計測用
	float mScaleTime;
};
#endif