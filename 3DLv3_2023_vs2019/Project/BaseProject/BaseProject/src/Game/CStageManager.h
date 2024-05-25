#ifndef CSTAGEMANAGER_H
#define CSTAGEMANAGER_H

class CStageBase;

// �X�e�[�W�̊Ǘ��N���X
class CStageManager
{
public:
	// �X�e�[�W�ǂݍ���
	static void LoadStage(int no);
	// ���݂̃X�e�[�W�j��
	static void UnloadStage();
	// �쐬�����^�X�N�����X�g�ɒǉ�
	static void AddTask(CTask* task);
	// �쐬�����^�X�N�����X�g�����菜��
	static void RemoveTask(CTask* task);
	// ���݂̃X�e�[�W���X�V
	static void Update();

private:
	// �R���X�g���N�^
	CStageManager();
	// �f�X�g���N�^
	~CStageManager();

	// �X�e�[�W�}�l�[�W���̃C���X�^���X
	static CStageManager* spInstance;
	// ���݂̃X�e�[�W
	static CStageBase* spCurrentStage;
};
#endif