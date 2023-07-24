#include "CXEnemy.h"

CXEnemy::CXEnemy()
	:mColSpherBody(this, nullptr, CVector(), 0.5f)
	, mColSpherHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
	, mColspherSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{
}

void CXEnemy::Init(CModelX *model)
{
	CXCharacter::Init(model);
	//�����s��
	//��
	mColSpherBody.Matrix(&mpCombinedMatrix[8]);
	//��
	mColSpherHead.Matrix(&mpCombinedMatrix[11]);
	//��
	mColspherSword.Matrix(&mpCombinedMatrix[21]);
}