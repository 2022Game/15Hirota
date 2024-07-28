#ifndef CGAMEMANAGER_H
#define CGAMEMANAGER_H

#include "CTask.h"

class CResult;
class CResultAnnouncement;

//	�Q�[���̏��
enum class EGameState
{
	eReady,			// ������
	eReset,			// ���Z�b�g
	eTitle,			// �^�C�g����
	eGame,			// �Q�[�����s��
	eRestart,		// �Q�[���ĊJ
	eStageClear,	// �X�e�[�W�N���A
	eStageOver,		// �X�e�[�W���s
	eResult,		// ���U���g
	eGameClear,		// �Q�[���N���A
	eGameOver,		// �Q�[���I�[�o�[z

	eStage1,		// �X�e�[�W1
	eStage2,		// �X�e�[�W2
	eStage3,		// �X�e�[�W3
	eStage4,		// �X�e�[�W4
};

//�Q�[���N���X���Ǘ�����N���X
class CGameManager : public CTask
{
public:
	//// �^�C�g���J�n
	//static void TitleStart();
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
	// �Q�[���N���A�[
	static void GameClear();
	// �X�e�[�W1
	static void Stage1();
	// �X�e�[�W2
	static void Stage2();
	// �X�e�[�W3
	static void Stage3();
	// �X�e�[�W4
	static void Stage4();
	// ���Z�b�g����
	static void Reset();

	// �t�F�[�h�C����Ԃł̍X�V����

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
	//// �^�C�g���X�V����
	//void UpdateTitle();
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
	// �X�e�[�W1�̍X�V����
	void UpdateStage1();
	// �X�e�[�W2�̍X�V����
	void UpdateStage2();
	// �X�e�[�W3�̍X�V����
	void UpdateStage3();
	// �X�e�[�W4�̍X�V����
	void UpdateStage4();

	// ���Z�b�g����
	void UpdateReset();

	// �X�R�A����������
	void ScoreReset();

	static CGameManager* spInstance;
	int mStageNo;		// ���݂̃X�e�[�W�ԍ�
	EGameState mState;	// ���݂̃Q�[���̏��
	int mStateStep;		// ��ԓ��ł̃X�e�b�v
	float mElapsedTime;	// �o�ߎ��Ԍv���p
	float mElapsedStageTime;	// �X�e�[�W�J�n���̌o�ߎ��Ԍv���p

	bool mResultSetUp;

	CResultAnnouncement* mpResultUI;
};
#endif