#include "CXPlayer.h"

#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //ˆÚ“®‘¬“x
#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //‰ñ“]‘¬“x

void CXPlayer::Update()
{
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
		ChangeAnimation(0, true, 60);
	}
	if (mInput.Key(VK_SPACE))
	{
		if (AnimationIndex() == 0)
		{
			if (IsAnimationFinished() == false)
			{
				ChangeAnimation(3, false, 30);
				ChangeAnimation(4, false, 30);
			}
		}
	}
	CXCharacter::Update();
}