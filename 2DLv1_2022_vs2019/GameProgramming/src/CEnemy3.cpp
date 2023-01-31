#include "CEnemy3.h"
#include "CApplication.h"

#define TEXCOORD 201, 218, 900, 883	//�e�N�X�`���}�b�s���O
#define TEXCRY 221, 238, 900, 890

#define TEXLEFT1 180, 197, 900, 883
#define TEXLEFT2 197, 180, 900, 883

#define TEXCOORD2 218, 201, 900, 883

#define GRAVITY (TIPSIZE / 20.0f)	//�d�͉����x

#define HP 1

int CEnemy3::sNum = 0;

int CEnemy3::sScore = 0;

void CEnemy3::Score(int score)
{
	sScore = score;
}

int CEnemy3::Score()
{
	return sScore;
}

void CEnemy3::Num(int num)
{
	sNum = num;
}

int CEnemy3::Num()
{
	return sNum;
}

void CEnemy3::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CEnemy3::Collision(CCharacter* m, CCharacter* o)
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
		break;
	case ETag::EENEMY:
		break;
	case ETag::EPLAYER:
		if (CRectangle::Collision(o, &x, &y))
		{
			mVx = -mVx;
			if (mVx == VELOCITY)
			{
				mVx = -mVx;
			}
			else(mVx == -VELOCITY);
			{
				mVx = -mVx;
			}
			if (o->State() == EState::EJUMP || o->State() == EState::EFALL)
			{
				//�G��1���Z
				if (mState != EState::ECRY)
				{
					sScore += 100;
					sNum--;
					mEnabled = false;
				}
			}
		}
		break;
	case ETag::EBLOCK2:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//���n�����Ƃ�
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
			if (x != 0.0f)
			{
				mVy = VELOCITY;
				if (x > mVx)
				{
					mState = EState::EMOVE;
					mVx = -mVx;
				}
				if (x < mVx)
				{
					mState = EState::EMOVE;
					mVx = -mVx;
				}
			}
		}
	case ETag::EBLOCK3:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//���n�����Ƃ�
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
			if (x != 0.0f)
			{
				mVy = VELOCITY;
				if (x > mVx)
				{
					mState = EState::EMOVE;
					mVx = -mVx;
				}
				if (x < mVx)
				{
					mState = EState::EMOVE;
					mVx = -mVx;
				}
			}
		}
	case ETag::EBLOCK4:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//���n�����Ƃ�
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
			if (x != 0.0f)
			{
				mVy = VELOCITY;
				if (x > mVx)
				{
					mState = EState::EMOVE;
					mVx = -mVx;
				}
				if (x < mVx)
				{
					mState = EState::EMOVE;
					mVx = -mVx;
				}
			}
		}
	case ETag::EBLOCK5:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//���n�����Ƃ�
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
			if (x != 0.0f)
			{
				mVy = VELOCITY;
				if (x > mVx)
				{
					mState = EState::EMOVE;
					mVx = -mVx;
				}
				if (x < mVx)
				{
					mState = EState::EMOVE;
					mVx = -mVx;
				}
			}
		}
	case ETag::EDOKAN:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//���n�����Ƃ�
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
			if (x != 0.0f)
			{
				mVy = VELOCITY;
				if (x > mVx)
				{
					mState = EState::EMOVE;
					mVx = -mVx;
				}
				if (x < mVx)
				{
					mState = EState::EMOVE;
					mVx = -mVx;
				}
			}
		}
	}
}

CEnemy3::CEnemy3(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EENEMY;
	//X�����x�̏����l���ړ����x�ɂ���
	mVx = VELOCITY;
	//�G����1���Z����
	sNum++;
	//�X�R�A�����Z����
	sScore;
}

void CEnemy3::Update()
{
	switch (mState)
	{
	case EState::ECRY:
		//�����摜��ݒ�
		Texture(Texture(), TEXCRY);
		break;
	case EState::EMOVE:
		//X�����x���AX���W���X�V����
		X(X() + mVx);
		const int PITCH = 32;//�摜��؂�ւ���Ԋu
		if ((int)X() % PITCH < PITCH / 3)
		{
			if (mVx < 0.0f) //���ֈړ�
			{
				//�������P��ݒ�
				Texture(Texture(), TEXLEFT1);
			}
			else
			{
				//�ʏ�̉摜��ݒ�
				Texture(Texture(), TEXCOORD);
			}
		}
		else
		{
			if (mVx < 0.0f) //���ֈړ�
			{
				//������2��ݒ�
				Texture(Texture(), TEXLEFT2);
			}
			else
			{
				//2�Ԗڂ̉摜��ݒ�
				Texture(Texture(), TEXCOORD2);
			}
		}
		break;
	}
	//Y���W��Y�����x��������
	Y(Y() + mVy);
	//Y�����x�ɏd�͂����Z����
	mVy -= GRAVITY;
}
