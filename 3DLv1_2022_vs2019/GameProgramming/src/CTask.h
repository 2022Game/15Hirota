#ifndef  CTASK_H
#define CTASK_H
class CTaskManager;
/*
�^�X�N�N���X
�^�X�N���X�g�̗v�f
*/
class CTask {
	friend CTaskManager;
public:
	//�f�t�H���g�R���X�g���N�^
	CTask()
		:mpNext(nullptr),mpPrev(nullptr),mPriority(0),mEnabled(true)
	{}
	//�f�X�g���N�^�@virtual�ɂ��Ȃ��Ǝq�N���X�̃f�X�g���N�^���Ă΂�Ȃ�
	virtual~CTask(){}
	//�X�V
	virtual void Update(){}
	//�`��
	virtual void Render(){}
protected:
	int mPriority;	//�D��x
	bool mEnabled;	//�L���t���O
private:
	CTask* mpNext;	//���̃|�C���^
	CTask* mpPrev;	//�O�̃|�C���^
};
#endif // ! CTASK_H
