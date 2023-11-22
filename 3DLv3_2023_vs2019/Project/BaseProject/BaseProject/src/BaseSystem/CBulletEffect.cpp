#include "CBulletEffect.h"

#define EFFECT	 "Effect\\4769611_2505787.jpg"
#define EFFECT2	 "Effect\\exp.tga"

// �e�ۂƓ����ړ����x
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

	// �e�ۂƓ����ړ����������Z
	mMoveDistance += moveSpeed;
	// ��苗���ړ�������A�G�t�F�N�g���폜
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
//	// �������g�̍s���Ԃ�
//	if (mpAttachMtx == nullptr)
//	{
//		return CTransform::Matrix();
//	}
//	// �A�^�b�`���Ă���s���Ԃ�
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