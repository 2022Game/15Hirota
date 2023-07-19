#ifndef CWEAPON_H
#define CWEAPON_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
#include "CBullet.h"
#include "CColliderLine.h"

/*
武器クラス
キャラクタクラスを継承
*/
class CWeapon : public CCharacter3 {
public:
	CWeapon();
	//CWeapon(位置, 回転, スケール)
	CWeapon(const CVector& pos, const CVector& rot, const CVector& scale);

	//衝突判定の更新処理
	void Collision();
	//衝突判定
	void Collision(CCollider* m, CCollider* o);

	//更新処理
	void Update();
private:

	//攻撃判定用のコライダー
	CColliderLine mAttackCollider;
};

#endif