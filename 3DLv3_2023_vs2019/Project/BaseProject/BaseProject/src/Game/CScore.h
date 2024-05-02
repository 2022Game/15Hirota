#ifndef CSCORE_H
#define CSCORE_H

#include "CTask.h"
class CText;
class CScore : public CTask
{
public:
	CScore();
	~CScore();

	//�C���X�^���X�̃|�C���^�̎擾
	static CScore* Instance();

	void Score(int score);
	void Update() override;
	void Render() override;

	int GetScore() const { return mScore; }
private:
	static CScore* spInstance;
	int mScore;
	bool mIsStage1;
	bool mIsStage2;
	bool mIsStage3;
	CText* mpScoreText;
};
#endif