#pragma once
#include "CObjectBase.h"

class CRideableObject : public CObjectBase
{
public:
	CRideableObject();
	virtual ~CRideableObject();

	virtual void AttackStart();

	virtual void AttackEnd();

protected:
	void AddAttackHitObj(CObjectBase* obj);
	bool IsAttackHitObj(CObjectBase* obj) const;

	std::list<CObjectBase*> mAttackHitObjects;
};