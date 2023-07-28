#include "CXEnemy.h"

CXEnemy::CXEnemy()
	:mColSpherBody(this, nullptr, CVector(), 0.5f,CCollider::ETag::EBODY)
	, mColSpherHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
	, mColspherSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{
	mTag = EENEMY;
}

void CXEnemy::Init(CModelX *model)
{
	CXCharacter::Init(model);
	//‡¬s—ñ
	//‘Ì
	mColSpherBody.Matrix(&mpCombinedMatrix[8]);
	//“ª
	mColSpherHead.Matrix(&mpCombinedMatrix[11]);
	//Œ•
	mColspherSword.Matrix(&mpCombinedMatrix[21]);
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
		}

		break;
    }
}

void CXEnemy::Update()
{
    CXCharacter::Update();
}