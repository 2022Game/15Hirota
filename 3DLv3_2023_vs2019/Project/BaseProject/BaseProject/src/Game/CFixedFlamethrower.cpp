#include "CFixedFlamethrower.h"
#include "CPlayer.h"
#include "CFlamethrower.h"
#include "Maths.h"

#define WAIT_TIME 4.0f

CFixedFlamethrower::CFixedFlamethrower(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
	, mStateStep(0)
	, fire(true)
	, mWaitTime(0.0f)
{
	// 火炎放射器モデル取得
	mpFlamethrowerModel = CResourceManager::Get<CModel>("FlamethrowerModel");
	mpFlamethrowerTank = CResourceManager::Get<CModel>("FlamethrowerTank");

	// 火炎放射器コライダー
	CModel* flameCol = CResourceManager::Get<CModel>("FlamethrowerCol");
	mpColliderMesh = new CColliderMesh(this, ELayer::eFlameWall, flameCol, true);

	// 火炎エフェクト
	mpFlamethrower = new CFlamethrower
	(
		this, nullptr,
		CVector(0.0f, 17.0f, -1.0f),
		CQuaternion(0.0f, -90.0f, 0.0f).Matrix()
	);

	ChangeState(EState::Idle);

	Position(pos);
	Scale(scale);
	Rotation(rot);

	SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
}

CFixedFlamethrower::~CFixedFlamethrower()
{
	SAFE_DELETE(mpColliderMesh);
}

void CFixedFlamethrower::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	mWaitTime = WAIT_TIME;
}

void CFixedFlamethrower::UpdateIdle()
{
	if (fire)
	{
		mWaitTime -= Time::DeltaTime();
		if (mWaitTime >= 0.0f)
		{
			if (!mpFlamethrower->IsThrowing())
			{
				mpFlamethrower->Start();
			}
		}
		else
		{
			if (mpFlamethrower->IsThrowing())
			{
				mpFlamethrower->Stop();
			}
			fire = false;
		}
	}
	else
	{
		if (mWaitTime <= WAIT_TIME)
		{
			mWaitTime += Time::DeltaTime();
			if (mWaitTime >= WAIT_TIME)
			{
				mWaitTime = WAIT_TIME;
				fire = true;
			}
		}
	}
	//CDebugPrint::Print("wait:%f\n", mWaitTime);
}

void CFixedFlamethrower::Update()
{
	switch (mState)
	{
	case EState::Idle:
		UpdateIdle();
		break;
	}
}

void CFixedFlamethrower::Render()
{
	mpFlamethrowerModel->SetColor(mColor);
	mpFlamethrowerModel->Render(Matrix());
	mpFlamethrowerTank->SetColor(mColor);
	mpFlamethrowerTank->Render(Matrix());
}