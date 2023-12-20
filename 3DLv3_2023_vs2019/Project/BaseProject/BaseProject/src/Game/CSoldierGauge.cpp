#include "CSoldierGauge.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"

#define BAR_IMAGE "UI\\Gauge.png"

// フレームの線の幅
#define FRAME_BORDER	(1.0f)
// フレームの横サイズ
#define FRAME_SIZE_X	(200.0f)	//(50.0f)

// バーの横サイズ
#define NEW_BAR_SIZE_X	(135.0f)
// バーの縦サイズ
#define NEW_BAR_SIZE_Y	(12.5f)

// バーの横サイズ * 線の幅
#define BAR_SIZE_X (NEW_BAR_SIZE_X - FRAME_BORDER) //*2.0f
// バーの縦サイズ * 線の幅
#define BAR_SIZE_Y (NEW_BAR_SIZE_Y - FRAME_BORDER)

// スケール値計算時のカメラとの距離の最小値
#define SCALE_DIST_MIN 50.0f
// スケール値計算時のカメラとの距離の最大値
#define SCALE_DIST_MAX 100.0f
// スケール値の最小値
#define SCALE_MIN 0.8f
// スケール値の最大値
#define SCALE_MAX 1.0f


CSoldierGauge::CSoldierGauge()
	: mMaxValue(10)
	, mValue(10)
	, mCenterRatio(0.0f, 0.0f)
	, mScale(0.0f)
{
	mpBarImage = new CImage(BAR_IMAGE);
	mpBarImage->SetSize(BAR_SIZE_X, BAR_SIZE_Y);
	mpBarImage->SetUV(438, 0, 500, 62);
	
}
// デストラクタ
CSoldierGauge::~CSoldierGauge()
{
	
}

// ゲージを削除
void CSoldierGauge::Kill()
{
	CTask::Kill();
	mpBarImage->Kill();
}

void CSoldierGauge::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

// ワールド座標を設定
void CSoldierGauge::SetWorldPos(const CVector& worldPos)
{
	// 現在のカメラを取得
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// 設定されたワールド座標をスクリーン座標に変換
	CVector screenPos = cam->WorldToScreenPos(worldPos);

	// 設定されたワールド座標がカメラの背後であれば、
	// ゲージを表示しない
	if (screenPos.Z() < 0.0f)
	{
		SetShow(false);
		return;
	}

	
	// ゲージ表示
	SetShow(true);
	// 求めたスクリーン座標を自身の座標に設定
	mPosition = screenPos;

	// 設定されたワールド座標とカメラの距離を求める
	float dist = (worldPos - cam->Position()).Length();

	// カメラから離れるごとにスケール値を小さくする
	float ratio = Math::Clamp01((dist - SCALE_DIST_MIN) / (SCALE_DIST_MAX -SCALE_DIST_MIN));
	mScale = Math::Lerp(SCALE_MIN, SCALE_MAX, ratio);
}

// 更新処理
void CSoldierGauge::Update()
{
	// ゲージの位置を設定
	CVector2 pos = mPosition;
	pos.X(pos.X() - FRAME_SIZE_X * mCenterRatio.X() * mScale);
	mpBarImage->SetPos(pos + CVector2(0.0f,0.0f) * mScale);


	// ゲージサイズを最大値と現在地から求める
	float percent = Math::Clamp01((float)mValue / mMaxValue);
	CVector2 size = CVector2(BAR_SIZE_X * percent, BAR_SIZE_Y) * mScale;
	mpBarImage->SetSize(size);

	// ゲージの中心位置を設定
	mpBarImage->SetCenter
	(
		0.0f,
		BAR_SIZE_Y * mCenterRatio.Y() * mScale
	);

	// HPの割合でゲージの色を変更
	CColor color;
	// 10%以下
	if (percent <= 0.2f) color = CColor(1.0f, 0.0f, 0.0f);
	// 50%以下
	else if (percent <= 0.5f) color = CColor(0.9f, 0.3f, 0.5f);
	// それ以外
	else color = CColor(0.0f, 1.0f, 0.0f);
	// ゲージに色を設定
	mpBarImage->SetColor(color);
}

// 最大値
void CSoldierGauge::SetMaxValue(int value)
{
	mMaxValue = value;
}

// 現在地を設定
void CSoldierGauge::SetValue(int value)
{
	mValue = value;
}

void CSoldierGauge::SetPor(float per)
{
}