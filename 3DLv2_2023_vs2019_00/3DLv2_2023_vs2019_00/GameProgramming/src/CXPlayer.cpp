#include "CXPlayer.h"

#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //�ړ����x
#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //��]���x

//void CXPlayer::Update()
//{
//	// �U�����̏ꍇ�͈ړ��Ɖ�]�̏������X�L�b�v����
//	if (AnimationIndex() == 3 || AnimationIndex() == 4)
//	{
//		CXCharacter::Update();
//		if (IsAnimationFinished())
//		{
//			if (AnimationIndex() == 3)
//			{
//				ChangeAnimation(4, false, 30);  // �A�j���[�V����4�ɐ؂�ւ���
//			}
//			else if (AnimationIndex() == 4)
//			{
//				ChangeAnimation(0, true, 60);  // �A�j���[�V����0�ɐ؂�ւ���
//			}
//		}
//		return;
//	}
//	if (mInput.Key('A'))
//	{
//		mRotation = mRotation + ROTATION_YV;
//	}
//	if (mInput.Key('D'))
//	{
//		mRotation = mRotation - ROTATION_YV;
//	}
//	if (mInput.Key('W'))
//	{
//		mPosition = mPosition + VELOCITY * mMatrixRotate;
//		ChangeAnimation(1, true, 60);
//	}
//	else
//	{
//		if (AnimationIndex() != 3 && AnimationIndex() != 4)
//		{
//			ChangeAnimation(0, true, 60);
//		}
//	}
//	if (mInput.Key(VK_SPACE))
//	{
//		if (AnimationIndex() != 3 && AnimationIndex() != 4)
//		{
//			ChangeAnimation(3, false, 30);	//�A�j���[�V����3
//		}
//	}
//	else if (AnimationIndex() == 3)
//	{
//		if (IsAnimationFinished())
//		{
//			ChangeAnimation(4, false, 30);  // �A�j���[�V����4
//		}
//	}
//	else if (AnimationIndex() == 4)
//	{
//		if (IsAnimationFinished())
//		{
//			ChangeAnimation(0, true, 60);  // �A�j���[�V����0
//		}
//	}
//	CXCharacter::Update();
//}

void CXPlayer::Update()
{
	if (mInput.Key(VK_SPACE))
	{
		if (AnimationIndex() != 3 && AnimationIndex() != 4)
		{
			ChangeAnimation(3, false, 30);	//�A�j���[�V����3
		}
	}
	if (AnimationIndex() == 3 || AnimationIndex() == 4)
	{
		CXCharacter::Update();
		if (IsAnimationFinished())
		{
			if (AnimationIndex() == 3)
			{
				ChangeAnimation(4, false, 30);  // �A�j���[�V����4�ɐ؂�ւ���
			}
			else if (AnimationIndex() == 4)
			{
				ChangeAnimation(0, true, 60);  // �A�j���[�V����0�ɐ؂�ւ���
			}
		}
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
			ChangeAnimation(0, true, 60);
		}
	}
	CXCharacter::Update();
}