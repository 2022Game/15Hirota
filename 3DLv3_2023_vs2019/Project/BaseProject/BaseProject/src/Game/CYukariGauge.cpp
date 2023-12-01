#include "CYukariGauge.h"
#include "Maths.h"
#include "CImage.h"


#define BAR_IMAGE "UI\\Gauge.png"

// フレームの線の幅
#define FRAME_BORDER	(1.0f)

// バーの横サイズ
#define NEW_BAR_SIZE_X	(5.0f)
// バーの縦サイズ
#define NEW_BAR_SIZE_Y	(1.0f)

// バーの横サイズ * 線の幅
#define BAR_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// バーの縦サイズ * 線の幅
#define BAR_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)

// ゲージポジション横
#define BARPOSITION_X		(0.0f)
// ゲージポジション縦
#define BARPOSITION_Z		(0.0f)

#define ENEMY_HEIGHT2 20.5f


CYukariGauge::CYukariGauge()
	: mMaxValue(50)
	, mValue(50)
{
	mpBarImage = new CBillBoardImage(BAR_IMAGE, ETag::eGauge, ETaskPriority::eEnemyGauge, 0, ETaskPauseType::eGame);
	mpBarImage->SetSize(CVector2(BAR_SIZE_X, BAR_SIZE_Y));
}

// デストラクタ
CYukariGauge::~CYukariGauge()
{

}

//void CYukariGauge::Setup(const CVector& pos, const CVector& dir)
//{
//
//}

// 更新処理
void CYukariGauge::Update()
{
	mpBarImage->Position(mPosition + CVector(0.0f, 20.0f, 0.0f));
	CDebugPrint::Print("Position: X=%f, Y=%f, Z=%f\n", mpBarImage->Position().X(), mpBarImage->Position().Y(), mpBarImage->Position().Z());


	// バーのサイズを最大値と現在地から求める
	float percent = Math::Clamp01((float)mValue / mMaxValue);
	CVector2 size = CVector2(BAR_SIZE_X, BAR_SIZE_Y);
	size.X(BAR_SIZE_X * percent);
	mpBarImage->SetSize(size);


	// HPの割合でバーの色を変更
	CColor color;
	// 10%以下
	if (percent <= 0.2f) color = CColor(1.0f, 0.0f, 0.0f);
	// 50%以下
	else if (percent <= 0.5f) color = CColor(0.9f, 0.3f, 0.5f);
	// それ以外
	else color = CColor(0.0f, 1.0f, 0.0f);
	// バーに色を設定
	mpBarImage->SetColor(color);
}

// 最大値
void CYukariGauge::SetMaxValue(int value)
{
	mMaxValue = value;
}

// 現在地を設定
void CYukariGauge::SetValue(int value)
{
	mValue = value;
}

void CYukariGauge::SetPor(float per)
{

}