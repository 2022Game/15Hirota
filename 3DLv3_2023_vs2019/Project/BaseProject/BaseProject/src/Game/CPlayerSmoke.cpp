#include "CPlayerSmoke.h"
#include "CSmoke.h"
#include "CInput.h"
#include "Maths.h"
#include "CPlayer.h"

// 煙の発射間隔時間
#define THROW_INTERVAL 0.15f
// 煙の発射方向のブレ幅
#define FLAME_DIR_RAND 0.02f
// 煙の移動速度
#define FLAME_MOVE_SPEED 75.0f
// 煙の色
#define FLAME_COLOR CColor(1.0f, 1.0f, 1.0f)

// コンストラクタ
CPlayerSmoke::CPlayerSmoke(CObjectBase* owner, const CMatrix* attach,
	const CVector& offsetPos, const CMatrix& offsetRot)
	: mpOwner(owner)
	, mpAttachMtx(attach)
	, mThrowOffsetPos(offsetPos)
	, mThrowOffsetRot(offsetRot)
	, mElapsedTime(0.0f)
	, mIsThrowing(false)
{
}

// デストラクタ
CPlayerSmoke::~CPlayerSmoke()
{
	for (CSmoke* flame : mSmoke)
	{
		flame->Kill();
	}
}

// 煙を発射開始
void CPlayerSmoke::Start()
{
	mIsThrowing = true;
	mElapsedTime = 0.0f;
}

// 煙を発射停止
void CPlayerSmoke::Stop()
{
	mIsThrowing = false;
}

// 煙を発射しているかどうか
bool CPlayerSmoke::IsThrowing() const
{
	return mIsThrowing;
}

// 発射時のオフセット位置を設定
void CPlayerSmoke::SetThrowOffsetPos(const CVector& pos)
{
	mThrowOffsetPos = pos;
}

// 発射時のオフセット回転値を設定
void CPlayerSmoke::SetThrowOffsetRot(const CMatrix& rot)
{
	mThrowOffsetRot = rot;
}

// 煙の発射位置を取得
CVector CPlayerSmoke::GetThrowPos() const
{
	// アタッチする行列が設定されている場合は、行列の座標を返す
	if (mpAttachMtx != nullptr)
	{
		CVector pos = mpAttachMtx->Position();
		pos += mpAttachMtx->VectorX().Normalized() * mThrowOffsetPos.X()
			+ mpAttachMtx->VectorY().Normalized() * mThrowOffsetPos.Y()
			+ mpAttachMtx->VectorZ().Normalized() * mThrowOffsetPos.Z();
		return pos;
	}
	// 持ち主が設定されている場合は、持ち主の座標を返す
	else if (mpOwner != nullptr)
	{
		return mpOwner->Position() + (mpOwner->Rotation() * mThrowOffsetPos);
	}

	return CVector::zero;
}

// 煙の発射方向を取得
CVector CPlayerSmoke::GetThrowDir() const
{
	//// アタッチする行列が設定されている場合は、行列の正面方向ベクトルを返す
	//if (mpAttachMtx != nullptr)
	//{
	//	return mThrowOffsetRot * mpAttachMtx->VectorY();
	//}
	//// 持ち主が設定されている場合は、持ち主の正面方向ベクトルを返す
	//else if (mpOwner != nullptr)

	//{
	//	return mThrowOffsetRot * mpOwner->VectorY();
	//}

	return mThrowOffsetRot * CVector::zero;
}

// 煙のエフェクトを作成
void CPlayerSmoke::CreateSmoke()
{
	// 煙のエフェクトを作成
	CSmoke* smoke = new CSmoke(ETag::eSmoke);

	// 発射位置を取得
	CVector pos = GetThrowPos(); // + CVector(0.0f, 10.0f, 0.0f);
	// 発射方向を取得
	CVector dir = GetThrowDir(); // + CVector(0.0f, -1.0f, 0.0f);
	// 発射方向をランダムでブラす
	//dir.X(dir.X() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	//dir.Y(dir.Y() + Math::Rand(0.0f, 0.0f));
	//dir.Z(dir.Z() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	dir.Normalize();
	// 発射位置、方向、移動速度を設定
	smoke->Setup(pos, dir, FLAME_MOVE_SPEED);

	// 煙のカラーを設定
	smoke->SetColor(FLAME_COLOR);
	// 加算ブレンドにして、炎が発光しているように見せる
	smoke->SetBlendType(EBlend::eAdd);

	// 作成した炎のエフェクトをリストに追加
	mSmoke.push_back(smoke);
}

// 更新
void CPlayerSmoke::Update()
{
	// 煙を発射していたら
	if (mIsThrowing)
	{
		// 経過時間に応じて、煙のエフェクトを作成
		if (mElapsedTime >= THROW_INTERVAL)
		{
			CreateSmoke();
			mElapsedTime -= THROW_INTERVAL;
		}
		mElapsedTime += Time::DeltaTime();
	}

	// 生成済みの煙のエフェクトの削除処理
	auto itr = mSmoke.begin();
	auto end = mSmoke.end();
	while (itr != end)
	{
		CSmoke* smoke = *itr;
		// 削除フラグが立っていたら、削除
		if (smoke->IsDeath())
		{
			itr = mSmoke.erase(itr);
			smoke->Kill();
		}
		else
		{
			itr++;
		}
	}
}