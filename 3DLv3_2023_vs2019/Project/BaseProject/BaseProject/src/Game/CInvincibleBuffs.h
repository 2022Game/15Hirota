#ifndef CINVINCIBLEBUFFS_H
#define CINVINCIBLEBUFFS_H

#include "CObjectBase.h"
#include "CModel.h"

// 無敵エフェクト
class CInvincibleBuffs : public CObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">effectを発生させたオブジェクト</param>
	/// <param name="pos">発生位置</param>
	/// <param name="dir">移動方向</param>
	/// <param name="speed">移動速度</param>
	/// <param name="dist">移動したら消える距離</param>
	CInvincibleBuffs(CObjectBase* owner, const CVector& pos, const CVector& dir, float speed, float dist);
	// デストラクタ
	~CInvincibleBuffs();

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;

private:
	CObjectBase* mpOwner;	// effectの持ち主
	CModel* mpModel;			// effectのモデル
	CVector mMoveSpeed;		// 移動速度
	float mKillMoveDist;	// 移動したら消える距離
	float mMovedDist;		// 現在移動した距離
};
#endif