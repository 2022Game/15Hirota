#include "CInsideCircleEffect.h"
#include "CPlayer.h"
#include "Maths.h"

// �R���X�g���N�^
CInsideCircleEffect::CInsideCircleEffect(float angle, float dist)
	: mAngle(angle)
	, mDistance(dist)
	, mElapsedTime(0.0f)
{
	mpCircleModel = CResourceManager::Get<CModel>("CircleEffect1");
	mpCircleModel->SetupEffectSettings();
	Scale(5.0f, 5.0f, 5.0f);
}

// �f�X�g���N�^
CInsideCircleEffect::~CInsideCircleEffect()
{

}

// �X�V����
void CInsideCircleEffect::Update()
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

	bool item = player->IsAttackItem();
	if (!item)
	{
		// �폜
		Kill();
	}
}

// �`�揈��
void CInsideCircleEffect::Render()
{
	mpCircleModel->SetColor(mColor);
	mpCircleModel->Render(Matrix());
}