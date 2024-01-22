#include "CYukariFrame.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"
#include "CPlayer.h"


// �t���[���̐��̕�
#define FRAME_BORDER	(1.0f)

// �t���[���̉��T�C�Y
#define FRAME_SIZE_X	(100.0f)		//(50.0f)
// �t���[���̏c�T�C�Y
#define FRAME_SIZE_Y	(15.0f)		//(32.0f)


// �X�P�[���l�v�Z���̃J�����Ƃ̋����̍ŏ��l
#define SCALE_DIST_MIN 50.0f
// �X�P�[���l�v�Z���̃J�����Ƃ̋����̍ő�l
#define SCALE_DIST_MAX 100.0f
// �X�P�[���l�̍ŏ��l
#define SCALE_MIN 0.8f
// �X�P�[���l�̍ő�l
#define SCALE_MAX 1.0f


#define DISTANCE_MIN 0.5f
#define DISTANCE_MAX 10.0f

CYukariFrame::CYukariFrame()
	: mCenterRatio(0.0f, 0.0f)
	, mScale(0.0f)
{
	mpFrameImage = new CImage("YFrame");
	mpFrameImage->SetSize(FRAME_SIZE_X, FRAME_SIZE_Y);
	mpFrameImage->SetUV(0, 0, 1, 1);

}

// �f�X�g���N�^
CYukariFrame::~CYukariFrame()
{

}

// �t���[�����폜
void CYukariFrame::Kill()
{
	CTask::Kill();
	mpFrameImage->Kill();
}

// �\�����邩�ǂ�����ݒ�
void CYukariFrame::SetShow(bool isShow)
{
	CTask::SetShow(isShow);

	// �Q�[�W�̕\���ݒ�Ɠ����ɁA
	// �Q�[�W�Ŏg�p����UI�̂Ђ傶�ݒ���ύX����
	mpFrameImage->SetShow(isShow);
}

// ���S�ʒu�̊�����ݒ�
void CYukariFrame::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

// ���[���h���W��ݒ�
void CYukariFrame::SetWorldPos(const CVector& worldPos)
{
	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	CVector playerPos = CPlayer::Instance()->Position();

	// �ݒ肳�ꂽ���[���h���W���X�N���[�����W�ɕϊ�
	CVector screenPos = cam->WorldToScreenPos(worldPos);

	// �ݒ肳�ꂽ���[���h���W���J�����̔w��ł���΁A
	// �Q�[�W��\�����Ȃ�
	if (screenPos.Z() < 0.0f)
	{
		SetShow(false);
		return;
	}

	float distanceToPlayer = (worldPos - playerPos).Length();
	if (distanceToPlayer < 100.0f)
	{
		SetShow(true);
	}
	else
	{
		SetShow(false);
	}

	// ���߂��X�N���[�����W�����g�̍��W�ɐݒ�
	mPosition = screenPos;

	// �ݒ肳�ꂽ���[���h���W�ƃJ�����̋��������߂�
	float dist = (worldPos - cam->Position()).Length();

	// �J�������痣��邲�ƂɃX�P�[���l������������
	float ratio = Math::Clamp01((dist - SCALE_DIST_MIN) / (SCALE_DIST_MAX - SCALE_DIST_MIN));
	mScale = Math::Lerp(SCALE_MIN, SCALE_MAX, ratio);
}

void CYukariFrame::Update()
{
	// �t���[���ʒu��ݒ�
	//CVector2 pos = mPosition - CVector2(FRAME_SIZE_X, 0.0f) * 0.5f;
	mpFrameImage->SetPos(mPosition);
	mpFrameImage->SetSize(CVector2(FRAME_SIZE_X, FRAME_SIZE_Y) * mScale);
	mpFrameImage->SetShow(IsShow());


	// �t���[���̒��S�ʒu
	mpFrameImage->SetCenter
	(
		FRAME_SIZE_X * mCenterRatio.X() * mScale,
		FRAME_SIZE_Y * mCenterRatio.Y() * mScale
	);
}