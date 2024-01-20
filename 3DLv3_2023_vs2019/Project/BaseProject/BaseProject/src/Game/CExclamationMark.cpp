#include "CExclamationMark.h"
#include "Maths.h"
#include "CImage.h"
#include "CPlayer.h"
#include "CSoldier.h"

// スケール値計算時のカメラとの距離の最小値
#define SCALE_DIST_MIN 50.0f
// スケール値計算時のカメラとの距離の最大値
#define SCALE_DIST_MAX 100.0f
// スケール値の最小値
#define SCALE_MIN 0.8f
// スケール値の最大値
#define SCALE_MAX 1.0f

// コンストラクタ
CExclamationMark::CExclamationMark()
	: mScale(0.0f)
	, mCenterRatio(0.0f, 0.0f)
{
	// ビックリマーク画像取得
	mpExclamationMark = new CImage("ExclamationMark");
	mpExclamationMark->SetSize(50.0f, 50.0f);
	mpExclamationMark->SetUV(0, 0, 1, 1);
}

// デストラクタ
CExclamationMark::~CExclamationMark()
{

}

// 削除
void CExclamationMark::Kill()
{
	CTask::Kill();
	mpExclamationMark->Kill();
}

// 中心位置を設定
void CExclamationMark::SetCeneterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

// ワールド座標を設定
void CExclamationMark::SetWorldPos(const CVector& worldPos)
{
	// 現在のカメラを取得
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	CVector playerPos = CPlayer::Instance()->Position();

	// 設定されたワールド座標をスクリーン座標に変換
	CVector screenPos = cam->WorldToScreenPos(worldPos);

	// 設定されたワールド座標がカメラの背後であれば、
	// ゲージを表示しない
	if (screenPos.Z() < 0.0f)
	{
		SetShow(false);
		return;
	}

	float distanceToPlayer = (worldPos - playerPos).Length();
	if (distanceToPlayer < 100.0f)
	{
		SetShow(true);
	}
	else
	{
		SetShow(false);
	}

	// 求めたスクリーン座標を自身の座標に設定
	mPosition = screenPos;

	//// 設定されたワールド座標とカメラの距離を求める
	//float dist = (worldPos - cam->Position()).Length();

	//// カメラから離れるごとにスケール値を小さくする
	//float ratio = Math::Clamp01((dist - SCALE_DIST_MIN) / (SCALE_DIST_MAX - SCALE_DIST_MIN));
	//mScale = Math::Lerp(SCALE_MIN, SCALE_MAX, ratio);

}

// 更新処理
void CExclamationMark::Update()
{
	// フレーム位置を設定
	//CVector2 pos = mPosition - CVector2(FRAME_SIZE_X, 0.0f) * 0.5f;
	mpExclamationMark->SetPos(mPosition);
	mpExclamationMark->SetSize(CVector2(50.0f, 50.0f));


	// フレームの中心位置
	mpExclamationMark->SetCenter
	(
		50.0f * mCenterRatio.X(),
		50.0f * mCenterRatio.Y()
	);

	mpExclamationMark->SetShow(IsShow());
}