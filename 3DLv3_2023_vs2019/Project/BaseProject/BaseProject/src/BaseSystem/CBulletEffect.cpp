#include "CBulletEffect.h"

#define EFFECT	 "Effect\\4769611_2505787.jpg"
#define EFFECT2	 "Effect\\exp.tga"

// 弾丸と同じ移動速度
#define MOVE_SPEED 100.0f

CEffect* CBulletEffect::mpBulletEffect = nullptr;

CBulletEffect::CBulletEffect()
	: mMoveDistance(0.0f)
{
	mpBulletEffect = new CEffect(Position(), 1.0f, 1.0f, EFFECT2, 4, 4, 2);
}

CBulletEffect::~CBulletEffect()
{
	SAFE_DELETE(mpBulletEffect);
}

void CBulletEffect::Update()
{
	CVector currentPos = Position();
	float moveSpeed = MOVE_SPEED * Time::DeltaTime();
	currentPos += VectorZ() * moveSpeed;
	Position(currentPos);

	// 弾丸と同じ移動距離を加算
	mMoveDistance += moveSpeed;
	// 一定距離移動したら、エフェクトを削除
	if (mMoveDistance >= 100.0f)
	{
		Kill();
	}
}

void CBulletEffect::Render()
{
	if (mpBulletEffect != nullptr)
	{
		mpBulletEffect->Render();
	}
}

//CMatrix CBulletEffect::Matrix() const
//{
//	// 自分自身の行列を返す
//	if (mpAttachMtx == nullptr)
//	{
//		return CTransform::Matrix();
//	}
//	// アタッチしている行列を返す
//	else
//	{
//		CMatrix sm;
//		sm.Scale(100.0f, 100.0f, 100.0f);
//
//		CMatrix moveMatrix;
//		moveMatrix.Translate(0.0f, 0.0f, 10.0f);
//		return moveMatrix * sm * (*mpAttachMtx);
//	}
//}