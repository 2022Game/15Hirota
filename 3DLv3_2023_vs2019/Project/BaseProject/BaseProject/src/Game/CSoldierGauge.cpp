#include "CSoldierGauge.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"

#define BAR_IMAGE "UI\\Gauge.png"

// �t���[���̐��̕�
#define FRAME_BORDER	(1.0f)
// �t���[���̉��T�C�Y
#define FRAME_SIZE_X	(90.0f)	//(50.0f)

// �o�[�̉��T�C�Y
#define NEW_BAR_SIZE_X	(71.5f)
// �o�[�̏c�T�C�Y
#define NEW_BAR_SIZE_Y	(8.0f)

// �o�[�̉��T�C�Y * ���̕�
#define BAR_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// �o�[�̏c�T�C�Y * ���̕�
#define BAR_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)


CSoldierGauge::CSoldierGauge()
	: mMaxValue(10)
	, mValue(10)
	, mCenterRatio(0.0f, 0.0f)
	, mScale(0.0f)
	, mIsShow(true)
{
	mpBarImage = new CImage(BAR_IMAGE);
	mpBarImage->SetSize(BAR_SIZE_X, BAR_SIZE_Y);
	mpBarImage->SetUV(438, 0, 500, 62);
	
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

void CSoldierGauge::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
	mpBarImage->SetCenter
	(
		0.0f,
		BAR_SIZE_Y * mCenterRatio.Y()
	);
}

// ���[���h���W��ݒ�
void CSoldierGauge::SetWorldPos(const CVector& worldPos)
{
	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// �ݒ肳�ꂽ���[���h���W���X�N���[�����W�ɕϊ�
	CVector screenPos = cam->WorldToScreenPos(worldPos);

	// �ݒ肳�ꂽ���[���h���W���J�����̔w��ł���΁A
	// �Q�[�W��\�����Ȃ�
	if (screenPos.Z() < 0.0f)
	{
		mIsShow = false;
		return;
	}

	// �Q�[�W�\��
	mIsShow = true;
	// ���߂��X�N���[�����W�����g�̍��W�ɐݒ�
	mPosition = screenPos;

	// �ݒ肳�ꂽ���[���h���W�ƃJ�����̋��������߂�
	float dist = (worldPos - cam->Position()).Length();

	// �J�������痣��邲�ƂɃX�P�[���l������������
	float ratio = Math::Clamp01((dist - 10.0f) / (50.0f, -10.0f));
	mScale = Math::Lerp(0.1f, 1.0f, ratio);
}

// �X�V����
void CSoldierGauge::Update()
{
	// �Q�[�W�̈ʒu��ݒ�
	CVector2 pos = mPosition;
	pos.X(pos.X() - FRAME_SIZE_X * mCenterRatio.X() * mScale);
	mpBarImage->SetPos(pos * mScale);


	// �Q�[�W�T�C�Y���ő�l�ƌ��ݒn���狁�߂�
	float percent = Math::Clamp01((float)mValue / mMaxValue);
	CVector2 size = CVector2(BAR_SIZE_X, BAR_SIZE_Y);
	size.X(BAR_SIZE_X * percent);
	mpBarImage->SetSize(size);

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