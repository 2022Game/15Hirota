#include "COutsideCircleEffect.h"
#include "CPlayer.h"
#include "Maths.h"

// �R���X�g���N�^
COutsideCircleEffect::COutsideCircleEffect(float angle, float dist)
	: mAngle(angle)
	, mDistance(dist)
	, mElapsedTime(0.0f)
{
	mpCircleModel = CResourceManager::Get<CModel>("CircleEffect2");
	mpCircleModel->SetupEffectSettings();
	Scale(5.0f, 4.0f, 5.0f);
}

// �f�X�g���N�^
COutsideCircleEffect::~COutsideCircleEffect()
{

}

// �X�V����
void COutsideCircleEffect::Update()
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

	bool healing = player->IsHealingItem();
	bool attack = player->IsAttackItem();

	if (mElapsedTime >= 3.0f)
	{
		mElapsedTime = 0.0f;
		Kill();
	}
	else
	{
		mElapsedTime += Time::DeltaTime();
	}

	//bool item = player->IsAttackItem();
	//bool healing = player->IsHealingItem();
	//if (!item)
	//{
	//	// �폜
	//	Kill();
	//}
	//else if (!healing)
	//{
	//	// �폜
	//	Kill();
	//}
}

// �`�揈��
void COutsideCircleEffect::Render()
{
	mpCircleModel->SetColor(mColor);
	mpCircleModel->Render(Matrix());
}