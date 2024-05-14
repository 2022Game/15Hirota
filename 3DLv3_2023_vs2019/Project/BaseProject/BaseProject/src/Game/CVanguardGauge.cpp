#include "CVanguardGauge.h"
#include "Maths.h"
#include "CImage.h"
#include "CPlayer.h"

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

#define CHANGE_SPEED 3.0f


CVanguardGauge::CVanguardGauge()
	: mMaxValue(100)
	, mValue(100)
	, mScale(0.0f)
{
	mpBarImage = new CImage("PBarImage");
	mpBarImage->SetSize(BAR_SIZE_X, BAR_SIZE_Y);
	mpBarImage->SetUV(438, 0, 500, 62);
}

// �f�X�g���N�^
CVanguardGauge::~CVanguardGauge()
{

}

// �t���[�����폜
void CVanguardGauge::Kill()
{
	CTask::Kill();
	mpBarImage->Kill();
}

// �\�����邩�ǂ�����ݒ�
void CVanguardGauge::SetShow(bool isShow)
{
	CTask::SetShow(isShow);

	// �Q�[�W�̕\���ݒ�Ɠ����ɁA
	// �Q�[�W�Ŏg�p����UI�̕\���ݒ���ύX����
	mpBarImage->SetShow(isShow);
}


// �X�V����
void CVanguardGauge::Update()
{
	// �Q�[�W�̃t���[���ƃo�[�̈ʒu��ݒ�
	mpBarImage->SetPos(mPosition + CVector2(BARPOSITION_X, 10.0f));


	// �o�[�̃T�C�Y��ڕW�̃T�C�Y�Ɍ������ĕω�������
	float targetPercent = Math::Clamp01((float)mValue / mMaxValue);
	float currentPercent = Math::Clamp01(mpBarImage->GetSize().X() / BAR_SIZE_X);
	float newPercent = Math::Lerp(currentPercent, targetPercent, Time::DeltaTime() * CHANGE_SPEED);


	// HP�̊����Ńo�[�̐F��ύX
	CColor color;
	// HP���������Ă���ꍇ�͐ԐF�ɐݒ�

	// ������x�̌덷�����e����l
	const float epsilon = 0.0001f;
	// �Q�[�W��h�炷
	float verticalOffset = 0.0f;
	if (targetPercent < currentPercent - epsilon) {

		verticalOffset = Math::Rand(-1.5f, 1.5f) * VERTICAL_SHAKE_AMOUNT;
		color = CColor(1.0f, 0.0f, 0.0f);
	}
	// ����ȊO�̏ꍇ��HP�̊����ɉ����ĐF��ݒ�
	else {
		// 10%�ȉ�
		if (targetPercent <= 0.2f) {
			color = CColor(1.0f, 0.0f, 0.0f);
		}
		// 50%�ȉ�
		else if (targetPercent <= 0.5f) {
			color = CColor(0.9f, 0.3f, 0.5f);
		}
		// ����ȊO
		else {
			color = CColor(0.0f, 1.0f, 0.0f);
		}
	}


	// �o�[�ɐF��ݒ�
	mpBarImage->SetColor(color);
	CVector2 position = mPosition + CVector2(BARPOSITION_X, 10.0f + verticalOffset);
	mpBarImage->SetPos(position);
	CVector2 size = CVector2(BAR_SIZE_X * newPercent, BAR_SIZE_Y);
	mpBarImage->SetSize(size);

}

// ���[���h���W��ݒ�
void CVanguardGauge::SetWorldPos(const CVector& worldPos)
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
	if (dist <= 130.0f)
	{
		// �J�������痣��邲�ƂɃX�P�[���l������������
		float ratio = Math::Clamp01((dist - 50.0f) / (130.0f - 50.0f));
		mScale = Math::Lerp(0.8f, 1.0f, ratio);
		SetShow(true);
	}
	// �J�����Ƃ̋����������ꍇ�́A��\��
	else
	{
		SetShow(false);
	}

}

// �ő�l
void CVanguardGauge::SetMaxValue(int value)
{
	mMaxValue = value;
}

// ���ݒn��ݒ�
void CVanguardGauge::SetValue(int value)
{
	mValue = value;
}

void CVanguardGauge::SetPor(float per)
{

}