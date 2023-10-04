#pragma once
#include "TaskPriority.h"
#include "TaskPauseType.h"
#include "SceneType.h"
class CTaskManager;

//�^�X�N�N���X
class CTask
{
	friend CTaskManager;
public:
	//�Փˏ���
	virtual void Collision() {}

	//�R���X�g���N�^
	CTask(ETaskPriority prio = ETaskPriority::eDefault);
	//�f�X�g���N�^
	virtual ~CTask();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Render();

	//�D��x��ݒ�
	void SetPriority(ETaskPriority prio);
	//�|�[�Y�̎�ނ�ݒ�
	void SetPauseType(ETaskPauseType type);
	//�|�[�Y�̎�ނ��擾
	ETaskPauseType GetPauseType() const;
	//��������V�[����ݒ�
	void SetSceneType(EScene scene);
	//��������V�[�����擾
	EScene GetSceneType() const;

	//�^�X�N���폜
	void Kill();
	//�폜�t���O�擾
	bool IsKill() const;

private:
	CTask* mpNext;		//���̃|�C���^
	CTask* mpPrev;		//�O�̃|�C���^
	ETaskPriority mPriority;	//�D��x
	bool mEnabled;		//�L���t���O
	ETaskPauseType mPauseType;//�|�[�Y�̎��
	EScene mSceneType;	//��������V�[���̎��
};
