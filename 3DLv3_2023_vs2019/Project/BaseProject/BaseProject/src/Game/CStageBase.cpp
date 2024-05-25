#include "CStageBase.h"

// �R���X�g���N�^
CStageBase::CStageBase()
	: mStageNo(0)
{

}

// �f�X�g���N�^
CStageBase::~CStageBase()
{

}

// �X�e�[�W�j��
void CStageBase::Unload()
{
	// ���̃X�e�[�W�ō쐬�����^�X�N�����ׂč폜
	for (CTask* task : mCreateTasks)
	{
		task->Kill();
	}
}

// �쐬�����^�X�N�����X�g�ɒǉ�
void CStageBase::AddTask(CTask* task)
{
	mCreateTasks.push_back(task);
}

// �쐬�����^�X�N�����X�g�����菜��
void CStageBase::RemoveTask(CTask* task)
{
	mCreateTasks.remove(task);
}

// �X�e�[�W�ԍ��擾
int CStageBase::GetStageNo() const
{
	return mStageNo;
}

// �X�V
void CStageBase::Update()
{

}