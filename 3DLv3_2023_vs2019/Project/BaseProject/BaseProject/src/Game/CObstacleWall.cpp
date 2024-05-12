#include "CObstacleWall.h"
#include "CModel.h"
#include "CStageManager.h"

// �R���X�g���N�^
CObstacleWall::CObstacleWall(const CVector& pos, const CQuaternion& rot, const CVector& scale)
	: CObstacle(ETag::eObstacle)
	, mState(EState::eIdle)
	, mStateStep(0)
	, mElapsedTimel(0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mTargetPos(0.0f, 0.0f, 0.0f)
{

	mpModel = CResourceManager::Get<CModel>("FieldCube");

	// �R���C�_�[
	mpColliderMesh = new CColliderMesh(this, ELayer::eFieldWall, mpModel, true);
	mpColliderMesh->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });

	Position(pos);
	Rotation(rot);
	Scale(scale);
}

// �f�X�g���N�^
CObstacleWall::~CObstacleWall()
{
	// �쐬�����^�X�N����菜��
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CObstacleWall::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{

}

// �폜���ɌĂяo�����
void CObstacleWall::Death()
{
	mState = EState::eDeath;
}

void CObstacleWall::UpdateIdle()
{

}

void CObstacleWall::UpdateDeath()
{
	switch (mStateStep)
	{
	case 0:
		mStartPos = Position();
		mTargetPos = mStartPos - CVector(0.0f, 40.0f, 0.0f);
		mElapsedTimel = 0.0f;
		mStateStep++;
		break;
	case 1:
		if (mElapsedTimel < 2.0f)
		{
			float per = mElapsedTimel / 2.0f;
			CVector pos = CVector::Lerp(mStartPos, mTargetPos, per);
			Position(pos);
			mElapsedTimel += Time::DeltaTime();
		}
		else
		{
			Position(mTargetPos);
			Kill();
		}
		break;
	}
}

// �X�V
void CObstacleWall::Update()
{
	switch (mState)
	{
	case EState::eIdle:
		UpdateIdle();
		break;
	case EState::eDeath:
		UpdateDeath();
		break;
	}
}

// �`��
void CObstacleWall::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}