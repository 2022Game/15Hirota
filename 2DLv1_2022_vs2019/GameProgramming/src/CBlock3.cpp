#include "CBlock3.h"

#define TEXCOORD 210.0f,369.0f,160.0f,0.0f //テクスチャ座標

CBlock3::CBlock3(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EBLOCK3;
	flag_B = true;
}

void CBlock3::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CBlock3::Collision(CCharacter* m, CCharacter* o)
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
				mEnabled = false;
			}
		}
		break;
	}
}