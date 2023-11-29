#include "CYukariGauge.h"
#include "Maths.h"
#include "CImage.h"

#define FRAME_IMAGE "UI\\Image_Gauge_Frame.png"
#define BAR_IMAGE "UI\\Gauge.png"

// �t���[���̐��̕�
#define FRAME_BORDER	(1.0f)

// �o�[�̉��T�C�Y
#define NEW_BAR_SIZE_X	(339.0f)
// �o�[�̏c�T�C�Y
#define NEW_BAR_SIZE_Y	(31.5f)

// �o�[�̉��T�C�Y * ���̕�
#define BAR_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// �o�[�̏c�T�C�Y * ���̕�
#define BAR_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)

// �Q�[�W�|�W�V������
#define BARPOSITION_X		(488.5f)
// �Q�[�W�|�W�V�����c
#define BARPOSITION_Y		(600.0f)

#define ENEMY_HEIGHT2 20.0f


CYukariGauge::CYukariGauge()
	: CBillBoardImage("UI\\Gauge.png", ETag::eGauge, ETaskPriority::eUI, 0, ETaskPauseType::eGame)
	, mMaxValue(100)
	, mValue(100)
{

}

// �f�X�g���N�^
CYukariGauge::~CYukariGauge()
{

}

// �X�V����
void CYukariGauge::Update()
{
	mpBarImage->SetSize(CVector2(BAR_SIZE_X, BAR_SIZE_Y));
	mpBarImage->SetSize(CVector2(5.0f, 1.0f));
	mpBarImage->Position(Position() + CVector(0.0f, ENEMY_HEIGHT2, 0.0f));
	

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
void CYukariGauge::SetMaxValue(int value)
{
	mMaxValue = value;
}

// ���ݒn��ݒ�
void CYukariGauge::SetValue(int value)
{
	mValue = value;
}

void CYukariGauge::SetPor(float per)
{

}