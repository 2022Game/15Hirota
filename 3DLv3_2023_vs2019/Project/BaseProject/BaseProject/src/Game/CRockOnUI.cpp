#include "CRockOnUI.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CStageManager.h"

// �X�P�[���l�v�Z���̃J�����Ƃ̋����̍ŏ��l
#define SCALE_DIST_MIN 50.0f
// �X�P�[���l�v�Z���̃J�����Ƃ̋����̍ő�l
#define SCALE_DIST_MAX 200.0f
// �X�P�[���l�̍ŏ��l
#define SCALE_MIN 0.8f
// �X�P�[���l�̍ő�l
#define SCALE_MAX 1.0f

// �R���X�g���N�^
CRockOnUI::CRockOnUI(std::string path)
	: mCenterRatio(0.0f, 0.0f)
{
	// ���b�N�I���\�摜&���b�N�I���摜
	mpCanRockOn = new CImage
	(
		path.c_str(),
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eGame,
		false,
		false
	);
	CVector2 size(100.0f, 100.0f);
	mpCanRockOn->SetSize(size);
	mpCanRockOn->SetCenter(size * 0.5f);
	SetShow(false);
}

// �f�X�g���N�^
CRockOnUI::~CRockOnUI()
{
	SAFE_DELETE(mpCanRockOn);
}

// �폜
void CRockOnUI::Kill()
{
	CTask::Kill();
}

// �\�����邩�ǂ�����ݒ�
void CRockOnUI::SetShow(bool isShow)
{
	CTask::SetShow(isShow);

	// �Q�[�W�̕\���ݒ�Ɠ����ɁA
	// �Q�[�W�Ŏg�p����UI�̕\���ݒ���ύX����
	mpCanRockOn->SetShow(isShow);
}

// ���S���W��ݒ�
void CRockOnUI::SetCeneterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

// ���[���h���W��ݒ�
void CRockOnUI::SetWorldPos(const CVector& worldpos)
{
	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// �ݒ肳�ꂽ���[���h���W���X�N���[�����W�ɕϊ�
	CVector screenPos = cam->WorldToScreenPos(worldpos);

	// �ݒ肳�ꂽ���[���h���W���J�����̔w��ł���΁A
	// �Q�[�W��\�����Ȃ�
	if (screenPos.Z() < 0.0f)
	{
		SetShow(false);
		printf("ssetshow:%s\n", IsShow() ? "true" : "false");
		return;
	}

	//// �X�N���[�����W���\���\�͈͓��ł���Ε\��
	//if (screenPos.X() >= 0.0f && screenPos.X() <= 1.0f && screenPos.Y() >= 0.0f && screenPos.Y() <= 1.0f)
	//{
	//	SetShow(true);
	//}
	//else
	//{
	//	SetShow(false);
	//}

	// ���߂��X�N���[�����W�����g�̍��W�ɐݒ�
	mPosition = screenPos;
}

// �X�V����
void CRockOnUI::Update()
{
	mpCanRockOn->SetPos(mPosition);
	//mpCanRockOn->SetSize(CVector2(50.0f, 50.0f) * mScale);

	//// �t���[���̒��S�ʒu
	//mpCanRockOn->SetCenter
	//(
	//	50.0f * mCenterRatio.X() * mScale,
	//	50.0f * mCenterRatio.Y() * mScale
	//);
	mpCanRockOn->SetShow(IsShow());
}

// �`�揈��
void CRockOnUI::Render()
{
	mpCanRockOn->Render();
}
