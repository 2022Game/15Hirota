#include "CCutInCamera.h"
#include "CTaskManager.h"

CCutInCamera* CCutInCamera::spCutInCamera = nullptr;

// �R���X�g���N�^
CCutInCamera::CCutInCamera()
	: CCamera(CVector::zero, CVector::zero, false)
	, mIsPlaying(false)
{

}

// �f�X�g���N�^
CCutInCamera::~CCutInCamera()
{

}

// �J�b�g�C���J�n
bool CCutInCamera::Start()
{
	// ���łɃJ�b�g�C���J�������I���ɂȂ��Ă�����A�J�n���Ȃ�
	if (spCutInCamera != nullptr) return false;

	// �Đ����̃J�b�g�C���J�����Ɏ��g��ݒ�
	spCutInCamera = this;
	mIsPlaying = true;
	// ���݂̃J���������g�ɐݒ�
	SetCurrent(true);

	// �J�b�g�C���p�̃|�[�Y���Ăяo��
	CTaskManager::Instance()->Pause(PAUSE_CUTIN);

	return true;
}

// �J�b�g�C���I��
bool CCutInCamera::End()
{
	// ���g���J�b�g�C���Đ����łȂ���΁A��~���Ȃ�
	if (spCutInCamera != this) return false;

	// �Đ����̃J�b�g�C���J�������폜
	spCutInCamera = nullptr;
	mIsPlaying = false;
	// ���݂̃J����������폜
	SetCurrent(false);

	// �J�b�g�C���p�̃|�[�Y������
	CTaskManager::Instance()->UnPause(PAUSE_CUTIN);

	return true;
}

// �J�b�g�C���Đ������ǂ���
bool CCutInCamera::IsPlaying() const
{
	return mIsPlaying;
}

// �X�V
void CCutInCamera::Update()
{

}