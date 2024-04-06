#include "CWireMeshMoveClimbWall.h"
#include "Maths.h"

CWireMeshMoveClimbWall::CWireMeshMoveClimbWall(std::string wireName, std::string topName,
	const CVector& moveUp, const CVector& moveForward, 
	const CVector& pos, const CVector& move, float moveTime)
	: CRideableObject(ETaskPriority::eRotate)
	, mClimbedMoveUp(moveUp)
	, mClimbMoveForward(moveForward)
	, mDefaultPos(pos)
	, mMoveVec(move)
	, mMoveTime(moveTime)
	, mElapsedTime(0.0f)
{
	mpWireMeshModel = CResourceManager::Get<CModel>(wireName);

	CModel* wireCol = CResourceManager::Get<CModel>("WireMeshMoveCol");
	mpWallCol = new CColliderMesh(this, ELayer::eWireMoveClimb, wireCol, true);
	mpWallCol->SetCollisionTags({ ETag::ePlayer });

	CModel* top = CResourceManager::Get<CModel>(topName);
	mpWallTopCol = new CColliderMesh(this, ELayer::eWireMoveClimbedTop, top, true);
	mpWallTopCol->SetCollisionTags({ ETag::ePlayer });
	mpWallTopCol->SetCollisionLayers({ ELayer::ePlayer });

	Position(mDefaultPos);
}

CWireMeshMoveClimbWall::~CWireMeshMoveClimbWall()
{
	SAFE_DELETE(mpWallCol);
	SAFE_DELETE(mpWallTopCol);
}

// ����֏��؂������̈ړ��ʂ��擾
void CWireMeshMoveClimbWall::GetClimbedMoveVec(CVector* outUp, CVector* outForward) const
{
	*outUp = mClimbedMoveUp;
	*outForward = mClimbMoveForward;
}

void CWireMeshMoveClimbWall::Update()
{
	float per = mElapsedTime / mMoveTime;
	Position(mDefaultPos + mMoveVec * sinf(M_PI * 2.0f * per));

	mElapsedTime += 1.0f / 60.0f;
	if (mElapsedTime >= mMoveTime)
	{
		mElapsedTime -= mMoveTime;
	}
}

void CWireMeshMoveClimbWall::Render()
{
	mpWireMeshModel->SetColor(mColor);
	mpWireMeshModel->Render(Matrix());
}