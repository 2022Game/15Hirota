#include "CBlock4.h"

#define TEXCOORD 365.0f,382.0f,166.0f,149.0f //�e�N�X�`�����W

#define TEXCOORD_NO_ITEM  366.0f,383.0f,90.0f,73.0f //�e�N�X�`���摜

//#define VELOCITY 10.0f	//�ړ����x

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
	//�X�R�A�����Z����
	sScore;
}

void CBlock4::Update()
{
	switch (mState)
	{
	case EState::EBLOCK_NOEITEM:
		//�A�C�e�������摜��ݒ�
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
	//�߂荞�ݒ����ϐ���錾����
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
					//�摜�ύX
				}
			}
			mState = EState::EBLOCK_NOEITEM;
		}
		break;
	}
}