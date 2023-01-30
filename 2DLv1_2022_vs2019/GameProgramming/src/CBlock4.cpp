#include "CBlock4.h"

#define TEXCOORD 365.0f,382.0f,166.0f,149.0f //テクスチャ座標

#define TEXCOORD_NO_ITEM  366.0f,383.0f,90.0f,73.0f //テクスチャ画像

//#define VELOCITY 10.0f	//移動速度

int CBlock4::sScore = 0;

void CBlock4::Score(int score)
{
	sScore = score;
}

int CBlock4::Score()
{
	return sScore;
}

CBlock4::CBlock4(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EBLOCK4;
	//スコアを加算する
	sScore;
}

void CBlock4::Update()
{
	switch (mState)
	{
	case EState::EBLOCK_NOEITEM:
		//アイテム無し画像を設定
		Texture(Texture(), TEXCOORD_NO_ITEM);
		break;
	}
}

void CBlock4::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CBlock4::Collision(CCharacter* m, CCharacter* o)
{
	//めり込み調整変数を宣言する
	float x, y;
	switch (o->Tag())
	{
	case ETag::EPLAYER:
		if (CRectangle::Collision(o))
		{
			if (o->State() == EState::EJUMP)
			{
				if (mState != EState::EBLOCK_NOEITEM)
				{
					sScore += 50;
					//画像変更
				}
			}
			mState = EState::EBLOCK_NOEITEM;
		}
		break;
	}
}