#ifndef CCANLOCKON_H
#define CCANLOCKON_H

#include "CBillBoardImage.h"

// ���b�N�I���\����UI
class CCanLockOn : public CBillBoardImage
{
public:
	// �R���X�g���N�^
	CCanLockOn(ETag tag, ETaskPriority, const CVector& pos);
	// �f�X�g���N�^
	~CCanLockOn();

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
};
#endif