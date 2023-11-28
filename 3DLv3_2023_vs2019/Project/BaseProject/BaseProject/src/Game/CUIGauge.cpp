#include "CUIGauge.h"
#include "Maths.h"
#include "CImage.h"

#define FRAME_IMAGE "UI\\Image_Gauge_Frame.png"
#define BAR_IMAGE "UI\\Gauge.png"

// �t���[���̐��̕�
#define FRAME_BORDER	(1.0f)

// �t���[���̉��T�C�Y
#define FRAME_SIZE_X	(426.0f)	//(50.0f)
// �t���[���̏c�T�C�Y
#define FRAME_SIZE_Y	(62.0f)		//(32.0f)

// �o�[�̉��T�C�Y
#define NEW_BAR_SIZE_X	(339.0f)
// �o�[�̏c�T�C�Y
#define NEW_BAR_SIZE_Y	(31.5f)

// �o�[�̉��T�C�Y * ���̕�
#define BAR_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// �o�[�̏c�T�C�Y * ���̕�
#define BAR_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)

// �t���[���|�W�V������
#define FRAMEPOSITION_X		(400.0f)
// �t���[���|�W�V�����c
#define FRAMEPOSITION_Y		(600.0f)

// �Q�[�W�|�W�V������
#define BARPOSITION_X		(488.5f)
// �Q�[�W�|�W�V�����c
#define BARPOSITION_Y		(600.0f)


CUIGauge::CUIGauge()
	: mMaxValue(100)
	, mValue(100)
{
	mpFrameImage = new CImage(FRAME_IMAGE);
	mpFrameImage->SetSize(FRAME_SIZE_X, FRAME_SIZE_Y);
	mpFrameImage->SetUV(0, 0, 1, 1);

	mpBarImage = new CImage(BAR_IMAGE);
	mpBarImage->SetSize(BAR_SIZE_X, BAR_SIZE_Y);
	mpBarImage->SetUV(438, 0, 500, 62);
}

// �f�X�g���N�^
CUIGauge::~CUIGauge()
{

}

// �X�V����
void CUIGauge::Update()
{
	// �Q�[�W�̃t���[���ƃo�[�̈ʒu��ݒ�
	mpFrameImage->SetPos(mPosition + CVector2(FRAMEPOSITION_X, FRAMEPOSITION_Y));
	mpBarImage->SetPos(mPosition + CVector2(BARPOSITION_X, BARPOSITION_Y));


	// �o�[�̃T�C�Y���ő�l�ƌ��ݒn���狁�߂�
	float percent = Math::Clamp01((float)mValue / mMaxValue);
	CVector2 size = CVector2(BAR_SIZE_X, BAR_SIZE_Y);
	size.X(BAR_SIZE_X * percent);
	mpBarImage->SetSize(size);

	// HP�̊����Ńo�[�̐F��ύX
	CColor color;
	// 10%�ȉ�
	if (percent <= 0.2f) color = CColor(1.0f, 0.0f, 0.0f);
	// 50%�ȉ�
	else if (percent <= 0.5f) color = CColor(0.9f, 0.3f, 0.5f);
	// ����ȊO
	else color = CColor(0.0f, 1.0f, 0.0f);
	// �o�[�ɐF��ݒ�
	mpBarImage->SetColor(color);
}

// �ő�l
void CUIGauge::SetMaxValue(int value)
{
	mMaxValue = value;
}

// ���ݒn��ݒ�
void CUIGauge::SetValue(int value)
{
	mValue = value;
}

void CUIGauge::SetPor(float per)
{

}