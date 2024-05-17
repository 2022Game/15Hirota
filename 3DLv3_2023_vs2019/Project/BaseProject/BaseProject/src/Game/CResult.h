#ifndef CRESULT_H
#define CRESULT_H

#include "CTask.h"

class CText;
class CStageTime;
class CScore;
class CImage;
class CFont;

class CResult : public CTask
{
public:
	// �R���X�g���N�^
	CResult();
	// �f�X�g���N�^
	~CResult();

	//�C���X�^���X�̃|�C���^�̎擾
	static CResult* Instance();

	// ���ԂƃX�R�A��ݒ�
	void SetResult(int remainingTime, int score);
	// ���ԂƃX�R�A�̍��v���擾
	int GetTotalScore() const;

	// �����X�R�A�̐ݒ�
	void StartScoreAnimation();
	// �X�R�A�𑝉�������A�j���[�V�����̐ݒ�
	void UpdateScoreAnimation();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �C���X�^���X
	static CResult* spInstance;

	// ���U���g�̃e�L�X�g
	CText* mpResultText;
	// ��������
	CStageTime* mpTime;
	// �X�R�A
	CScore* mpScore;
	// �t�H���g�e�L�X�g
	CFont* mpFont;

	// ����
	int mRemainingTime;
	// �X�R�A
	int mScore;
	// ���݂̃X�R�A
	int mCurrentDisplayedScore;
	// �ڕW�X�R�A
	int mTargetScore;
	// �X�R�A�𑝉�������A�j���[�V�����̑��x
	int mScoreAnimationSpeed;
};
#endif