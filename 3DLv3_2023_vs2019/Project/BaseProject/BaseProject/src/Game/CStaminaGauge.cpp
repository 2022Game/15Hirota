#include "CStaminaGauge.h"
#include "Maths.h"
#include "CImage.h"

#define STAMINA_IMAGE "UI\\Sutamina.png"

// CUIgaugeと一緒
// フレームの線の幅
#define FRAME_BORDER	(1.0f)
// バーの横サイズ
#define NEW_BAR_SIZE_X	(339.0f)
// バーの縦サイズ
#define NEW_BAR_SIZE_Y	(31.5f)


// スタミナの横サイズ * 線の幅
#define SUTAMINA_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// スタミナの縦サイズ * 線の幅
#define SUTAMINA_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)

// スタミナポジション横
#define SUTAMINAPOSITION_X	(237.5f)
// スタミナポジション縦
#define SUTAMINAPOSITION_Y	(100.0f)

CStaminaGauge::CStaminaGauge()
	: mMaxSutaminaValue(100)
	, mSutaminaValue(100)
{
	mpStaminaImage = new CImage(STAMINA_IMAGE);
	mpStaminaImage->SetSize(SUTAMINA_SIZE_X, SUTAMINA_SIZE_Y);
	mpStaminaImage->SetUV(0, 1, 1, 0);
}

CStaminaGauge::~CStaminaGauge()
{
}

void CStaminaGauge::Update()
{
	// スタミナゲージのポジション
	mpStaminaImage->SetPos(mPosition + CVector2(SUTAMINAPOSITION_X, SUTAMINAPOSITION_Y));
	mpStaminaImage->SetUV(0, 1, 1, 0);

	// スタミナのサイズを最大値と現在地から求める
	float percent_sutamina = Math::Clamp01((float)mSutaminaValue / mMaxSutaminaValue);
	CVector2 sizesutamina = CVector2(SUTAMINA_SIZE_X, SUTAMINA_SIZE_Y);
	sizesutamina.X(SUTAMINA_SIZE_X * percent_sutamina);
	mpStaminaImage->SetSize(sizesutamina);

	// スタミナの割合でバーの色を変更
	CColor colorsutamina;
	// 10%以下
	if (percent_sutamina <= 0.2f) colorsutamina = CColor(1.0f, 0.0f, 0.0f);
	// 50%以下
	else if (percent_sutamina <= 0.5f) colorsutamina = CColor(0.9f, 0.3f, 0.5f);
	// それ以外
	else colorsutamina = CColor(1.0f, 1.0f, 0.0f);
	// バーに色を設定
	mpStaminaImage->SetColor(colorsutamina);
}

// スタミナ最大値
void CStaminaGauge::SetSutaminaMaxValue(int value_st)
{
	mMaxSutaminaValue = value_st;
}

// スタミナ現在値
void CStaminaGauge::SetSutaminaValue(int value_st)
{
	mSutaminaValue = value_st;
}

void CStaminaGauge::SetPor(float per)
{

}