#include "CXCharacter.h"

//�R���X�g���N�^
CXCharacter::CXCharacter(ETag tag, ETaskPriority prio)
	: CCharaBase(tag, prio)
	, mpModel(nullptr)
	, mpCombinedMatrix(nullptr)
	, mAnimationLoopFlg(false)
	, mAnimationIndex(0)
	, mAnimationFrame(0.0f)
	, mAnimationFrameSize(0.0f)
{
}

//�f�X�g���N�^
CXCharacter::~CXCharacter()
{
	SAFE_DELETE_ARRAY(mpCombinedMatrix)
}

/*
Init
����������
*/
void CXCharacter::Init(CModelX* model)
{
	mpModel = model;
	//�����s��ޔ��G���A�̊m��
	mpCombinedMatrix = new CMatrix[model->Frames().size()];
	//�ŏ��̃A�j���[�V�����ɂ���
	mAnimationIndex = 0;
	//�J��Ԃ��Đ�����
	mAnimationLoopFlg = true;
	//1�A�j���[�V�����ڂ̍ő�t���[����
	mAnimationFrameSize = model->AnimationSet()[0]->MaxTime();
	//�A�j���[�V�����̃t���[�����ő�ɂ���
	mAnimationFrame = 0.0f;
	mpModel->AnimationSet()[mAnimationIndex]->Time(mAnimationFrame);
	//�A�j���[�V�����̏d�݂�1.0(100%)�ɂ���
	mpModel->AnimationSet()[mAnimationIndex]->Weight(1.0f);
}


/*
ChangeAnimation
�A�j���[�V������؂�ւ���
index:�A�j���[�V�����̔ԍ�
loop:true:�J��Ԃ�
framesize:�Ō�܂ōĐ�����̂Ɏg�p�����t���[����
*/
void CXCharacter::ChangeAnimation(int index, bool loop, float framesize)
{
	//�����ꍇ�͐؂�ւ��Ȃ�
	if (mAnimationIndex == index) return;
	//���̃A�j���[�V�����̏d�݂�0.0(0%)�ɂ���
	mpModel->AnimationSet()[mAnimationIndex]->Weight(0.0f);
	//�ԍ��A�J��Ԃ��A�t���[�������w��
	mAnimationIndex = index % mpModel->AnimationSet().size();
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->AnimationSet()[mAnimationIndex]->Time(mAnimationFrame);
	//�A�j���[�V�����̏d�݂�1.0(100%)�ɂ���
	mpModel->AnimationSet()[mAnimationIndex]->Weight(1.0f);
}

/*
Update
�X�V����
matrix:�ړ��A��]�A�g��k���̍s��
*/
void CXCharacter::Update(const CMatrix& matrix)
{
	if (mpModel == nullptr) return;
	for (size_t i = 0; i < mpModel->AnimationSet().size(); i++)
	{
		mpModel->AnimationSet()[i]->mWeight = 0.0f;
		mpModel->AnimationSet()[mAnimationIndex]->mWeight = 1.0f;
	}
	//�Ō�܂ōĐ�����
	if (mAnimationFrame <= mAnimationFrameSize)
	{
		//�A�j���[�V�����̎��Ԃ��v�Z
		mpModel->AnimationSet()[mAnimationIndex]->Time(
			mpModel->AnimationSet()[mAnimationIndex]->MaxTime() *
			mAnimationFrame / mAnimationFrameSize);
		//�t���[����i�߂�
		mAnimationFrame++;
	}
	else
	{
		//�J��Ԃ��̏ꍇ�́A�t���[����0�ɖ߂�
		if (mAnimationLoopFlg)
		{
			//�A�j���[�V�����̃t���[�����ŏ��ɂ���
			mAnimationFrame = 0.0f;
			mpModel->AnimationSet()[mAnimationIndex]->Time(mAnimationFrame);
		}
		else
		{
			mpModel->AnimationSet()[mAnimationIndex]->
				Time(mpModel->AnimationSet()[mAnimationIndex]
					->MaxTime());
		}
	}
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->Frames()[0]->AnimateCombined(&matrix);
	//�����s��̑ޔ�
	for (size_t i = 0; i < mpModel->Frames().size(); i++)
	{
		mpCombinedMatrix[i] =
			mpModel->Frames()[i]->CombinedMatrix();
	}
}

//�X�V����
void CXCharacter::Update()
{
	//�A�j���[�V�������X�V����
	Update(Matrix());
}

/*
Render
�`�悷��
*/
void CXCharacter::Render()
{
	mpModel->RenderShader(mpCombinedMatrix);
}

bool CXCharacter::IsAnimationFinished()
{
	return mAnimationFrame >= mAnimationFrameSize;
}

int CXCharacter::AnimationIndex()
{
	return mAnimationIndex;
}