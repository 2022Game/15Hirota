#include "CXEnemy.h"

CXEnemy::CXEnemy()
	:mColSpherBody(this, nullptr, CVector(0.5f, -1.0f, 0.0f), 0.0f)
	, mColSpherHead(this, nullptr, CVector(0.0f, 1.0f, 0.0f), 1.5f)
	, mColspherSword0(this, nullptr, CVector(0.7f, 3.5f, -0.2f), 0.5f)
	, mColspherSword1(this, nullptr, CVector(0.5f, 2.5f, -0.2f), 0.5f)
	, mColspherSword2(this, nullptr, CVector(0.3f, 1.5f, -0.2f), 0.5f)
{
	mTag = EENEMY;
}

void CXEnemy::Init(CModelX *model)
{
	CXCharacter::Init(model);
	//‡¬s—ñ
	//‘Ì
	mColSpherBody.Matrix(&mpCombinedMatrix[1]);
	//“ª
	mColSpherHead.Matrix(&mpCombinedMatrix[1]);
	//Œ•
	mColspherSword0.Matrix(&mpCombinedMatrix[26]);
	mColspherSword1.Matrix(&mpCombinedMatrix[26]);
	mColspherSword2.Matrix(&mpCombinedMatrix[26]);
}

void CXEnemy::Collision(CCollider* m, CCollider* o)
{
    switch (m->Type()) {
	case CCollider::ESPHERE:
		if (m->Type() == CCollider::EType::ESPHERE &&
			o->Type() == CCollider::EType::ESPHERE &&
			o->Parent()->Tag() == CCharacter3::EPLAYER &&
			o->Tag() == CCollider::ETag::ESWORD &&
			m->Tag() == CCollider::ETag::EBODY &&
			CCollider::Collision(m, o))
		{
			ChangeAnimation(11, false, 30);
			CXCharacter::Update();
		}
		break;
    }
}

void CXEnemy::Update()
{
    CXCharacter::Update();
}