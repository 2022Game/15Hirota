#include "CSoldierFrame.h"
#include "Maths.h"
#include "CImage.h"

#define FRAME_IMAGE "UI\\Image_Gauge_Frame.png"

// フレームの線の幅
#define FRAME_BORDER	(1.0f)

// フレームの横サイズ
#define FRAME_SIZE_X	(90.0f)	//(50.0f)
// フレームの縦サイズ
#define FRAME_SIZE_Y	(16.0f)		//(32.0f)

CSoldierFrame::CSoldierFrame()
{
	mpFrameImage = new CImage(FRAME_IMAGE);
	mpFrameImage->SetSize(FRAME_SIZE_X, FRAME_SIZE_Y);
	mpFrameImage->SetUV(0, 0, 1, 1);
}

// デストラクタ
CSoldierFrame::~CSoldierFrame()
{

}

void CSoldierFrame::Update()
{
	// ゲージのフレームとバーの位置を設定（修正箇所）
	mpFrameImage->SetPos(mPosition);
}