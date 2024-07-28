#ifndef CSTAGETIME_H
#define CSTAGETIME_H

#include "CTask.h"

class CText;
class CImage;
class CFont;

class CStageTime : public CTask
{
public:
	// �R���X�g���N�^
	CStageTime();
	// �f�X�g���N�^
	~CStageTime();

	//�C���X�^���X�̃|�C���^�̎擾
	static CStageTime* Instance();

	// ���Ԃ�ݒ�
	void Time(int time);
	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

	// ���Ԃ��擾
	int GetTime() const { return mTime; }
private:
	// �C���X�^���X
	static CStageTime* spInstance;


	// ���Ԃ̃e�L�X�g
	CText* mpTimerText;
	// �t�H���g
	CFont* mpLogoFont;
	// ���v�̉摜
	CImage* mpTimer;

	// ����
	int mTime;

	// �X�e�[�W1��
	bool mIsStage1;
	// �X�e�[�W2��
	bool mIsStage2;
	// �X�e�[�W3��
	bool mIsStage3;
	// �X�e�[�W4��
	bool mIsStage4;
};
#endif