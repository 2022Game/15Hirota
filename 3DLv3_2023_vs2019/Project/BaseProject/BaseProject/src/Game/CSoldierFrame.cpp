#include "CSoldierFrame.h"
#include "Maths.h"
#include "CImage.h"

#define FRAME_IMAGE "UI\\Image_Gauge_Frame.png"

// �t���[���̐��̕�
#define FRAME_BORDER	(1.0f)

// �t���[���̉��T�C�Y
#define FRAME_SIZE_X	(90.0f)	//(50.0f)
// �t���[���̏c�T�C�Y
#define FRAME_SIZE_Y	(16.0f)		//(32.0f)

CSoldierFrame::CSoldierFrame()
	: mCenterRatio(0.0f,0.0f)
{
	mpFrameImage = new CImage(FRAME_IMAGE);
	mpFrameImage->SetSize(FRAME_SIZE_X, FRAME_SIZE_Y);
	mpFrameImage->SetUV(0, 0, 1, 1);
	
}

// �f�X�g���N�^
CSoldierFrame::~CSoldierFrame()
{
	
}

// �t���[�����폜
void CSoldierFrame::Kill()
{
	CTask::Kill();
	mpFrameImage->Kill();
}

// ���S�ʒu�̊�����ݒ�
void CSoldierFrame::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
	mpFrameImage->SetCenter
	(
		FRAME_SIZE_X * mCenterRatio.X(),
		FRAME_SIZE_Y * mCenterRatio.Y()
	);
}

void CSoldierFrame::Update()
{
	// �t���[���ʒu��ݒ�
	//CVector2 pos = mPosition - CVector2(FRAME_SIZE_X, 0.0f) * 0.5f;
	mpFrameImage->SetPos(mPosition);
}