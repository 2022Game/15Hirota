#include "CGun.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CInput.h"
#include "CEffect.h"

//#define M1GARAND_O "Item\\Gun_M1Garand\\Gun_M1Garand.obj"
//#define M1GARAND_M "Item\\Gun_M1Garand\\Gun_M1Garand.mtl"


CGun::CGun()
{
	// ���f���f�[�^�擾
	mpGun = CResourceManager::Get<CModel>("Gun_M1G");
}

CGun::~CGun()
{

}

void CGun::Update()
{

}

void CGun::Render()
{
	mpGun->Render(Matrix());
}


CMatrix CGun::Matrix() const
{
	const CMatrix* attachMtx = GetAttachMtx();
	// ��Ɏ����Ă��Ȃ��Ƃ��́A�������g�̍s���Ԃ�
	if (attachMtx == nullptr)
	{
		return CTransform::Matrix();
	}
	// ��Ɏ����Ă���Ƃ��́A�A�^�b�`���Ă���s���Ԃ�
	else
	{
		CMatrix sm;
		sm.Scale(190.0f, 190.0f, 190.0f);

		// ��]��\���s����쐬
		CMatrix rotateY;
		CMatrix rotateZ;
		CMatrix rotateX;

		// �ړ���\���s����쐬
		CMatrix positionX;
		CMatrix positionZ;
		CMatrix positionY;

		//rotateX.RotateX(30.0f);		// X���̉�]
		rotateY.RotateY(-105.0f);	// Y���̉�]
		rotateZ.RotateZ(-22.5f);		// Z���̉�]

		float xOffset = 5.0f;	// X�������̂�����w��
		positionX.Translate(xOffset, 0, 0);
		float yOffset = 17.0f;	// Y�������̂�����w��
		positionY.Translate(0, yOffset, 0);
		float zOffset = 8.0f;	// Z�������̂�����w��3.5f
		positionZ.Translate(0, 0, zOffset);

		return sm * rotateZ * rotateY * positionX * positionY * positionZ * (*attachMtx);
	}
}