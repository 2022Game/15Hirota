#ifndef CCUTINRESULT_H
#define CCUTINRESULT_H

#include "CCutInCamera.h"

// ���U���g�J����
class CCutInResult : public CCutInCamera
{
public:
	// �R���X�g���N�^
	CCutInResult();
	// �f�X�g���N�^
	~CCutInResult();

	//�C���X�^���X�̃|�C���^�̎擾
	static CCutInResult* Instance();

	// �J�b�g�C���J�n
	bool Start() override;
	// �J�b�g�C���I��
	bool End() override;

	// �J�b�g�C���ɕK�v�ȏ���ݒ�
	void Setup(CObjectBase* obj);

	// �X�V
	void Update() override;

private:
	static CCutInResult* spInstance;
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