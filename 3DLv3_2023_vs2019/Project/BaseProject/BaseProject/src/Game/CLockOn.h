#ifndef CLOCKON_H
#define CLOCKON_H

#include "CBillBoardImage.h"

// ���b�N�I���\����UI
class CLockOn : public CBillBoardImage
{
public:
	// �R���X�g���N�^
	CLockOn(ETag tag, ETaskPriority, const CVector& pos);
	// �f�X�g���N�^
	~CLockOn();

	// �J���[��ݒ�
	void SetColor(const CColor& color) override;
	// �u�����h�^�C�v��ݒ�
	void SetBlendType(EBlend type);
	
	// �X�V
	void Update() override;

private:
	// ���̈ʒu
	CVector mDefaultPos;
	float mElapsedTime;		// �o�ߎ���
	float mRotationAngle;	// �p�x
	float mSpeed;			// ��]�X�s�[�h
	bool mIsDeath;			// �폜�t���O
};
#endif