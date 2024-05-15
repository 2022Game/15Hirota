#ifndef CGAMEMANAGER_H
#define CGAMEMANAGER_H
#include "CTask.h"
class CResultAnnouncement;
class CResult;

//	�Q�[���̏��
enum class EGameState
{
	eRaady,			// ������
	eGame,			// �Q�[�����s��
	eRestart,		// �Q�[���ĊJ
	eStageClear,	// �X�e�[�W�N���A
	eStageOver,		// �X�e�[�W���s
	eResult,		// ���U���g
	eGameClear,		// �Q�[���N���A
	eGameOver,		// �Q�[���I�[�o�[

	eStage1,
	eStage2,
	eStage3,
};

//�Q�[���N���X���Ǘ�����N���X
class CGameManager : public CTask
{
public:
	// �Q�[���J�n
	static void GameStart();
	// �Q�[���ĊJ
	static void GameRestart();
	// �X�e�[�W�N���A
	static void StageClear();
	// �X�e�[�W���s
	static void StageOver();
	// �Q�[���I�[�o�[
	static void GameOver();
	// ���U���g
	static void Result();

	static void Stage1();
	static void Stage2();
	static void Stage3();

	// ���݂̃Q�[���̏�Ԃ��擾
	static EGameState GameState();
	// ���݂̃X�e�[�W�ԍ�
	static int StageNo();
	// �X�e�[�W�ԍ��̐ݒ�
	static void SetStageNo(int stageNo) {
		Instance()->mStageNo = stageNo;
	}
	
	// �X�V����
	void Update();

private:

	static CGameManager* Instance();
	// ���݂̃Q�[���̏�Ԃ�؂�ւ�
	void ChangeState(EGameState state);

	// �R���X�g���N�^
	CGameManager();
	// �f�X�g���N�^
	~CGameManager();

	// ������Ԃ̍X�V����
	void UpdateReady();
	// �Q�[�����̍X�V����
	void UpdateGame();
	// �Q�[���ĊJ�X�V����
	void UpdateRestart();
	// �X�e�[�W�N���A���̍X�V����
	void UpdateStageClear();
	// �X�e�[�W���s
	void UpdateStageOver();
	// �Q�[���N���A���̍X�V����
	void UpdateGameClear();
	// �Q�[���I�[�o�[���̍X�V����
	void UpdateGameOver();
	// ���U���g���̍X�V����
	void UpdateResult();

	void UpdateStage1();
	void UpdateStage2();
	void UpdateStage3();


	static CGameManager* spInstance;
	int mStageNo;		// ���݂̃X�e�[�W�ԍ�
	EGameState mState;	// ���݂̃Q�[���̏��
	int mStateStep;		// ��ԓ��ł̃X�e�b�v
	float mElapsedTime;	// �o�ߎ��Ԍv���p

	bool mResultSetUp;

	CResultAnnouncement* mpResult;
};
#endif