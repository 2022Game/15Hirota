#include "CStageSelectCamera.h"
#include "CInput.h"

// �R���X�g���N�^
CStageSelectCamera::CStageSelectCamera(const CVector& eye, const CVector& center, bool isMainCamera)
	: CCamera(eye, center, isMainCamera)
{
}

// �f�X�g���N�^
CStageSelectCamera::~CStageSelectCamera()
{
}

// �X�V
void CStageSelectCamera::Update()
{
	// �J�����̃x�[�X�̍X�V����
	CCamera::Update();
}