#pragma once
#include "CCharacter.h"
#include "CInput.h"
#include "CSound.h"

class CPlayer2 : public CCharacter
{
public:
	//HPを取得
	static int Hp();
	//GOAL1を取得
	static int Goal1();
	//衝突処理2
	void Collision();
	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);
	//CPlayer2(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CPlayer2(float x, float y, float w, float h, CTexture* pt);
	//更新処理
	void Update();
	static CPlayer2* Instance();
private:
	CSound mSoundJump;	//ジャンプSE
	static int sHp;	//HP
	static int sGoal1; //ゴール
	int mInvincible; //無敵カウンタ
	int mJumpcount;	//ジャンプカウンタ
	CInput mInput;
	static CPlayer2* spInstance;
};