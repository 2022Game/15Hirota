#include "CCircleEffect.h"
#include "CPlayer.h"
#include "Maths.h"

// コンストラクタ
CCircleEffect::CCircleEffect(float angle, float dist)
	: mAngle(angle)
	, mDistance(dist)
	, mElapsedTime(0.0f)
{
	mpModel = CResourceManager::Get<CModel>("CircleEffect");
	mpModel->SetupEffectSettings();
}

// デストラクタ
CCircleEffect::~CCircleEffect()
{

}

// 更新処理
void CCircleEffect::Update()
{
	CPlayer* player = CPlayer::Instance();

	CVector center = mOwner->Position();
	CVector pos = CVector::zero;
	pos.X(cosf(Math::DegreeToRadian(mAngle)) * mDistance);
	pos.Z(sinf(Math::DegreeToRadian(mAngle)) * mDistance);
	pos.Y(0.0f);
	Position(center + pos);

	CVector dir = center - Position();
	dir.Y(0.0f);
	dir.Normalized();
	Rotation(CQuaternion::LookRotation(dir));

	mAngle += 55.0f * Time::DeltaTime();
	if (mAngle >= 360.0f) mAngle -= 360.0f;

	if (mElapsedTime <= 10.0f)
	{
		mElapsedTime += Time::DeltaTime();
		if (player->IsAttackItem())
		{
			// 点滅の速度を調整するための定数
			const float blinkSpeed = 1.0f;

			// sin関数を使って点滅する色を計算
			// 0.0～1.0の間を往復する
			float red = 0.5f + 0.5f * sin(mElapsedTime * blinkSpeed);
			// バフの色設定
			SetColor(CColor(red, 0.0f, 0.0f, 1.0f));


			CDebugPrint::Print("green:%f\n", red);
			CDebugPrint::Print("ElapsedTime:%f\n", mElapsedTime);
		}
	}
	else
	{
		// 削除
		Kill();
	}
}

// 描画処理
void CCircleEffect::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}