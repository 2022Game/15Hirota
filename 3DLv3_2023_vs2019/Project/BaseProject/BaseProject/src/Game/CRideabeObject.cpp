#include "CRideableObject.h"

CRideableObject::CRideableObject()
	: CObjectBase(ETag::eRideableObject, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
{
	
}

CRideableObject::~CRideableObject()
{
}

void CRideableObject::AttackStart()
{
	mAttackHitObjects.clear();
}

void CRideableObject::AttackEnd()
{

}

void CRideableObject::AddAttackHitObj(CObjectBase* obj)
{
	mAttackHitObjects.push_back(obj);
}

bool CRideableObject::IsAttackHitObj(CObjectBase* obj) const
{
	auto find = std::find(
		mAttackHitObjects.begin(),
		mAttackHitObjects.end(),
		obj
	);
	return find != mAttackHitObjects.end();
}