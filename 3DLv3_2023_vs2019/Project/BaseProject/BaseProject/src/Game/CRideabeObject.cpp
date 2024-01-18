#include "CRideableObject.h"
#include "CPlayer.h"

// Weaponと同じ
CRideableObject::CRideableObject(ETaskPriority prio)
	: CObjectBase(ETag::eRideableObject, prio, 0, ETaskPauseType::eGame)
{
	
}

CRideableObject::~CRideableObject()
{
	// プレイヤーが存在すれば、
	// 自分自身が削除されることをプレイヤーに伝える
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		player->DeleteRideableObject(this);
	}
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