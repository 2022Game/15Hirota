#ifndef CALIEN1_H
#define CALIEN1_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
//コライダクラスのインクルード
#include "CCollider.h"
/*
エネミークラス
キャラクタクラスを継承
*/
class CAlien1 : public CCharacter3 {
public:
	//コンストラクタ
	CAlien1();
	//CEnemy3(位置, 回転, 拡縮)
	CAlien1(const CVector& position, const CVector& rotation,
		const CVector& scale);
	//更新処理
	void Update();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void Collision();
private:
	CVector mPoint;	//目標地点
	int mHp;	//ヒットポイント
	//モデルデータ
	static CModel sModel;
	//コライダ
	CCollider mCollider;
};

#endif