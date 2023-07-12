#include "CTaskManager.h"

//�^�X�N�}�l�[�W���̃C���X�^���X
CTaskManager* CTaskManager::mpInstance = nullptr;

//�C���X�^���X�̎擾
CTaskManager* CTaskManager::Instance()
{
	//�C���X�^���X���������
	if (mpInstance == nullptr)
	{	//�C���X�^���X�𐶐�����
		mpInstance = new CTaskManager();
	}
	return mpInstance;
}

//�f�t�H���g�R���X�g���N�^
CTaskManager::CTaskManager()
	: mPauseBit(0)
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

void CTaskManager::Delete() {
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		CTask* del = task;
		//����
		task = task->mpNext;
		//mEnabled��false�Ȃ�폜
		if (del->mEnabled == false) {
			delete del;
		}
	}
}

//�V�[�����̃^�X�N�����ׂč폜
void CTaskManager::DeleteInScene(EScene scene)
{
	//�퓬����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		CTask* del = task;
		//����
		task = task->mpNext;
		//��������V�[������v������A
		//�폜�t���O�𗧂Ă�(�L���t���O���I�t�ɂ���)
		if (del->GetSceneType() == scene) {
			del->mEnabled = false;
		}
	}
}

void CTaskManager::Remove(CTask* task)
{
	//�^�X�N�̑O�̎����A�^�X�N�̎��ɂ���
	task->mpPrev->mpNext = task->mpNext;
	//�^�X�N�̎��̑O���A�^�X�N�̑O�ɂ���
	task->mpNext->mpPrev = task->mpPrev;
}
CTaskManager::~CTaskManager() {
}
//���X�g�ɒǉ�
//Add(�^�X�N�̃|�C���^)
void CTaskManager::Add(CTask* addTask)
{
	//mHead�̎����猟��
	CTask* task = mHead.mpNext;

	//�D��x�̑傫�����ɑ}������
	//�}���ʒu�̌����i�D��x���������傫���Ȃ����O�j
	//mPriority>=0�̂���
	while (task != &mTail && addTask->mPriority < task->mPriority)
	{
		task = task->mpNext; //����
	}

	//addTask�̎���task
	addTask->mpNext = task;
	//addTask�̑O��task�̑O��
	addTask->mpPrev = task->mpPrev;
	//addTask�̑O�̎���addTask��
	addTask->mpPrev->mpNext = addTask;
	//task�̑O��addTask��
	task->mpPrev = addTask;
}

//�X�V
void CTaskManager::Update() {
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		//�|�[�Y���̃^�X�N�łȂ����
		TaskPauseType pause = task->GetPauseType();
		if (pause == TaskPauseType::eNone || (mPauseBit & (int)pause) == 0)
		{
			//�X�V�������Ă�
			task->Update();
		}
		//����
		task = task->mpNext;
	}
}

//�`��
void CTaskManager::Render() {
	//�Ōォ��擪�܂ŌJ��Ԃ�
	CTask* task = mTail.mpPrev;
	while (task->mpPrev) {
		//�`�揈�����Ă�
		task->Render();
		//����
		task = task->mpPrev;
	}
}

//�Փˏ���
void CTaskManager::Collision()
{
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		//�Փˏ������Ă�
		task->Collision();
		//����
		task = task->mpNext;
	}
}

//�|�[�Y��ݒ�
void CTaskManager::Pause(int pauseBit)
{
	mPauseBit |= pauseBit;
}

//�|�[�Y����������
void CTaskManager::UnPause(int pauseBit)
{
	mPauseBit &= ~pauseBit;
}

//�|�[�Y�����ǂ���
bool CTaskManager::IsPaused(int pauseBit) const
{
	if (pauseBit == 0) pauseBit = ~pauseBit;
	return (mPauseBit & pauseBit) != 0;
}
