#ifndef CSCORE_H
#define CSCORE_H

#include "CTask.h"

class CText;
class CFont;

class CScore : public CTask
{
public:
	// �R���X�g���N�^
	CScore();
	// �f�X�g���N�^
	~CScore();

	//�C���X�^���X�̃|�C���^�̎擾
	static CScore* Instance();

	// �X�R�A��ݒ�
	void Score(int score);

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

	// �X�R�A���擾
	int GetScore() const { return mScore; }
private:
	static CScore* spInstance;

	// �X�R�A�̃e�L�X�g
	CText* mpScoreText;
	// �t�H���g�e�L�X�g
	CFont* mpLogoFont;

	// �X�R�A
	int mScore;

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