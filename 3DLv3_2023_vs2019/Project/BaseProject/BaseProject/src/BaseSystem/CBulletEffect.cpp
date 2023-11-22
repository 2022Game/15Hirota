#include "CBulletEffect.h"
#include "CBullet.h"

#define EFFECT	 "Effect\\4769611_2505787.jpg"
#define EFFECT2	 "Effect\\exp.tga"

// 弾丸と同じ移動速度
#define MOVE_SPEED 100.0f

CEffect* CBulletEffect::mpBulletEffect = nullptr;

CBulletEffect::CBulletEffect()
	: CEffect(Position(),1.0f,1.0f, EFFECT2,2,2,4)
	, mMoveDistance(0.0f)
	, mpAssociatedBullet(nullptr)
{
	mpBulletEffect = new CBulletEffect();
}

CBulletEffect::~CBulletEffect()
{
	
}

void CBulletEffect::Update()
{
	if (mpAssociatedBullet != nullptr)
	{
		Position(mpAssociatedBullet->Position());
	}

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

		mpAssociatedBullet = nullptr;
	}
	CDebugPrint::Print("mpAssociatedBullet%p\n", mpAssociatedBullet);
}

void CBulletEffect::Render()
{
	if (mpAssociatedBullet != nullptr)
	{
		mpAssociatedBullet->Render();
	}
}

void CBulletEffect::SetAssociatedBullet(CBullet* pBullet)
{
	mpAssociatedBullet = pBullet;
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