#ifndef CRESULTANNOUNCEMENT_H
#define CRESULTANNOUNCEMENT_H

#include "CTask.h"
#include <vector>

class CImage;
class CExpandButton;
class CText;
class CFont;

// ���U���g��ʕ\��
// ���U���g��ʑI�����j���[
class CResultAnnouncement : public CTask
{
public:
	// �R���X�g���N�^
	CResultAnnouncement();
	// �f�X�g���N�^
	~CResultAnnouncement();

	//�C���X�^���X�̃|�C���^�̎擾
	static CResultAnnouncement* Instance();

	// �^�C�g����ʏI����
	bool IsEnd() const;
	// �Q�[�����J�n���邩
	bool IsStartGame() const;
	// �Q�[�����I�����邩
	bool IsExitGame() const;

	// �J��
	void Open();
	// ����
	void Close();

	// �J�������ǂ���
	bool IsOpened() const;
	// �ʂ̃N���X�Ń��U���g�̏�Ԃ��m�F����p
	bool IsResultOpened() const;

	//  �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	static CResultAnnouncement* spInstance;

	// �������Ȃ����
	void UpdateNone();
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
		eNone,		// �������Ȃ����
		eIdle,		// �ҋ@���
		eOpen,		// ���j���[���J��
		eSelect,	// ���j���[�I��
		eFadeOut,	// �t�F�[�h�A�E�g
	};
	// ��Ԑ؂�ւ�
	void ChangeState(EState state);
	// [CONTINUE]�N���b�N���̃R�[���o�b�N�֐�
	void OnClickContinue();
	// [END]�N���b�N���̃R�[���o�b�N�֐�
	void OnClickEnd();

	EState mState;			// ���݂̏��
	int mStateStep;			// ��ԓ��ł̃X�e�b�v�Ǘ��p
	int mSelectIndex;		// ���ݑI�����Ă��鍀��
	float mElapsedTime;		// �o�ߎ��Ԍv���p
	float mElapsedABCTime;	// A,B,C�摜�̌o�ߎ��Ԍv���p
	float mElapsedRankTime;	// �����N�I�摜�̌o�ߎ��Ԍv���p
	float mAlpha;			// ���l
	bool mIsEnd;			// �^�C�g����ʏI���t���O
	bool mIsOpened;			// ���j���[�J�t���O
	bool mResultOpened;		// �ʂ̃N���X�ɓ`����悤�t���O

	CText* mpStartText;						// �uCLICK TO START�v�̃e�L�X�g
	std::vector<CExpandButton*> mButtons;	// �{�^���̉摜�z��

	// ���U���g�̉摜
	enum Result
	{
		A,	// �ō�
		B,	// ����
		C,	// �Œ�
	};
	std::vector<std::pair<Result, CImage*>> mABCItems;

	// �����N�I�摜
	CText* mpRankText;
	CFont* mpRankFont;
};
#endif