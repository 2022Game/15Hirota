#include "CMoveBlock2.h"
#include "CApplication.h"

#define TEXCOORD 136.0f,169.0f,52.0f,43.0f //�e�N�X�`�����W

CMoveBlock2::CMoveBlock2(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EMOVEBLOCK2;
	//X�����x�̏����l���ړ����x�ɂ���
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
			mVy = -mVy;
		}
	}
}

void CMoveBlock2::Update()
{
	switch (mState)
	{
	case EState::EMOVE:
		//X�����x���AX���W���X�V����
		Y(Y() + mVy);
	}
	//X�����x���AX���W���X�V����
	Y(Y() + mVy);
}