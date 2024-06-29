#ifndef CCUTINDEATHJUMP_H
#define CCUTINDEATHJUMP_H

#include "CCutInCamera.h"

// ���S�W�����v�J����
class CCutInDeathJump : public CCutInCamera
{
public:
	// �R���X�g���N�^
	CCutInDeathJump();
	// �f�X�g���N�^
	~CCutInDeathJump();

	// �C���X�^���X�̃s�����̎擾
	static CCutInDeathJump* Instance();

	// �J�b�g�C���J�n
	bool Start() override;
	// �J�b�g�C���I��
	bool End() override;

	// �J�b�g�C���ɕK�v�ȏ���ݒ�
	void Setup(CObjectBase* obj);

	// �X�V
	void Update() override;
private:
	static CCutInDeathJump* spInstance;
	// �X�e�b�v0 �J��������]
	void CutInStep0();
	// �X�e�b�v1 �J�b�g�C���I�����̑҂�
	void CutInStep1();
	int mCutInStep;	// �J�b�g�C���̃X�e�b�v
	float mElapsedTime;	// �o�ߎ��Ԍv���p

	CVector mCenterPos;	// �J�b�g�C���̒��S�n�_
	float mStartAngleY;	// �J�n�̃J������Y���p�x

	CObjectBase* mObject;
};
#endif