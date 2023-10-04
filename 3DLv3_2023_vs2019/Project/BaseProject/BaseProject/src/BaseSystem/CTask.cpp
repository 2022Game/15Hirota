#include "CTask.h"
#include "CTaskManager.h"
#include "CSceneManager.h"

//�R���X�g���N�^
CTask::CTask(ETaskPriority prio)
	: mpNext(nullptr)
	, mpPrev(nullptr)
	, mPriority(prio)
	, mEnabled(true)
	, mPauseType(ETaskPauseType::eDefault)
	, mSceneType(CSceneManager::Instance()->GetCurrentScene())
{
	//�^�X�N�𐶐���������
	//�^�X�N�}�l�[�W���[�̃^�X�N���X�g�ɒǉ�
	CTaskManager::Instance()->Add(this);
}

//�f�X�g���N�^
CTask::~CTask()
{
	//�^�X�N�}�l�[�W���[�̃^�X�N���X�g�����菜��
	CTaskManager::Instance()->Remove(this);
}

//�X�V
void CTask::Update()
{
}

//�`��
void CTask::Render()
{
}

//�D��x��ݒ�
void CTask::SetPriority(ETaskPriority prio)
{
	//���ɐݒ肳��Ă���D��x�ł���Ώ������Ȃ�
	if (mPriority == prio) return;

	//��x�^�X�N���X�g�����菜���A�ēx�ǉ����邱�ƂŁA
	//�V�����D��x�̏ꏊ�Ƀ^�X�N����������
	mPriority = prio;
	CTaskManager::Instance()->Remove(this);
	CTaskManager::Instance()->Add(this);
}

//�|�[�Y�̎�ނ�ݒ�
void CTask::SetPauseType(ETaskPauseType type)
{
	mPauseType = type;
}

//�|�[�Y�̎�ނ��擾
ETaskPauseType CTask::GetPauseType() const
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

//�^�X�N���폜
void CTask::Kill()
{
	mEnabled = false;
}

//�폜�t���O�擾
bool CTask::IsKill() const
{
	return !mEnabled;
}