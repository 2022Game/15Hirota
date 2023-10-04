#include "CTaskManager.h"
#include "CCamera.h"

//�^�X�N�}�l�[�W���̃C���X�^���X
CTaskManager* CTaskManager::mpInstance = nullptr;

// �C���X�^���X���擾
CTaskManager* CTaskManager::Instance()
{
	// �C���X�^���X��������΁A�V������������
	if (mpInstance == nullptr)
	{
		mpInstance = new CTaskManager();
		mpInstance->Initialize();
	}
	return mpInstance;
}

// �C���X�^���X�̔j��
void CTaskManager::ClearInstance()
{
	delete mpInstance;
	mpInstance = nullptr;
}

// �R���X�g���N�^
CTaskManager::CTaskManager()
	: mpHead(nullptr)
	, mpTail(nullptr)
{
}

// �f�X�g���N�^
CTaskManager::~CTaskManager()
{
}

// ������
void CTaskManager::Initialize()
{
	mpHead = new CTask();
	mpTail = new CTask();

	mpHead->mpNext = mpTail;
	mpTail->mpPrev = mpHead;
}

// �w�肵���^�X�N�����X�g�ɒǉ�
void CTaskManager::Add(CTask* task)
{
	if (mpHead == nullptr) return;
	if (mpHead->mpNext == nullptr) return;

	// mHead�̎����猟��
	CTask* next = mpHead->mpNext;

	// �D��x�̐��l�����������ɕ��ׂ�
	// �}���ʒu�̌���
	// �i�ǉ�����^�X�N�̗D��x���傫���^�X�N�̑O�ɑ}���j
	while (next != mpTail && task->mPriority >= next->mPriority)
	{
		next = next->mpNext;	// ����
	}

	// ���^�X�N�̑O�̃^�X�N���o���Ă���
	CTask* prev = next->mpPrev;

	// [prev]��[task]��[next] �̏��Ɋe�^�X�N�̎��̃^�X�N���q��
	prev->mpNext = task;	// prev �� task ���q��
	task->mpNext = next;	// task �� next ���q��

	// [prev]��[task]��[next] �̏��Ɋe�^�X�N�̑O�̃^�X�N���q��
	task->mpPrev = prev;	// prev �� task ���q��
	next->mpPrev = task;	// task �� next ���q��
}

// �w�肵���^�X�N�����X�g�����菜��
void CTaskManager::Remove(CTask* task)
{
	// ��菜���^�X�N�̑O��̃^�X�N���q��
	CTask* prev = task->mpPrev;
	CTask* next = task->mpNext;

	// [prev]��[next] ���q��
	prev->mpNext = next;
	// [prev]��[next] ���q��
	next->mpPrev = prev;

	// ��菜���^�X�N�̑O��̃^�X�N��������
	task->mpPrev = nullptr;
	task->mpNext = nullptr;
}

// �폜�t���O�������Ă���^�X�N��S�č폜
void CTaskManager::Delete()
{
	// �擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mpHead->mpNext;
	while (task != mpTail)
	{
		// �폜�^�X�N���L�����Ă���
		CTask* del = task;
		// ����
		task = task->mpNext;

		// �폜�t���O�������Ă�����A�폜
		if (del->IsKill())
		{
			delete del;
		}
	}
}

// �w�肵���V�[���ɏ�������^�X�N��S�č폜
void CTaskManager::DeleteInScene(EScene scene)
{
	// �擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mpHead->mpNext;
	while (task != mpTail)
	{
		// ��������V�[������v������A
		// �폜�t���O�𗧂Ă�
		if (task->GetSceneType() == scene)
		{
			task->Kill();
		}
		// ����
		task = task->mpNext;
	}
}

// �X�V
void CTaskManager::Update()
{
	// �擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mpHead->mpNext;
	while (task != mpTail)
	{
		// �^�X�N���X�V
		task->Update();
		// ����
		task = task->mpNext;
	}
}

// �`��
void CTaskManager::Render()
{
	// �擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mpHead->mpNext;

	// 3D�֘A�̕`��
	// ���C���J�����𔽉f
	CCamera::MainCamera()->Apply();
	// �擪����2D�֘A�̃^�X�N�܂ŕ`�悷��
	while (task != mpTail && task->mPriority < ETaskPriority::Start2d)
	{
		// �^�X�N��`��
		task->Render();
		task = task->mpNext;
	}

	// 2D�֘A�̕`��
	// 2D�`��p�̃J�����ɐ؂�ւ���
	CCamera::Start2DCamera();
	while (task != mpTail)
	{
		// �^�X�N��`��
		task->Render();
		task = task->mpNext;
	}
	// 3D�`��p�̃J�����֖߂�
	CCamera::End2DCamera();
}

//�Փˏ���
void CTaskManager::Collision()
{
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mpHead->mpNext;
	while (task->mpNext)
	{
		//�Փˏ������Ă�
		task->Collision();
		//����
		task = task->mpNext;
	}
}
