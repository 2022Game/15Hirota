#ifndef CCUTINCAMERA_H
#define CCUTINCAMERA_H

#include "CCamera.h"

// �J�b�g�C�����̃J�����̃x�[�X�N���X
class CCutInCamera : public CCamera
{
public:
	// �R���X�g���N�^
	CCutInCamera();
	// �f�X�g���N�^
	virtual ~CCutInCamera();

	// �J�b�g�C���J�n
	virtual bool Start();
	// �J�b�g�C���I��
	virtual bool End();

	// �X�V
	void Update() override;
	// �J�b�g�C���Đ�����
	bool IsPlaying() const;

protected:
	// ���ݍĐ����̃J�b�g�C���J����
	static CCutInCamera* spCutInCamera;
	bool mIsPlaying;	// �J�b�g�C���Đ������ǂ���
};
#endif