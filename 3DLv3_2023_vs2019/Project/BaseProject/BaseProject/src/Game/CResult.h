#ifndef CRESULT_H
#define CRESULT_H

#include "CTask.h"
class CText;
class CStageTime;
class CScore;
class CImage;

class CResult : public CTask
{
public:
	CResult();
	~CResult();

	//�C���X�^���X�̃|�C���^�̎擾
	static CResult* Instance();

	// ���ԂƃX�R�A��ݒ�
	void SetResult(int remainingTime, int score);
	// ���ԂƃX�R�A���擾
	void SetTimeAndScore(CStageTime* pTime, CScore* pScore);
	// ���ԂƃX�R�A�̍��v���擾
	int GetTotalScore() const;

	// �����X�R�A�̐ݒ�
	void StartScoreAnimation();
	// �X�R�A�𑝉�������A�j���[�V�����̐ݒ�
	void UpdateScoreAnimation();

	void Update() override;
	void Render() override;

private:
	// �C���X�^���X
	static CResult* spInstance;
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

	CText* mpResultText;
	CStageTime* mpTime;
	CScore* mpScore;
};
#endif