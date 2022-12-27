#include "CMoveBlock2.h"
#include "CApplication.h"

#define TEXCOORD 136.0f,169.0f,52.0f,43.0f //テクスチャ座標

CMoveBlock2::CMoveBlock2(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EMOVEBLOCK2;
	//X軸速度の初期値を移動速度にする
	mVy = 2.0f;
	spInstance = this;
}

CMoveBlock2* CMoveBlock2::spInstance = nullptr;

CMoveBlock2* CMoveBlock2::Instance()
{
	return spInstance;
}

void CMoveBlock2::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CMoveBlock2::Collision(CCharacter* m, CCharacter* o)
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
			mVy = -mVy;
		}
	}
}

void CMoveBlock2::Update()
{
	switch (mState)
	{
	case EState::EMOVE:
		//X軸速度分、X座標を更新する
		Y(Y() + mVy);
	}
	//X軸速度分、X座標を更新する
	Y(Y() + mVy);
}