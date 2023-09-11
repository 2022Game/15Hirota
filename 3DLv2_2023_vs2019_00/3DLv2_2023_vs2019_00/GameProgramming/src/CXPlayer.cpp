#include "CXPlayer.h"

#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //�ړ����x
#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //��]���x


CXPlayer::CXPlayer()
	:mColSpherBody(this, nullptr, CVector(), 0.5f)
	, mColSpherHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
	,mColspherSword(this,nullptr,CVector(-10.0f,10.0f,50.0f),0.3f, CCollider::ETag::ESWORD)
{
	mTag = EPLAYER;
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��
	//��
	mColSpherBody.Matrix(&mpCombinedMatrix[9]);
	//��
	mColSpherHead.Matrix(&mpCombinedMatrix[12]);
	//��
	mColspherSword.Matrix(&mpCombinedMatrix[22]);
}

void CXPlayer::Update()
{
	if (mInput.Key(VK_SPACE))
	{
		if (AnimationIndex() != 3 && AnimationIndex() != 4)
		{
			ChangeAnimation(3, false, 30);  //�A�j���[�V����3
		}
	}
	if (AnimationIndex() == 3 || AnimationIndex() == 4)
	{
		if (IsAnimationFinished())
		{
			if (AnimationIndex() == 3)
			{
				ChangeAnimation(4, false, 30);  // �A�j���[�V����4
			}
			else if (AnimationIndex() == 4)
			{
				ChangeAnimation(0, true, 60);  // �A�j���[�V����0
			}
		}
		CXCharacter::Update();
		return;
	}

	//�J�����̑O��
	CVector cameraZ = CActionCamera::Instance()->VectorZ();
	//�J�����̍�����
	CVector cameraX = CActionCamera::Instance()->VectorX();
	//�L�����N�^�̑O��
	CVector charZ = mMatrixRotate.VectorZ();
	//XZ���ʂɂ��Đ��K��
	cameraZ.Y(0.0f); cameraZ = cameraZ.Normalize();
	cameraX.Y(0.0f); cameraX = cameraX.Normalize();
	charZ.Y(0.0f); charZ = charZ.Normalize();
	//�ړ������̐ݒ�
	CVector move;
	bool AnimeChangeflag = false;

	if (mInput.Key('A')) {
		move = move + cameraX;
		AnimeChangeflag = true;
	}
	if (mInput.Key('D')) {
		move = move - cameraX;
		AnimeChangeflag = true;
	}
	if (mInput.Key('W')) {
		move = move + cameraZ;
		AnimeChangeflag = true;
	}
	if (mInput.Key('S')) {
		move = move - cameraZ;
		AnimeChangeflag = true;
	}
	if (AnimeChangeflag)
	{
		ChangeAnimation(1, true, 60);
	}
	else
	{
		ChangeAnimation(0, true, 60);
	}
	//�ړ��L��
	if (move.Length() > 0.0f)
	{
		//�V��
		const float MARGIN = 0.06f;
		//���K��
		move = move.Normalize();
		//�����̌����ƌ��������������ŊO��
		float cross = charZ.Cross(move).Y();
		//�����̌����ƌ��������������œ���
		float dot = charZ.Dot(move);
		//�O�ς��v���X�͍���]
		if (cross > MARGIN) {
			mRotation.Y(mRotation.Y() + 5.0f);
		}
		//�O�ς��}�C�i�X�͉E��]
		else if (cross < -MARGIN) {
			mRotation.Y(mRotation.Y() - 5.0f);
		}
		//�O��̌����������Ƃ����ς�1.0
		else if (dot < 1.0f - MARGIN) {
			mRotation.Y(mRotation.Y() - 5.0f);
		}
		//�ړ������ֈړ�
		mPosition = mPosition + move * 0.1f;
		ChangeAnimation(1, true, 60);
	}

	CXCharacter::Update();
}

//if (mInput.Key('A'))
	//{
	//	mRotation = mRotation + ROTATION_YV;
	//}
	//if (mInput.Key('D'))
	//{
	//	mRotation = mRotation - ROTATION_YV;
	//}
	//if (mInput.Key('S')) 
	//{
	//	mRotation = mRotation - ROTATION_YV;
	//}
	//if (mInput.Key('W'))
	//{
	//	mPosition = mPosition + VELOCITY * mMatrixRotate;
	//	ChangeAnimation(1, true, 60);
	//}
	//else
	//{
	//	if (AnimationIndex() != 3 && AnimationIndex() != 4)
	//	{
	//		ChangeAnimation(0, true, 60);	//�A�j���[�V����0
	//	}
	//}