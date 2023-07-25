#include "CXEnemy.h"

CXEnemy::CXEnemy()
	:mColSpherBody(this, nullptr, CVector(), 0.5f)
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
        if (o->Type() == CCollider::ESPHERE)
        {
            if ()
            {
                if (o->Tag() == CCollider::ETag::ESWORD)
                {
                    if (m->Tag() == CCollider::ETag::EBODY)
                    {
                        if (CCollider::Collision(m, o))
                        {
                           
                        }
                    }
                }
            }
        }
        break;
    }
}

void CXEnemy::Update()
{
}