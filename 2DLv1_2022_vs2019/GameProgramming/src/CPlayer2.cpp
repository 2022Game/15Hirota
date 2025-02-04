#include "CPlayer2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 158, 128	//テクスチャマッピング
#define TEXCRY 196, 216, 158, 128	//テクスチャマッピング
#define GRAVITY (TIPSIZE / 20.0f)	//重力加速度
#define JUMPV0 (TIPSIZE / 1.2f)		//ジャンプの初速

#define TEXCOORD2 136,156,158,128	//右向き2
#define TEXLEFT1 188,168,158,128	//左向き1
#define TEXLEFT2 156,136,158,128	//左向き2
#define VELOCITY 10.0f	//移動速度


#define HP 3	//HPの初期値は3
#define GOAL1 1	//GOALの初期値は1

#define SE_JUMP "res\\jump.wav" //ジャンプの音声ファイル

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

			//敵の衝突判定を実行
			o->Collision(o, m);
			X(X() + x);
			Y(Y() + y);
			//着地した時
			if (y != 0.0f)
			{
				//Y軸速度を0にする
				mVy = 0.0f;
				if (y > 0.0f)
				{
					mState = EState::EMOVE;
					mState = EState::EFALL;
				}
				else
				{	//ジャンプでなければ泣く
					mState = EState::ECRY;
					if (mInvincible == 0)
					{
						mInvincible = 60;
						sHp--;
					}
				}
			}
			else
			{	//ジャンプでなければ泣く
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
			//着地した時
			if (y != 0.0f)
			{
				//Y軸速度を0にする
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
			//着地した時
			if (y != 0.0f)
			{
				//Y軸速度を0にする
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
			//着地した時
			if (y != 0.0f)
			{
				//Y軸速度を0にする
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
			//着地したとき
			if (y != 0.0f)
			{
				//Y軸速度を0にする
				mVy = 0.0f;
				if (o->State() == EState::EJUMP)
				{
					mEnabled = false;
				}
				else
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
				if (o->State() == EState::EJUMP && y > 0.0f)
				{
					mVy = 0.0f;
					mState = EState::EBLOCK_NOEITEM;
				}
				else
				{
					mVy = 0.0f;
					mState = EState::EMOVE;
				}
			}
			else
			{
				mVy = 0.0f;
				mState = EState::EMOVE;
			}
		}
	case ETag::EBLOCK5:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			//着地した時
			if (y != 0.0f)
			{
				//Y軸速度を0にする
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
			//着地した時
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
				//Y軸速度を0にする
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
			//着地した時
			if (y != 0.0f)
			{
				//X軸速度を0にする
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
			//未定
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

	//ジャンプ音ロード
	mSoundJump.Load(SE_JUMP);
}

CPlayer2* CPlayer2::spInstance = nullptr;

CPlayer2* CPlayer2::Instance()
{
	return spInstance;
}

int CPlayer2::sGoal1 = 0; //ゴール

int CPlayer2::Goal1()
{
	return sGoal1;
}

void CPlayer2::Update()
{	
	//無敵時間中はカウントを減少する
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
				//ジャンプ音
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
	//Y座標にY軸速度を加える
	Y(Y() + mVy);
	//Y軸速度に重力を減算する
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
		//泣く画像を設定
		Texture(Texture(), TEXCRY);
	}
	else
	{
		const int PITCH = 32;//画像を切り替える間隔
		if ((int)X() % PITCH < PITCH / 2)
		{
			if (mVx < 0.0f) //左へ移動
			{
				//左向き１を設定
				Texture(Texture(), TEXLEFT1);
			}
			else
			{
				//通常の画像を設定
				Texture(Texture(), TEXCOORD);
			}
		}
		else
		{
			if (mVx < 0.0f) //左へ移動
			{
				//左向き2を設定
				Texture(Texture(), TEXLEFT2);
			}
			else
			{
				//2番目の画像を設定
				Texture(Texture(), TEXCOORD2);
			}
		}
	}
}
