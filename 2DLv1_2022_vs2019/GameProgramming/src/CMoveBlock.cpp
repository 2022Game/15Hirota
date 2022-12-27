#include "CMoveBlock.h"
#include "CApplication.h"

#define TEXCOORD 136.0f,169.0f,52.0f,43.0f //テクスチャ座標

CMoveBlock::CMoveBlock(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EMOVEBLOCK;
	//X軸速度の初期値を移動速度にする
	mVx = 2.0f;
	spInstance = this;
}

CMoveBlock* CMoveBlock::spInstance = nullptr;

CMoveBlock* CMoveBlock::Instance()
{
	return spInstance;
}

void CMoveBlock::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CMoveBlock::Collision(CCharacter* m, CCharacter* o)
{
	//めり込み調整変数を宣言する
	float x, y;
	switch (o->Tag())
	{
	case ETag::ETURN:
		//折り返しに当たった時
		if (CRectangle::Collision(o, &x, &y))
		{
			//めり込まない位置まで戻す
			X(X() + x);
			Y(Y() + y);
			//X軸速度を反転させる
			mVx = -mVx;
		}
	}
}

void CMoveBlock::Update()
{
	switch (mState)
	{
	case EState::EMOVE:
		//X軸速度分、X座標を更新する
		X(X() + mVx);
	}
	//X軸速度分、X座標を更新する
	X(X() + mVx);
}

//if (X() < CPlayer2::Instance()->X())
//{
//	if (mVx < 0)
//		mVx = -mVx;
//}
//else
//{
//	if (mVx > 0)
//		mVx = -mVx;
//}