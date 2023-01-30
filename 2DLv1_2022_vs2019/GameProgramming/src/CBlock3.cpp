#include "CBlock3.h"

#define TEXCOORD 210.0f,369.0f,160.0f,0.0f //�e�N�X�`�����W

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
	//�߂荞�ݒ����ϐ���錾����
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