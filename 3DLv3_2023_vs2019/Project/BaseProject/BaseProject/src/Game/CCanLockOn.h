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

	// �폜�t���O�������Ă��邩�ǂ���
	bool IsDeath() const;

	// �X�V
	void Update() override;

private:
	// ���̈ʒu
	CVector mDefaultPos;
	CVector mMoveSpeed;	// �ړ����x
	float mElapsedTime;	// �o�ߎ���
	float mAngle;// �p�x
	float mDistance;// ����
	float mSpeed;// ��]�X�s�[�h
	bool mIsDeath;		// �폜�t���O
};
#endif