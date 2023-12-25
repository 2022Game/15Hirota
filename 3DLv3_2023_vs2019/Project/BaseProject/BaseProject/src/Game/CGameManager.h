#ifndef CGAMEMANAGER_H
#define CGAMEMANAGER_H
#include "CTask.h"

//	�Q�[���̏��
enum class EGameState
{
	eRaady,			// ������
	eGame,			// �Q�[�����s��
	eStageClear,	// �X�e�[�W�N���A
	eGameClear,		// �Q�[���N���A
	eGameOver,		// �Q�[���I�[�o�[
};

//�Q�[���N���X���Ǘ�����N���X
class CGameManager : public CTask
{
public:
	// �Q�[���J�n
	static void GameStart();
	// �X�e�[�W�N���A
	static void StageClear();
	// �Q�[���I�[�o�[
	static void GameOver();
	// ���݂̃Q�[���̏�Ԃ��擾
	static EGameState GameState();
	// ���݂̃X�e�[�W�ԍ�
	static int StageNo();

	// �X�V����
	void Update();

private:
	// �R���X�g���N�^
	CGameManager();
	// �f�X�g���N�^
	~CGameManager();

	static CGameManager* Instance();

	// ���݂̃Q�[���̏�Ԃ�؂�ւ�
	void ChangeState(EGameState state);

	// ������Ԃ̍X�V����
	void UpdateReady();
	// �Q�[�����̍X�V����
	void UpdateGame();
	// �X�e�[�W�N���A���̍X�V����
	void UpdateStageClear();
	// �Q�[���N���A���̍X�V����
	void UpdateGameClear();
	// �Q�[���I�[�o�[���̍X�V����
	void UpdateGameOver();

	static CGameManager* spInstance;
	int mStageNo;		// ���݂̃X�e�[�W�ԍ�
	EGameState mState;	// ���݂̃Q�[���̏��
	int mStateStep;		// ��ԓ��ł̃X�e�b�v
	float mElapsedTime;	// �o�ߎ��Ԍv���p
};
#endif