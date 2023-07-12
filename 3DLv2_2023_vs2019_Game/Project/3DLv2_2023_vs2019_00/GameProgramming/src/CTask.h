#ifndef CTASK_H
#define CTASK_H
#include "TaskPriority.h"
#include "TaskPauseType.h"
#include "SceneType.h"
class CTaskManager;
class CCollisionManager;

/*
�^�X�N�N���X
�^�X�N���X�g�̗v�f
*/
class CTask {
	friend CTaskManager;
	friend CCollisionManager;
public:
	//�Փˏ���
	virtual void Collision() {}


	//�f�t�H���g�R���X�g���N�^
	CTask(EScene scene = EScene::eNone);
	//�f�X�g���N�^ virtual�ɂ��Ȃ��Ǝq�N���X�̃f�X�g���N�^���Ă΂�Ȃ�
	virtual ~CTask();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Render();

	//�|�[�Y�̎�ނ�ݒ�
	void SetPauseType(TaskPauseType type);
	//�|�[�Y�̎�ނ��擾
	TaskPauseType GetPauseType() const;
	//��������V�[����ݒ�
	void SetSceneType(EScene scene);
	//��������V�[�����擾
	EScene GetSceneType() const;
protected:
	int mPriority;	//�D��x
	bool mEnabled;	//�L���t���O
private:
	CTask* mpNext;//���̃|�C���^
	CTask* mpPrev;//�O�̃|�C���^
	TaskPauseType mPauseType;//�|�[�Y�̎��
	EScene mSceneType;//��������V�[���̎��
};

#endif
