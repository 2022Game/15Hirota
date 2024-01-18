#include "CRideableObject.h"
#include "CPlayer.h"

// Weapon�Ɠ���
CRideableObject::CRideableObject(ETaskPriority prio)
	: CObjectBase(ETag::eRideableObject, prio, 0, ETaskPauseType::eGame)
{
	
}

CRideableObject::~CRideableObject()
{
	// �v���C���[�����݂���΁A
	// �������g���폜����邱�Ƃ��v���C���[�ɓ`����
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