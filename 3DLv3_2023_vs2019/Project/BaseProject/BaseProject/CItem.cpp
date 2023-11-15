#include "CItem.h"

CItem::CItem()
	:CObjectBase(ETag::eItem,ETaskPriority::eWeapon)
	, mpAttachMtx(nullptr)
{
}

CItem::~CItem()
{
	
}

void CItem::SetOwner(CCharaBase* owner)
{
	mOwner = owner;
}

CCharaBase* CItem::GetOwner() const
{
	return mOwner;
}

void CItem::AttackMtx(const CMatrix* mtx)
{
	mpAttachMtx = mtx;
}

void CItem::AttackStart()
{
	mAttackHitObjects.clear();
}

void CItem::AttackEnd()
{
}

void CItem::AddAttackHitObj(CObjectBase* obj)
{
	mAttackHitObjects.push_back(obj);
}

bool CItem::IsAttackHitObj(CObjectBase* obj) const
{
	// 既にリストに追加されているかを確認する
	auto find = std::find
	(
		mAttackHitObjects.begin(),
		mAttackHitObjects.end(),
		obj
	);
	return find != mAttackHitObjects.end();
}