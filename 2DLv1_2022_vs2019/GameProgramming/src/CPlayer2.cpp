#include "CPlayer2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 158, 128	//�e�N�X�`���}�b�s���O
#define TEXCRY 196, 216, 158, 128	//�e�N�X�`���}�b�s���O
#define GRAVITY (TIPSIZE / 20.0f)	//�d�͉����x
#define JUMPV0 (TIPSIZE / 1.2f)		//�W�����v�̏���

#define TEXCOORD2 136,156,158,128	//�E����2
#define TEXLEFT1 188,168,158,128	//������1
#define TEXLEFT2 156,136,158,128	//������2
#define VELOCITY 10.0f	//�ړ����x


#define HP 3	//HP�̏����l��3
#define GOAL1 1	//GOAL�̏����l��1

#define SE_JUMP "res\\jump.wav" //�W�����v�̉����t�@�C��

int CPlayer2::sHp = 0;	//HP

int CPlayer2::Hp()
{
	return sHp;
}

void CPlayer2::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CPlayer2::Collision(CCharacter* m, CCharacter* o)
{
	float x, y;
	switch (o->Tag())
	{
	case ETag::EENEMY:
		if (CRectangle::Collision(o, &x, &y))
		{

			//�G�̏Փ˔�������s
			o->Collision(o, m);
			X(X() + x);
			Y(Y() + y);
			//���n������
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
					mState = EState::EFALL;
				}
				else
				{	//�W�����v�łȂ���΋���
					mState = EState::ECRY;
					if (mInvincible == 0)
					{
						mInvincible = 60;
						sHp--;
					}
				}
			}
			else
			{	//�W�����v�łȂ���΋���
				mState = EState::ECRY;
				if (mInvincible == 0)
				{
					mInvincible = 60;
					sHp--;
				}
			}
		}
		break;
	case ETag::EPLAYER:
		break;
	case ETag::EBLOCK:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//���n������
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
		}
		break;
	case ETag::EDOKAN:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//���n������
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
		}
		break;
	case ETag::EBLOCK2:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//���n������
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
		}
		break;
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
		}
		break;
	case ETag::EBLOCK4:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			if (y != 0.0f)
			{
				if (y > 0.0f)
				{
					mVy = 0.0f;
					mState = EState::EBLOCK_NOEITEM;
				}
				else
				{
					mState = EState::EMOVE;
				}
			}
			else
			{
				mState = EState::EMOVE;
			}
		}
	case ETag::EBLOCK5:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//���n������
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
		}
	case ETag::EMOVEBLOCK:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//���n������
			if (y != 0.0f)
			{
				X(X() + o->Vx());
				{
					X(X() + o->Vx() + 2.0f);
					mVx = -mVx;
				}
				X(X() + o->Vx());
				{
					X(X() + o->Vx() - 2.0f);
					mVx = -mVx;
				}
				//Y�����x��0�ɂ���
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
		}
		break;
	case ETag::EMOVEBLOCK2:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//���n������
			if (y != 0.0f)
			{
				//X�����x��0�ɂ���
				mVx = 0.0f;
				if (x > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}
		}
		break;
	case ETag::EGOAL:
		if (CRectangle::Collision(o, &x, &y))
		{
			sGoal1--;
		}
		break;
	case ETag::EFALLING:
		if (CRectangle::Collision(o, &x, &y))
		{
			sHp =0;
			{

			}
			mState = EState::EMOVE;
		}
		break;
	case ETag::EITEM:
		if (CRectangle::Collision(o, &x, &y))
		{
			//����
		}
		break;
	}
}

CPlayer2::CPlayer2(float x, float y, float w, float h, CTexture* pt)
	: mInvincible(0)
	, mJumpcount(0)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EPLAYER;
	sHp = HP;
	sGoal1 = GOAL1;
	spInstance = this;

	//�W�����v�����[�h
	mSoundJump.Load(SE_JUMP);
}

CPlayer2* CPlayer2::spInstance = nullptr;

CPlayer2* CPlayer2::Instance()
{
	return spInstance;
}

int CPlayer2::sGoal1 = 0; //�S�[��

int CPlayer2::Goal1()
{
	return sGoal1;
}

void CPlayer2::Update()
{	
	//���G���Ԓ��̓J�E���g����������
	if (mInvincible > 0)
	{
		mInvincible--;
	}
	if (mState != EState::EJUMP)
	{
		if (mInput.Key('J'))
		{
			if (mJumpcount == 0)
			{
				//�W�����v��
				mSoundJump.Play(0.1f);
				mVy = JUMPV0;
				mState = EState::EJUMP;
				mJumpcount++;
			}
			if (mJumpcount > 1)
			{
				mVy = 0;
			}
		}
		else if (!mInput.Key('J'))
		{
			mJumpcount = 0;
		}
	}
	if (mInput.Key('A'))
	{
		mVx = -VELOCITY;
		//		float x = X() - 4.0f;
		X(X() + mVx);
	}
	if (mInput.Key('D'))
	{
		mVx = VELOCITY;
		//		float x = X() - 4.0f;
		X(X() + mVx);
	}
	//Y���W��Y�����x��������
	Y(Y() + mVy);
	//Y�����x�ɏd�͂����Z����
	mVy -= GRAVITY;

	if (mInvincible > 0)
	{
		if (mState != EState::EJUMP)
		{
			mState = EState::ECRY;
		}
	}
	if (mState == EState::ECRY)
	{
		//�����摜��ݒ�
		Texture(Texture(), TEXCRY);
	}
	else
	{
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
	}
}
