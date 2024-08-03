#include "CPicoChanUI.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"
#include "CPlayer.h"

// �X�P�[���l�v�Z���̃J�����Ƃ̋����̍ŏ��l
#define SCALE_DIST_MIN 50.0f
// �X�P�[���l�v�Z���̃J�����Ƃ̋����̍ő�l
#define SCALE_DIST_MAX 200.0f
// �X�P�[���l�̍ŏ��l
#define SCALE_MIN 0.8f
// �X�P�[���l�̍ő�l
#define SCALE_MAX 1.0f

CPicoChanUI::CPicoChanUI()
	: mMaxValue(15)
	, mValue(15)
	, mCenterRatio(0.0f, 0.0f)
	, mScale(0.0f)
	, mGauge(false)
	, mElapsedTime(0.0f)
{
	mpFrameImage = new CImage("PicoFrame");
	mpFrameImage->SetSize(100.0f, 100.0f);
	mpFrameImage->SetUV(0, 0, 1, 1);

	mpBarImage = new CImage("PicoGauge");
	mpBarImage->SetSize(90.0f, 90.0f);
	mpBarImage->SetUV(0, 0, 1, 1);
	SetShow(false);
}

CPicoChanUI::~CPicoChanUI()
{

}

void CPicoChanUI::Kill()
{
	CTask::Kill();
	mpBarImage->Kill();
	mpFrameImage->Kill();
}

// �\�����邩�ǂ�����ݒ�
void CPicoChanUI::SetShow(bool isShow)
{
	CTask::SetShow(isShow);

	// �Q�[�W�̕\���ݒ�Ɠ����ɁA
	// �Q�[�W�Ŏg�p����UI�̕\���ݒ���ύX����
	mpBarImage->SetShow(isShow);
	mpFrameImage->SetShow(isShow);
}

void CPicoChanUI::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

// ���[���h���W��ݒ�
void CPicoChanUI::SetWorldPos(const CVector& worldPos)
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

	// ���߂��X�N���[�����W�����g�̍��W�ɐݒ�
	mPosition = screenPos;

	// �ݒ肳�ꂽ���[���h���W�ƃJ�����̋��������߂�
	float dist = (worldPos - cam->Position()).Length();

	// �J�����Ƃ̋�����������x�߂��ꍇ��
	if (dist <= SCALE_DIST_MAX)
	{
		// �J�������痣��邲�ƂɃX�P�[���l������������
		float ratio = Math::Clamp01((dist - SCALE_DIST_MIN) / (SCALE_DIST_MAX - SCALE_DIST_MIN));
		mScale = Math::Lerp(SCALE_MIN, SCALE_MAX, ratio);
		SetShow(true);
	}
	// �J�����Ƃ̋����������ꍇ�́A��\��
	else
	{
		SetShow(false);
	}
}

// �X�V����
void CPicoChanUI::Update()
{
	mpFrameImage->SetPos(mPosition);
	mpFrameImage->SetSize(CVector2(100.0f, 100.0f) * mScale);

	// �t���[���̒��S�ʒu
	mpFrameImage->SetCenter
	(
		100.0f * mCenterRatio.X() * mScale,
		100.0f * mCenterRatio.Y() * mScale
	);

	// �Q�[�W�̈ʒu��ݒ�
	CVector2 pos = mPosition;
	pos.X(pos.X() - 90.0f * mCenterRatio.X() * mScale);
	mpBarImage->SetPos(pos + CVector2(0.0f, 5.0f) * mScale);


	// �Q�[�W�T�C�Y���ő�l�ƌ��ݒn���狁�߂�
	float percent = Math::Clamp01((float)mValue / mMaxValue);
	CVector2 size = CVector2(90.0f * percent, 90.0f) * mScale;
	mpBarImage->SetSize(size);

	// �Q�[�W�̒��S�ʒu��ݒ�
	mpBarImage->SetCenter
	(
		0.0f,
		90.0f * mCenterRatio.Y() * mScale
	);

	// HP�̊����ŃQ�[�W�̐F��ύX
	CColor color;
	// 10%�ȉ�
	if (percent <= 0.2f) color = CColor(1.0f, 0.0f, 0.0f);
	// 50%�ȉ�
	else if (percent <= 0.5f) color = CColor(0.9f, 0.3f, 0.5f);
	// ����ȊO
	else color = CColor(0.0f, 1.0f, 0.0f);
	// �Q�[�W�ɐF��ݒ�
	mpBarImage->SetColor(color);
}

// �ő�l
void CPicoChanUI::SetMaxValue(int value)
{
	mMaxValue = value;
}

// ���ݒn��ݒ�
void CPicoChanUI::SetValue(int value)
{
	mValue = value;
}