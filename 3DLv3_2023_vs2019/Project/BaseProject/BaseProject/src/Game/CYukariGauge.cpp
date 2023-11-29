#include "CYukariGauge.h"
#include "Maths.h"
#include "CImage.h"


#define BAR_IMAGE "UI\\Gauge.png"

// �t���[���̐��̕�
#define FRAME_BORDER	(1.0f)

// �o�[�̉��T�C�Y
#define NEW_BAR_SIZE_X	(5.0f)
// �o�[�̏c�T�C�Y
#define NEW_BAR_SIZE_Y	(1.0f)

// �o�[�̉��T�C�Y * ���̕�
#define BAR_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// �o�[�̏c�T�C�Y * ���̕�
#define BAR_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)

// �Q�[�W�|�W�V������
#define BARPOSITION_X		(0.0f)
// �Q�[�W�|�W�V�����c
#define BARPOSITION_Z		(0.0f)

#define ENEMY_HEIGHT2 20.5f


CYukariGauge::CYukariGauge()
	: CBillBoardImage(BAR_IMAGE, ETag::eGauge, ETaskPriority::eEnemyGauge, 0, ETaskPauseType::eGame)
	, mMaxValue(50)
	, mValue(50)
{
	
}

// �f�X�g���N�^
CYukariGauge::~CYukariGauge()
{

}

// �X�V����
void CYukariGauge::Update()
{
	//CDebugPrint::Print("Position: X=%f, Y=%f, Z=%f\n", mpBarImage->Position().X(), mpBarImage->Position().Y(), mpBarImage->Position().Z());

	//// �o�[�̃T�C�Y���ő�l�ƌ��ݒn���狁�߂�
	//float percent = Math::Clamp01((float)mValue / mMaxValue);
	//CVector2 size = CVector2(BAR_SIZE_X, BAR_SIZE_Y);
	//size.X(BAR_SIZE_X * percent);
	//mpBarImage->SetSize(size);

	//// HP�̊����Ńo�[�̐F��ύX
	//CColor color;
	//// 10%�ȉ�
	//if (percent <= 0.2f) color = CColor(1.0f, 0.0f, 0.0f);
	//// 50%�ȉ�
	//else if (percent <= 0.5f) color = CColor(0.9f, 0.3f, 0.5f);
	//// ����ȊO
	//else color = CColor(0.0f, 1.0f, 0.0f);
	//// �o�[�ɐF��ݒ�
	//mpBarImage->SetColor(color);
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