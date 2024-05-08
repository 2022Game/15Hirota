#ifndef CCUTINCLEAR_H
#define CCUTINCLEAR_H

#include "CCutInCamera.h"

// �X�e�[�W�N���A�J����
class CCutInClear : public CCutInCamera
{
public:
	// �R���X�g���N�^
	CCutInClear();
	// �f�X�g���N�^
	~CCutInClear();

	// �J�b�g�C���J�n
	bool Start() override;
	// �J�b�g�C���I��
	bool End() override;

	// �J�b�g�C���ɕK�v�ȏ���ݒ�
	void Setup(CObjectBase* obj);

	// �X�V
	void Update() override;

private:
	// �X�e�b�v0 �J��������]
	void CutInStep0();
	// �X�e�b�v1 �J�b�g�C���I�����̑҂�
	void CutInStep1();
	int mCutInStep;	// �J�b�g�C���̃X�e�b�v
	float mElapsedTime;	// �o�ߎ��Ԍv���p

	CVector mCenterPos;	// �J�b�g�C���̒��S�n�X
	float mStartAngleY;	// �J�n�̃J������Y���p�x
	float mStartAngleZ;

	CObjectBase* mObject;
};
#endif