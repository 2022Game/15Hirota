#include "CUIGauge.h"
#include "Maths.h"
#include "CImage.h"

#define FRAME_IMAGE "UI\\Image_Gauge_Frame.png"
#define BAR_IMAGE "UI\\Gauge.png"

// フレームの横サイズ
#define FRAME_SIZE_X (426.0f)	//(50.0f)
// フレームの縦サイズ
#define FRAME_SIZE_Y (62.0f)	//(32.0f)
// フレームの線の幅
#define FRAME_BORDER (2.0f)
// バーの横のサイズ
#define BAR_SIZE_X (FRAME_SIZE_X - FRAME_BORDER * 2.0f)
// バーの縦のサイズ
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

// デストラクタ
CUIGauge::~CUIGauge()
{

}

// 更新処理
void CUIGauge::Update()
{
	// ゲージのフレームとバーの位置を設定
	mpFrameImage->SetPos(mPosition);
	mpFrameImage->SetPos(mPosition + CVector2(FRAME_BORDER, FRAME_BORDER));

	// バーのサイズを最大値と現在地から求める
	float percent = Math::Clamp01((float)mValue / mMaxVsalue);
	CVector2 size = CVector2(BAR_SIZE_X, BAR_SIZE_Y);
	size.X(BAR_SIZE_X * percent);
	mpBarImage->SetSize(size);

	// HPの割合でバーの色を変更
	CColor color;
	if (percent <= 0.1f) color = CColor(1.0f, 0.0f, 0.0f);
	//　30%以下
	else if (percent <= 0.3f) color = CColor(1.0f, 1.0f, 0.0f);
	// それ以外
	else color = CColor(0.0f, 1.0f, 0.0f);
	// バーに色を設定
	mpBarImage->SetColor(color);
}

// 最大値
void CUIGauge::SetMaxValue(int value)
{
	mMaxVsalue = value;
}

// 現在地を設定
void CUIGauge::SetValue(int value)
{
	mValue = value;
}

void CUIGauge::SetPor(float per)
{

}