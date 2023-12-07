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
{
	mpFrameImage = new CImage(FRAME_IMAGE);
	mpFrameImage->SetSize(FRAME_SIZE_X, FRAME_SIZE_Y);
	mpFrameImage->SetUV(0, 0, 1, 1);
}

// �f�X�g���N�^
CSoldierFrame::~CSoldierFrame()
{

}

void CSoldierFrame::Update()
{
	// �Q�[�W�̃t���[���ƃo�[�̈ʒu��ݒ�i�C���ӏ��j
	mpFrameImage->SetPos(mPosition);
}