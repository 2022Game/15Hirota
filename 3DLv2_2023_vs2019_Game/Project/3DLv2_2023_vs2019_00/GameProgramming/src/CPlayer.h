#ifndef CPLAYER_H
#define CPLAYER_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
#include "CInput.h"
#include "CBullet.h"
#include "CColliderLine.h"
#include"CWeapon.h"

/*
プレイヤークラス
キャラクタクラスを継承
*/
class CPlayer : public CCharacter3 {
public:
	//インスタンスのポインタの取得
	static CPlayer* Instance();
	//衝突処理
	void Collision();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	//CBullet bullet;
	CPlayer();
	//CPlayer(位置, 回転, スケール)
	CPlayer(const CVector& pos, const CVector& rot, const CVector& scale);

	static int Hp();
	//更新処理
	void Update();

private:
	//プレイヤーのインスタンス
	static CPlayer* spInstance;

	static int sHp;

	CColliderLine mLine; //線分コライダ
	CColliderLine mLine2; //線分コライダ
	CColliderLine mLine3; //線分コライダ
	CInput mInput;
	//プレイヤーの持っている武器
	CWeapon* mpWeapon;
	
	int mJumpcount;	//ジャンプの回数処理
	bool isOnObstacle;	//障害物に乗っているかどうかのフラグ
	bool disableGravity; // 障害物上で重力を無効化するためのフラグ
	bool isOnObstacleJump;	//障害物に乗っているか
	bool isJumping;	//ジャンプ判定
	bool isDodging;	//回避中かどうかのフラグ
};

#endif
