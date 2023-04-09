#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
#include "CCollisionManager.h"

class CCollisionManager;

/*
コライダクラス
衝突判定データ
*/

class CCollider : public CTransform, public CTask {
	friend CCollisionManager;
public:
	//コンストラクタ
	//CCollider(親、親行列、位置、半径)
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	//親ポインタの取得
	CCharacter3* Parent();
	//デストラクタ
	~CCollider();
	//衝突判定
	//Collision(コライダ1、コライダ2)
	//return:true(衝突している)false(衝突していない)
	static bool Collision(CCollider* m, CCollider* o);
	//コライダタイプ
	enum EType {
		ESPHERE,	//弾コライダ
		ETRIANGLE,	//△コライダ
		ELINE,		//線分コライダ
	};
	//デフォルトコンストラクタ
	CCollider();

	//CollisionTriangleLine(△コライダ、線分コライダ、調整値)
	//return:true(衝突している)false(衝突していない)
	//調整値：衝突していない位置まで戻す値
	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* abjust);

	EType Type();

	//描画
	void Render();
protected:
	CCharacter3* mpParent;	//親
	CMatrix* mpMatrix;		//親行列
	float mRadius;			//半径
	EType mType;	//コライダタイプ
	CVector mV[3];
};
#endif