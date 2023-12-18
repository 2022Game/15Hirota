#include "CUIGauge.h"
#include "Maths.h"
#include "CImage.h"

#define FRAME_IMAGE "UI\\Image_Gauge_Frame.png"
#define BAR_IMAGE "UI\\WhiteUI.png"

// フレームの線の幅
#define FRAME_BORDER	(1.0f)

// フレームの横サイズ
#define FRAME_SIZE_X	(426.0f)	//(50.0f)
// フレームの縦サイズ
#define FRAME_SIZE_Y	(62.0f)		//(32.0f)

// バーの横サイズ
#define NEW_BAR_SIZE_X	(339.0f)
// バーの縦サイズ
#define NEW_BAR_SIZE_Y	(31.5f)

// バーの横サイズ * 線の幅
#define BAR_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// バーの縦サイズ * 線の幅
#define BAR_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)

// フレームポジション横
#define FRAMEPOSITION_X		(400.0f)
// フレームポジション縦
#define FRAMEPOSITION_Y		(600.0f)

// ゲージポジション横
#define BARPOSITION_X		(488.5f)
// ゲージポジション縦
#define BARPOSITION_Y		(600.0f)

#define VERTICAL_SHAKE_AMOUNT 20.0f

#define CHANGE_SPEED 3.0f

CUIGauge::CUIGauge()
	: mMaxValue(100)
	, mValue(100)
{
	mpFrameImage = new CImage(FRAME_IMAGE);
	mpFrameImage->SetSize(FRAME_SIZE_X, FRAME_SIZE_Y);
	mpFrameImage->SetUV(0, 0, 1, 1);

	mpBarImage = new CImage(BAR_IMAGE);
	mpBarImage->SetSize(BAR_SIZE_X, BAR_SIZE_Y);
	mpBarImage->SetUV(438, 0, 500, 62);
}

// デストラクタ
CUIGauge::~CUIGauge()
{

}

// 更新処理
void CUIGauge::Update()
{
	//// ゲージのフレームとバーの位置を設定
	//mpFrameImage->SetPos(mPosition + CVector2(FRAMEPOSITION_X, FRAMEPOSITION_Y));
	//mpBarImage->SetPos(mPosition + CVector2(BARPOSITION_X, BARPOSITION_Y));


	//// バーのサイズを最大値と現在地から求める
	//float percent = Math::Clamp01((float)mValue / mMaxValue);
	//CVector2 size = CVector2(BAR_SIZE_X, BAR_SIZE_Y);
	//size.X(BAR_SIZE_X * percent);
	//mpBarImage->SetSize(size);


	//// HPの割合でバーの色を変更
	//CColor color;
	//// 10%以下
	//if (percent <= 0.2f) color = CColor(1.0f, 0.0f, 0.0f);
	//// 50%以下
	//else if (percent <= 0.5f) color = CColor(0.9f, 0.3f, 0.5f);
	//// それ以外
	//else color = CColor(0.0f, 1.0f, 0.0f);
	//// バーに色を設定
	//mpBarImage->SetColor(color);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//bool hpDecreased = fabs(targetPercent - currentPercent) > std::numeric_limits<float>::epsilon();

	// ゲージのフレームとバーの位置を設定
	mpFrameImage->SetPos(mPosition + CVector2(FRAMEPOSITION_X, FRAMEPOSITION_Y));
	mpBarImage->SetPos(mPosition + CVector2(BARPOSITION_X, BARPOSITION_Y));


	// バーのサイズを目標のサイズに向かって変化させる
	float targetPercent = Math::Clamp01((float)mValue / mMaxValue);
	float currentPercent = Math::Clamp01(mpBarImage->GetSize().X() / BAR_SIZE_X);
	float newPercent = Math::Lerp(currentPercent, targetPercent, Time::DeltaTime() * CHANGE_SPEED);

	
	// HPの割合でバーの色を変更
	CColor color;
	// HPが減少している場合は赤色に設定
	
	// ある程度の誤差を許容する値
	const float epsilon = 0.0001f;
	// ゲージを揺らす
	float verticalOffset = 0.0f;
	if (targetPercent < currentPercent - epsilon) {

		verticalOffset = Math::Rand(-1.5f, 1.5f) * VERTICAL_SHAKE_AMOUNT;
		color = CColor(1.0f, 0.0f, 0.0f);
	}
	// それ以外の場合はHPの割合に応じて色を設定
	else {
		// 10%以下
		if (targetPercent <= 0.2f) {
			color = CColor(1.0f, 0.0f, 0.0f);
		}
		// 50%以下
		else if (targetPercent <= 0.5f) {
			color = CColor(0.9f, 0.3f, 0.5f);
		}
		// それ以外
		else {
			color = CColor(0.0f, 1.0f, 0.0f);
		}
	}


	// バーに色を設定
	mpBarImage->SetColor(color);
	CVector2 position = mPosition + CVector2(BARPOSITION_X, BARPOSITION_Y + verticalOffset);
	mpBarImage->SetPos(position);
	CVector2 size = CVector2(BAR_SIZE_X * newPercent, BAR_SIZE_Y);
	mpBarImage->SetSize(size);

}

// 最大値
void CUIGauge::SetMaxValue(int value)
{
	mMaxValue = value;
}

// 現在地を設定
void CUIGauge::SetValue(int value)
{
	mValue = value;
}

void CUIGauge::SetPor(float per)
{

}