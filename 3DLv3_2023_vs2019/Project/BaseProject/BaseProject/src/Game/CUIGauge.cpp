#include "CUIGauge.h"
#include "Maths.h"
#include "CImage.h"

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

#define VERTICAL_SHAKE_AMOUNT 20.0f

#define CHANGE_SPEED 0.7f

#define DAMAGE_DELAY 0.1f


CUIGauge::CUIGauge()
    : mMaxValue(100)
    , mValue(100)
    , mElapsedTime(0.0f)
	, mGauge(false)
	, mDamaged(false)
	, mStartDamaged(false)
{
	mpFrameImage = new CImage("PFrame");
	mpFrameImage->SetSize(FRAME_SIZE_X, FRAME_SIZE_Y);
	mpFrameImage->SetUV(0, 0, 1, 1);

	mpDecreaseBarImage = new CImage("PBarImage");
	mpDecreaseBarImage->SetSize(BAR_SIZE_X, BAR_SIZE_Y);
	mpDecreaseBarImage->SetUV(438, 0, 500, 62);

	mpBarImage = new CImage("PBarImage");
	mpBarImage->SetSize(BAR_SIZE_X, BAR_SIZE_Y);
	mpBarImage->SetUV(438, 0, 500, 62);
}

// �f�X�g���N�^
CUIGauge::~CUIGauge()
{

}

// �t���[�����폜
void CUIGauge::Kill()
{
	CTask::Kill();
	mpBarImage->Kill();
	mpFrameImage->Kill();
	mpDecreaseBarImage->Kill();
}

// �\�����邩�ǂ�����ݒ�
void CUIGauge::SetShow(bool isShow)
{
	CTask::SetShow(isShow);

	// �Q�[�W�̕\���ݒ�Ɠ����ɁA
	// �Q�[�W�Ŏg�p����UI�̕\���ݒ���ύX����
	mpBarImage->SetShow(isShow);
	mpFrameImage->SetShow(isShow);
	mpDecreaseBarImage->SetShow(isShow);
}

// �X�V����
void CUIGauge::Update()
{
	// �Q�[�W�̍���
	mpDecreaseBarImage->SetPos(mPosition + CVector2(BARPOSITION_X, BARPOSITION_Y));
	// �o�[�̃T�C�Y��ڕW�̃T�C�Y�Ɍ������ĕω�������
	float targetPercent = Math::Clamp01((float)mValue / mMaxValue);
	float currentPercent = Math::Clamp01(mpDecreaseBarImage->GetSize().X() / BAR_SIZE_X);
	float newPercent = Math::Lerp(currentPercent, targetPercent, Time::DeltaTime() * CHANGE_SPEED);

	// HP�̊����Ńo�[�̐F��ύX
	CColor color2;
	// HP���������Ă���ꍇ�͐ԐF�ɐݒ�
	if (targetPercent < currentPercent)
	{
		mGauge = true;
		color2 = CColor(0.9f, 0.2f, 0.0f); // �ԐF�ɐݒ�
		if (mGauge)
		{
			// 2�b�o�ߌ�ɃT�C�Y���X�V
			// �o�[�̃T�C�Y���X�V
			CVector2 size = CVector2(BAR_SIZE_X * newPercent, BAR_SIZE_Y);
			mpDecreaseBarImage->SetSize(size);
		}
		else
		{
			CVector2 size2 = CVector2(BAR_SIZE_X * targetPercent, BAR_SIZE_Y);
			mpDecreaseBarImage->SetSize(size2);
		}
	}
	else
	{
		CVector2 size2 = CVector2(BAR_SIZE_X * targetPercent, BAR_SIZE_Y);
		mpDecreaseBarImage->SetSize(size2);
	}

	// �T�C�Y���ڕW�ɒB�����ꍇ�AmElapsedTime�����Z�b�g
	if (fabs(targetPercent - currentPercent) < 0.010000)
	{
		mGauge = false;
		mElapsedTime = 0.0f;
	}
	/*CDebugPrint::Print("mGauge: %s\n", mGauge ? "true" : "false");
	CDebugPrint::Print("mDamaged: %s\n", mDamaged ? "true" : "false");
	CDebugPrint::Print("mStartDamaged: %s\n", mStartDamaged ? "true" : "false");
	CDebugPrint::Print("mElapsedTime: %f\n", mElapsedTime);
	CDebugPrint::Print("targetPercent: %f\n", targetPercent);
	CDebugPrint::Print("currentPercent: %f\n", currentPercent);*/

	// �����ɐF��ݒ�
	mpDecreaseBarImage->SetColor(color2);

	CVector2 position = mPosition + CVector2(BARPOSITION_X, BARPOSITION_Y);
	mpDecreaseBarImage->SetPos(position);


	// �t���[���ʒu��ݒ�
	mpFrameImage->SetPos(mPosition + CVector2(FRAMEPOSITION_X, FRAMEPOSITION_Y));
	// �Q�[�W
	mpBarImage->SetPos(mPosition + CVector2(BARPOSITION_X, BARPOSITION_Y));

    // �Q�[�W�T�C�Y���ő�l�ƌ��ݒn���狁�߂�
    float percent = Math::Clamp01((float)mValue / mMaxValue);

	
	// HP�̊����ŃQ�[�W�̐F��ύX
	//CColor color;
	//// 10%�ȉ�
	//if (percent <= 0.2f) color = CColor(1.0f, 0.0f, 0.0f);
	//// 50%�ȉ�
	//else if (percent <= 0.5f) color = CColor(0.9f, 0.3f, 0.5f);
	//// ����ȊO
	//else color = CColor(0.0f, 1.0f, 0.0f);
	//// �Q�[�W�ɐF��ݒ�
	//mpBarImage->SetColor(color);
	mpBarImage->SetColor(CColor(0.0f, 1.0f, 0.0f));

    CVector2 size2 = CVector2(BAR_SIZE_X * percent, BAR_SIZE_Y);
    mpBarImage->SetSize(size2);
    CVector2 position2 = mPosition + CVector2(BARPOSITION_X, BARPOSITION_Y);
    mpBarImage->SetPos(position2);
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