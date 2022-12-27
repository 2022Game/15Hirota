#include "CKinoko.h"
#include "CApplication.h"

#define TEXCOORD 64,81,49,32

#define Score 100

void CKinoko::Collision()
{
	CApplication::CharacterManager()->Collision(this);
}

void CKinoko::Collision(CCharacter* m, CCharacter* o)
{
	//めり込み調整変数を宣言する
	float x, y;
	switch (o->Tag())
	{
	case ETag::EPLAYER:
		if (CRectangle::Collision(o))
		{
			return;
		}
		break;
	case ETag::EBLOCK2:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			mVx = -mVx;
		}
	case ETag::EDOKAN:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);
			mVx = -mVx;
		}
	}
}

CKinoko::CKinoko(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EITEM;
	//X軸速度の初期値を移動速度にする
	mVx = VELOCITY;
}

void CKinoko::Update()
{
	switch (mState)
	{
	case EState::EMOVE:
		//X軸速度分、X座標を更新する
		X(X() + mVx);
		if (mVx < 0.0f); //左へ移動
	}
}