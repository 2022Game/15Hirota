#include "CStaminaGauge.h"
#include "Maths.h"
#include "CImage.h"

#define STAMINA_IMAGE "UI\\Sutamina.png"

// CUIgauge�ƈꏏ
// �t���[���̐��̕�
#define FRAME_BORDER	(1.0f)
// �o�[�̉��T�C�Y
#define NEW_BAR_SIZE_X	(339.0f)
// �o�[�̏c�T�C�Y
#define NEW_BAR_SIZE_Y	(31.5f)


// �X�^�~�i�̉��T�C�Y * ���̕�
#define SUTAMINA_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// �X�^�~�i�̏c�T�C�Y * ���̕�
#define SUTAMINA_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)

// �X�^�~�i�|�W�V������
#define SUTAMINAPOSITION_X	(488.5f)
// �X�^�~�i�|�W�V�����c
#define SUTAMINAPOSITION_Y	(632.0f)

#define VERTICAL_SHAKE_AMOUNT 20.0f

#define CHANGE_SPEED 3.0f

CStaminaGauge::CStaminaGauge()
	: mMaxSutaminaValue(150)
	, mSutaminaValue(150)
{
	mpStaminaImage = new CImage("PStamina");
	mpStaminaImage->SetSize(SUTAMINA_SIZE_X, SUTAMINA_SIZE_Y);
	mpStaminaImage->SetUV(0, 1, 1, 0);
}

CStaminaGauge::~CStaminaGauge()
{
}

// �t���[�����폜
void CStaminaGauge::Kill()
{
	CTask::Kill();
	mpStaminaImage->Kill();
}

// �\�����邩�ǂ�����ݒ�
void CStaminaGauge::SetShow(bool isShow)
{
	CTask::SetShow(isShow);

	// �Q�[�W�̕\���ݒ�Ɠ����ɁA
	// �Q�[�W�Ŏg�p����UI�̕\���ݒ���ύX����
	mpStaminaImage->SetShow(isShow);
}

void CStaminaGauge::Update()
{
	// �X�^�~�i�Q�[�W�̃|�W�V����
	mpStaminaImage->SetPos(mPosition + CVector2(SUTAMINAPOSITION_X, SUTAMINAPOSITION_Y));
	mpStaminaImage->SetUV(0, 1, 1, 0);

	// �X�^�~�i�̃T�C�Y���ő�l�ƌ��ݒn���狁�߂�
	float percent_sutamina = Math::Clamp01((float)mSutaminaValue / mMaxSutaminaValue);
	CVector2 sizesutamina = CVector2(SUTAMINA_SIZE_X, SUTAMINA_SIZE_Y);
	sizesutamina.X(SUTAMINA_SIZE_X * percent_sutamina);
	mpStaminaImage->SetSize(sizesutamina);

	// �X�^�~�i�̊����Ńo�[�̐F��ύX
	CColor colorsutamina;
	// 10%�ȉ�
	if (percent_sutamina <= 0.2f) colorsutamina = CColor(1.0f, 0.0f, 0.0f);
	// 50%�ȉ�
	else if (percent_sutamina <= 0.5f) colorsutamina = CColor(0.9f, 0.3f, 0.5f);
	// ����ȊO
	else colorsutamina = CColor(1.0f, 1.0f, 0.0f);
	// �o�[�ɐF��ݒ�
	mpStaminaImage->SetColor(colorsutamina);

	////////////////////////////////////////////////////////////////////////////////////////////////

	//// �X�^�~�i�Q�[�W�̃|�W�V����
	//mpStaminaImage->SetPos(mPosition + CVector2(SUTAMINAPOSITION_X, SUTAMINAPOSITION_Y));


	//// �o�[�̃T�C�Y��ڕW�̃T�C�Y�Ɍ������ĕω�������
	//float targetPercent = Math::Clamp01((float)mSutaminaValue / mMaxSutaminaValue);
	//float currentPercent = Math::Clamp01(mpStaminaImage->GetSize().X() / NEW_BAR_SIZE_X);
	//float newPercent = Math::Lerp(currentPercent, targetPercent, Time::DeltaTime() * CHANGE_SPEED);

	//CColor colorSutamina;

	//const float epsilon = 0.0001f;
	//float verticalOffset = 0.0f;
	//if (targetPercent < currentPercent - epsilon) {

	//	verticalOffset = Math::Rand(-1.5f, 1.5f) * VERTICAL_SHAKE_AMOUNT;
	//}
	//else {
	//	// 10%�ȉ�
	//	if (targetPercent <= 0.2f) {
	//		colorSutamina = CColor(1.0f, 0.0f, 0.0f);
	//	}
	//	// 50%�ȉ�
	//	else if (targetPercent <= 0.5f) {
	//		colorSutamina = CColor(0.9f, 0.3f, 0.5f);
	//	}
	//	// ����ȊO
	//	else {
	//		colorSutamina = CColor(0.0f, 1.0f, 0.0f);
	//	}
	//}


	//// �o�[�ɐF��ݒ�
	//mpStaminaImage->SetColor(colorSutamina);
	//CVector2 position = mPosition + CVector2(SUTAMINAPOSITION_X, SUTAMINAPOSITION_Y + verticalOffset);
	//mpStaminaImage->SetPos(position);
	//CVector2 size = CVector2(SUTAMINA_SIZE_X * newPercent, SUTAMINA_SIZE_Y);
	//mpStaminaImage->SetSize(size);
}

// �X�^�~�i�ő�l
void CStaminaGauge::SetSutaminaMaxValue(int value_st)
{
	mMaxSutaminaValue = value_st;
}

// �X�^�~�i���ݒl
void CStaminaGauge::SetSutaminaValue(int value_st)
{
	mSutaminaValue = value_st;
}

void CStaminaGauge::SetPor(float per)
{

}