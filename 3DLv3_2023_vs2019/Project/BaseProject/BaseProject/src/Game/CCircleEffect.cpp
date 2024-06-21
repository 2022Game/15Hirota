#include "CCircleEffect.h"
#include "CPlayer.h"
#include "Maths.h"

// �R���X�g���N�^
CCircleEffect::CCircleEffect(float angle, float dist)
	: mAngle(angle)
	, mDistance(dist)
	, mElapsedTime(0.0f)
{
	mpModel = CResourceManager::Get<CModel>("CircleEffect");
	mpModel->SetupEffectSettings();
}

// �f�X�g���N�^
CCircleEffect::~CCircleEffect()
{

}

// �X�V����
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
			// �_�ł̑��x�𒲐����邽�߂̒萔
			const float blinkSpeed = 1.0f;

			// sin�֐����g���ē_�ł���F���v�Z
			// 0.0�`1.0�̊Ԃ���������
			float red = 0.5f + 0.5f * sin(mElapsedTime * blinkSpeed);
			// �o�t�̐F�ݒ�
			SetColor(CColor(red, 0.0f, 0.0f, 1.0f));


			CDebugPrint::Print("green:%f\n", red);
			CDebugPrint::Print("ElapsedTime:%f\n", mElapsedTime);
		}
	}
	else
	{
		// �폜
		Kill();
	}
}

// �`�揈��
void CCircleEffect::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}