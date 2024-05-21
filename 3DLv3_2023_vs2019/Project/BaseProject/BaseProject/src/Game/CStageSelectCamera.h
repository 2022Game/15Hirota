#ifndef CSTAGESELECTCAMERA_H
#define CSTAGESELECTCAMERA_H

#include "CCamera.h"

// �X�e�[�W�I����ʂ̃J����
class CStageSelectCamera : public CCamera
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="eye">�J�����̎��_</param>
	/// <param name="center">�J�����̒����_</param>
	/// <param name="isMainCamera">���C���J�������ǂ���</param>
	CStageSelectCamera(const CVector& eye, const CVector& center, bool isMainCamera = true);
	// �f�X�g���N�^
	~CStageSelectCamera();

	// �X�V
	void Update() override;
};
#endif