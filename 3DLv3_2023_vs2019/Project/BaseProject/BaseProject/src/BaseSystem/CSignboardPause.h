#ifndef CSIGNBOARDPAUSE_H
#define CSIGNBOARDPAUSE_H

#include "CTask.h"
#include "CInput.h"
#include "CImage.h"

class CSignboardPause : public CTask
{
private:
	// �v���C���[�̃C���X�^���X
	static CSignboardPause* spInstance;
	bool mIsPaused;			//�|�[�Y�����ǂ���
	int mPauseStep;			//�|�[�Y�����̃X�e�b�v
	float mElapsedTime;		//�o�ߎ��Ԍv���p
	float mPauseTextAlpha;	//PAUSE�e�L�X�g�̃A���t�@�l�ۑ��p

	CImage* mFadeBg;		//�t�F�[�h�w�i�̃C���[�W
	CImage* mPauseText;		//PAUSE�e�L�X�g�̃C���[�W

public:
	//�C���X�^���X�̃|�C���^�̎擾
	static CSignboardPause* Instance();

	
	//�R���X�g���N�^
	CSignboardPause();
	//�f�X�g���N�^
	~CSignboardPause();

	void StartPause();
	void TogglePause();
	void EndPause();
	bool IsPauseInProgress();

	//�X�V
	void Update();
	//�`��
	void Render();
};
#endif