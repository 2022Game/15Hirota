#ifndef CPLAYER_H
#define CPLAYER_H
//キャラクタクラスのインクルード
#include "CCharacter3.h"
#include "CInput.h"
#include "CBullet.h"
#include "CColliderLine.h"

/*
プレイヤークラス
キャラクタクラスを継承
*/
class CPlayer : public CCharacter3 {
public:
	CPlayer();
	//CPlayer(位置、回転、スケール)
	CPlayer(const CVector& pos, const CVector& rot, const CVector& scale);
	//CBullet bullet;
	//更新処理
	void Update();

	void Collision();
	//衝突処理
	void Collision(CCollider* m, CCollider* o);
	//インスタンスのポインタの取得
	static CPlayer* Instance();
private:
	CInput mInput;
	CColliderLine mLine;	//線分コライダ
	CColliderLine mLine2;	//線分コライダ２
	CColliderLine mLine3;	//線分コライダ３
	//プレイヤーのインスタンス
	static CPlayer* spInstance;
};

#endif