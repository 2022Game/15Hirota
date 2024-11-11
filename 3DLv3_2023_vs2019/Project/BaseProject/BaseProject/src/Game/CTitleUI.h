#pragma once
#include "CTask.h"

class CFont;
class CImage;
class CExpandButton;
class CSound;

class CTitleUI : public CTask
{
public:
	// �R���X�g���N�^
	CTitleUI();
	// �f�X�g���N�^
	~CTitleUI();

	// �J��
	void Open();
	// ����
	void Close();
	// �J���Ă��邩�ǂ���
	bool IsOpened() const;

	// �^�C�g����ʏI����
	bool IsEnd() const;
	// �Q�[�����J�n���邩
	bool IsStartGame() const;
	// ����������J��
	bool IsTutorial() const;
	// �Q�[�����I�����邩
	bool IsExitGame() const;

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:
	// �ҋ@���
	void UpdateIdle();
	// ���j���[���J��
	void UpdateOpen();
	// ���j���[�I��
	void UpdateSelect();
	// �t�F�[�h�A�E�g
	void UpdateFadeOut();

	// �^�C�g���̏��
	enum class EState
	{
		eIdle,		// �ҋ@���
		eOpen,		// ���j���[���J��
		eSelect,	// ���j���[�I��
		eFadeOut,	// �t�F�[�h�A�E�g
	};
	// ��Ԑ؂�ւ�
	void ChangeState(EState state);

	// [START]�N���b�N���̃R�[���o�b�N�֐�
	void OnClickStart();
	// [TUTORIAL]�N���b�N���̃R�[���o�b�N�֐�
	void OnClickTutorial();
	// [QUIT]�N���b�N���̃R�[���o�b�N�֐�
	void OnClickQuit();

	EState mState;		// ���݂̏��
	int mStateStep;		// ��ԓ��ł̃X�e�b�v�Ǘ��p
	float mElapsedTime;	// �o�ߎ��Ԍv���p
	// �t�F�[�h�C���p�̌o�ߎ��Ԍv���p
	float mFadeInTime;
	// �t�F�[�h�A�E�g�p�̌o�ߎ��Ԍv���p
	float mFadeOutTime;
	float mTutorialAlpha;
	float mTutorialAlphaMax;
	bool mIsEnd;		// �^�C�g����ʏI���t���O
	bool mFadeOut;
	int mSelectIndex;	// ���ݑI�����Ă��鍀��

	CFont* mpLogoFont;	// �^�C�g�����S�̃t�H���g
	CText* mpTitleLogo;	// �^�C�g�����S
	CImage* mpTitleBg;	// �^�C�g���w�i�C���[�W
	CText* mpStartText;	// �uCLICK TO START�v�̃e�L�X�g
	std::vector<CExpandButton*> mButtons;

	// ��������摜
	CImage* mpTutorialImage;
	CSound* mpOpenTutorial;
	// �J���Ă��邩�ǂ����̃t���O
	bool mIsOpened;
	bool mTutorialSE;
};