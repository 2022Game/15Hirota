#include "CXPlayer.h"

#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //移動速度
#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //回転速度


CXPlayer::CXPlayer()
	:mColSpherBody(this, nullptr, CVector(), 0.5f)
	, mColSpherHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
	,mColspherSword(this,nullptr,CVector(-10.0f,10.0f,50.0f),0.3f,CCollider::ETag::ESWORD)
{
	mTag = EPLAYER;
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列
	//体
	mColSpherBody.Matrix(&mpCombinedMatrix[8]);
	//頭
	mColSpherHead.Matrix(&mpCombinedMatrix[11]);
	//剣
	mColspherSword.Matrix(&mpCombinedMatrix[21]);
}

void CXPlayer::Update()
{
	if (mInput.Key(VK_SPACE))
	{
		if (AnimationIndex() != 3 && AnimationIndex() != 4)
		{
			ChangeAnimation(3, false, 30);  //アニメーション3
		}
	}
	if (AnimationIndex() == 3 || AnimationIndex() == 4)
	{
		if (IsAnimationFinished())
		{
			if (AnimationIndex() == 3)
			{
				ChangeAnimation(4, false, 30);  // アニメーション4
			}
			else if (AnimationIndex() == 4)
			{
				ChangeAnimation(0, true, 60);  // アニメーション0
			}
		}
		CXCharacter::Update();
		return;
	}
	if (mInput.Key('A'))
	{
		mRotation = mRotation + ROTATION_YV;
	}
	if (mInput.Key('D'))
	{
		mRotation = mRotation - ROTATION_YV;
	}
	if (mInput.Key('W'))
	{
		mPosition = mPosition + VELOCITY * mMatrixRotate;
		ChangeAnimation(1, true, 60);
	}
	else
	{
		if (AnimationIndex() != 3 && AnimationIndex() != 4)
		{
			ChangeAnimation(0, true, 60);	//アニメーション0
		}
	}
	CXCharacter::Update();
}