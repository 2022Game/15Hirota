#ifndef CSTAGEBASE_H
#define CSTAGEBASE_H
#include "CTask.h"
#include <list>

// �X�e�[�W�̃x�[�X�N���X
class CStageBase
{
public:
	// �R���X�g���N�^
	CStageBase();
	// �f�X�g���N�^
	virtual ~CStageBase();

	// �X�e�[�W�ǂݍ���
	virtual void Load() = 0;
	// �X�e�[�W�j��
	virtual void Unload();

	// �X�e�[�W�ԍ��擾
	int GetStageNo() const;
	

	// �쐬�����^�X�N�����X�g�ɒǉ�
	void AddTask(CTask* task);
	// �쐬�����^�X�N�����X�g�����菜��
	void RemoveTask(CTask* task);

	// �X�V
	virtual void Update();

protected:
	int mStageNo;	// �X�e�[�W�ԍ�

	// ���̃X�e�[�W�ō쐬�����^�X�N�̃��X�g
	std::list<CTask*> mCreateTasks;
};
#endif