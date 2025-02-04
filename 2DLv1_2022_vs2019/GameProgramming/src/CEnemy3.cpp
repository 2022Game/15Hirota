#include "CEnemy3.h"
#include "CApplication.h"

#define TEXCOORD 201, 218, 900, 883	//テクスチャマッピング
#define TEXCRY 221, 238, 900, 890

#define TEXLEFT1 180, 197, 900, 883
#define TEXLEFT2 197, 180, 900, 883

#define TEXCOORD2 218, 201, 900, 883

#define GRAVITY (TIPSIZE / 20.0f)	//重力加速度

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
	//めり込み調整変数を宣言する
	float x, y;
	switch (o->Tag())
	{
	case ETag::ETURN:
		//折り返しに当たった時
		if (CRectangle::Collision(o, &x, &y))
		{
			//めり込まない位置まで戻す
			X(X() + x);
			Y(Y() + y);
			//X軸速度を反転させる
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
				//敵数1減算
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
			//着地したとき
			if (y != 0.0f)
			{
				//Y軸速度を0にする
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
			//着地したとき
			if (y != 0.0f)
			{
				//Y軸速度を0にする
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
			//着地したとき
			if (y != 0.0f)
			{
				//Y軸速度を0にする
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
			//着地したとき
			if (y != 0.0f)
			{
				//Y軸速度を0にする
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
			//着地したとき
			if (y != 0.0f)
			{
				//Y軸速度を0にする
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
	//X軸速度の初期値を移動速度にする
	mVx = VELOCITY;
	//敵数に1加算する
	sNum++;
	//スコアを加算する
	sScore;
}

void CEnemy3::Update()
{
	switch (mState)
	{
	case EState::ECRY:
		//泣く画像を設定
		Texture(Texture(), TEXCRY);
		break;
	case EState::EMOVE:
		//X軸速度分、X座標を更新する
		X(X() + mVx);
		const int PITCH = 32;//画像を切り替える間隔
		if ((int)X() % PITCH < PITCH / 3)
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
		break;
	}
	//Y座標にY軸速度を加える
	Y(Y() + mVy);
	//Y軸速度に重力を減算する
	mVy -= GRAVITY;
}
