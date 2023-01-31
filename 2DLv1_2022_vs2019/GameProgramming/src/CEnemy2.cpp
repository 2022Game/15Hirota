#include "CEnemy2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 190, 160	//�e�N�X�`���}�b�s���O
#define TEXCRY 196, 216, 190, 160	//�e�N�X�`���}�b�s���O

#define TEXCOORD2 136,156,190,160	//�E����2
#define TEXLEFT1 188,168,190,160	//������1
#define TEXLEFT2 156,136,190,160	//������2

#define GRAVITY (TIPSIZE / 20.0f)	//�d�͉����x

#define HP 1

int CEnemy2::sNum = 0;

int CEnemy2::sScore = 0;

void CEnemy2::Score(int score)
{
	sScore = score;
}

int CEnemy2::Score()
{
	return sScore;
}

void CEnemy2::Num(int num)
{
	sNum = num;
}

int CEnemy2::Num()
{
	return sNum;
}

void CEnemy2::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CEnemy2::Collision(CCharacter* m, CCharacter* o)
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
			if (o->State() == EState::EMOVE || o->State() == EState::ESTOP)
			{
				if (mVx > x && mVy == 0.0f)
				{
					mVx = -mVx;
				}
				else
				{
					mVx = -mVx;
				}
			}
			if (o->State() == EState::EJUMP || o->State() == EState::EFALL)
			{
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
			/*if (x != 0.0f)
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
			}*/
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

CEnemy2::CEnemy2(float x, float y, float w, float h, CTexture* pt)
	:sCount(0)
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

void CEnemy2::Update()
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
		if ((int)X() % PITCH < PITCH / 2)
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
