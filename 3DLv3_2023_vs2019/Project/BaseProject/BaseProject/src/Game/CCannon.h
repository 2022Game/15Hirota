#ifndef CCANNON_H
#define CCANNON_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderSphere.h"

class CPlayer;

// 大砲クラス
class CCannon : public CObjectBase
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="scale">大きさ</param>
	/// <param name="rot">回転</param>
	CCannon(const CVector& pos, const CVector& scale, const CVector& rot);
	// デストラクタ
	~CCannon();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した自身のコライダー</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// 更新処理
	void Update();
	// 描画処理
	void Render();

private:

	// プレイヤーを見つける処理
	bool IsFoundPlayer() const;

	// 大砲モデル
	CModel* mpCannon;
	// 大砲のコライダー
	//CColliderMesh* mpColliderMesh;

	// 次に打つまでの時間計測
	float mFireTime;
	// 打てるかどうか
	bool mFire;

};

class CCannonFoundations : public CObjectBase
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="scale">大きさ</param>
	/// <param name="rot">回転</param>
	CCannonFoundations(const CVector& pos, const CVector& scale, const CVector& rot);
	// デストラクタ
	~CCannonFoundations();

	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="self">衝突した自身のコライダー</param>
	/// <param name="other">衝突した自身のコライダー</param>
	/// <param name="hit">衝突したときの情報</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// 更新処理
	void Update();
	// 描画処理
	void Render();

private:

	// 大砲の土台モデル
	CModel* mpCannonFoundations;
	// 大砲のコライダー
	//CColliderMesh* mpColliderMesh;

};
#endif