#include "CMoveBlock.h"
#include "CApplication.h"

#define TEXCOORD 136.0f,169.0f,52.0f,43.0f //�e�N�X�`�����W

CMoveBlock::CMoveBlock(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EMOVEBLOCK;
	//X�����x�̏����l���ړ����x�ɂ���
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
	//�߂荞�ݒ����ϐ���錾����
	float x, y;
	switch (o->Tag())
	{
	case ETag::ETURN:
		//�܂�Ԃ��ɓ���������
		if (CRectangle::Collision(o, &x, &y))
		{
			//�߂荞�܂Ȃ��ʒu�܂Ŗ߂�
			X(X() + x);
			Y(Y() + y);
			//X�����x�𔽓]������
			mVx = -mVx;
		}
	}
}

void CMoveBlock::Update()
{
	switch (mState)
	{
	case EState::EMOVE:
		//X�����x���AX���W���X�V����
		X(X() + mVx);
	}
	//X�����x���AX���W���X�V����
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