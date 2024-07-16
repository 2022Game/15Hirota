#include "CSoldierGauge.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"
#include "CPlayer.h"


// �t���[���̐��̕�
#define FRAME_BORDER	(1.0f)
// �t���[���̉��T�C�Y
#define FRAME_SIZE_X	(100.0f)	//(50.0f)

// �o�[�̉��T�C�Y
#define NEW_BAR_SIZE_X	(80.0f)
// �o�[�̏c�T�C�Y
#define NEW_BAR_SIZE_Y	(7.5f)

// �o�[�̉��T�C�Y * ���̕�
#define BAR_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// �o�[�̏c�T�C�Y * ���̕�
#define BAR_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)

// �X�P�[���l�v�Z���̃J�����Ƃ̋����̍ŏ��l
#define SCALE_DIST_MIN 50.0f
// �X�P�[���l�v�Z���̃J�����Ƃ̋����̍ő�l
#define SCALE_DIST_MAX 200.0f
// �X�P�[���l�̍ŏ��l
#define SCALE_MIN 0.8f
// �X�P�[���l�̍ő�l
#define SCALE_MAX 1.0f


CSoldierGauge::CSoldierGauge()
	: mMaxValue(10)
	, mValue(10)
	, mCenterRatio(0.0f, 0.0f)
	, mScale(0.0f)
{
	mpBarImage = new CImage("SBar");
	mpBarImage->SetSize(BAR_SIZE_X, BAR_SIZE_Y);
	mpBarImage->SetUV(438, 0, 500, 62);
	// �ŏ��͔�\���ɂ��Ă���
	SetShow(false);
}
// �f�X�g���N�^
CSoldierGauge::~CSoldierGauge()
{
	
}

// �Q�[�W���폜
void CSoldierGauge::Kill()
{
	CTask::Kill();
	mpBarImage->Kill();
}

// �\�����邩�ǂ�����ݒ�
void CSoldierGauge::SetShow(bool isShow)
{
	CTask::SetShow(isShow);

	// �Q�[�W�̕\���ݒ�Ɠ����ɁA
	// �Q�[�W�Ŏg�p����UI�̕\���ݒ���ύX����
	mpBarImage->SetShow(isShow);
}

void CSoldierGauge::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

// ���[���h���W��ݒ�
void CSoldierGauge::SetWorldPos(const CVector& worldPos)
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
void CSoldierGauge::Update()
{
	// �Q�[�W�̈ʒu��ݒ�
	CVector2 pos = mPosition;
	pos.X(pos.X() - FRAME_SIZE_X * mCenterRatio.X() * mScale);
	mpBarImage->SetPos(pos + CVector2(0.0f,0.0f) * mScale);


	// �Q�[�W�T�C�Y���ő�l�ƌ��ݒn���狁�߂�
	float percent = Math::Clamp01((float)mValue / mMaxValue);
	CVector2 size = CVector2(BAR_SIZE_X * percent, BAR_SIZE_Y) * mScale;
	mpBarImage->SetSize(size);

	// �Q�[�W�̒��S�ʒu��ݒ�
	mpBarImage->SetCenter
	(
		0.0f,
		BAR_SIZE_Y * mCenterRatio.Y() * mScale
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
void CSoldierGauge::SetMaxValue(int value)
{
	mMaxValue = value;
}

// ���ݒn��ݒ�
void CSoldierGauge::SetValue(int value)
{
	mValue = value;
}

void CSoldierGauge::SetPor(float per)
{
}