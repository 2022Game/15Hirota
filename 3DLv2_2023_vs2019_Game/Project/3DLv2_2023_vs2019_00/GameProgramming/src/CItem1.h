#ifndef CITEM1_H
#define CITEM1_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
#include "CInput.h"
#include "CColliderLine.h"

/*
アイテムクラス1(プレイヤークラスの流用)
キャラクタクラスを継承
*/
class CItem1 : public CCharacter3 {
public:
	//インスタンスのポインタの取得
	static CItem1* Instance();
	//衝突処理
	void Collision();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//CBullet bullet;
	CItem1();
	//CPlayer(位置, 回転, スケール)
	CItem1(const CVector& pos, const CVector& rot, const CVector& scale);

	static int Hp();
	//更新処理
	void Update();

private:
	//プレイヤーのインスタンス
	static CItem1* spInstance;

	static int sHp;

	CColliderLine mLine; //線分コライダ
	CColliderLine mLine2; //線分コライダ
	CColliderLine mLine3; //線分コライダ
	CInput mInput;

};

#endif