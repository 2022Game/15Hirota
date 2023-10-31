#include "CUIGauge.h"
#include "Maths.h"
#include "CImage.h"

#define FRAME_IMAGE "UI\\Image_Gauge_Frame.png"
#define BAR_IMAGE "UI\\Gauge.png"

// �t���[���̉��T�C�Y
#define FRAME_SIZE_X (426.0f)	//(50.0f)
// �t���[���̏c�T�C�Y
#define FRAME_SIZE_Y (62.0f)	//(32.0f)
// �t���[���̐��̕�
#define FRAME_BORDER (2.0f)
// �o�[�̉��̃T�C�Y
#define BAR_SIZE_X (FRAME_SIZE_X - FRAME_BORDER * 2.0f)
// �o�[�̏c�̃T�C�Y
#define BAR_SIZE_Y (FRAME_SIZE_Y - FRAME_BORDER * 2.0f)

CUIGauge::CUIGauge()
	: mMaxVsalue(100)
	, mValue(100)
{
	mpFrameImage = new CImage(FRAME_IMAGE);
	mpFrameImage->SetSize(FRAME_SIZE_X, FRAME_SIZE_Y);
	mpFrameImage->SetUV(0, 1, 1, 0);

	mpBarImage = new CImage(BAR_IMAGE);
	mpBarImage->SetSize(BAR_SIZE_X, BAR_SIZE_Y);
}

// �f�X�g���N�^
CUIGauge::~CUIGauge()
{

}

// �X�V����
void CUIGauge::Update()
{
	// �Q�[�W�̃t���[���ƃo�[�̈ʒu��ݒ�
	mpFrameImage->SetPos(mPosition);
	mpFrameImage->SetPos(mPosition + CVector2(FRAME_BORDER, FRAME_BORDER));

	// �o�[�̃T�C�Y���ő�l�ƌ��ݒn���狁�߂�
	float percent = Math::Clamp01((float)mValue / mMaxVsalue);
	CVector2 size = CVector2(BAR_SIZE_X, BAR_SIZE_Y);
	size.X(BAR_SIZE_X * percent);
	mpBarImage->SetSize(size);

	// HP�̊����Ńo�[�̐F��ύX
	CColor color;
	if (percent <= 0.1f) color = CColor(1.0f, 0.0f, 0.0f);
	//�@30%�ȉ�
	else if (percent <= 0.3f) color = CColor(1.0f, 1.0f, 0.0f);
	// ����ȊO
	else color = CColor(0.0f, 1.0f, 0.0f);
	// �o�[�ɐF��ݒ�
	mpBarImage->SetColor(color);
}

// �ő�l
void CUIGauge::SetMaxValue(int value)
{
	mMaxVsalue = value;
}

// ���ݒn��ݒ�
void CUIGauge::SetValue(int value)
{
	mValue = value;
}

void CUIGauge::SetPor(float per)
{

}