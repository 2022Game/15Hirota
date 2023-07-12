#include "CTask.h"

//�R���X�g���N�^
CTask::CTask(EScene scene)
	: mpNext(nullptr)
	, mpPrev(nullptr)
	, mPriority((int)TaskPriority::eDefault)
	, mEnabled(true)
	, mPauseType(TaskPauseType::eDefault)
	, mSceneType(scene)
{
}

//�f�X�g���N�^
CTask::~CTask()
{
}

//�X�V
void CTask::Update()
{
}

//�`��
void CTask::Render()
{
}

//�|�[�Y�̎�ނ�ݒ�
void CTask::SetPauseType(TaskPauseType type)
{
	mPauseType = type;
}

//�|�[�Y�̎�ނ��擾
TaskPauseType CTask::GetPauseType() const
{
	return mPauseType;
}

//��������V�[����ݒ�
void CTask::SetSceneType(EScene scene)
{
	mSceneType = scene;
}

//��������V�[�����擾
EScene CTask::GetSceneType() const
{
	return mSceneType;
}