#include "CItemObjectBase.h"

CItemObjectBase::CItemObjectBase()
	: CObjectBase(ETag::eItem, ETaskPriority::eItem)
{
}

CItemObjectBase::~CItemObjectBase()
{

}

// 回復がヒットしたオブジェクトを追加
void CItemObjectBase::AddAttachHitObj(CObjectBase* obj)
{
	mRecoveryObjects.push_back(obj);
}

// 回復開始
void CItemObjectBase::RecoverStart()
{
	mRecoveryObjects.clear();
}

// 回復終了
void CItemObjectBase::RecoverEnd()
{

}

bool CItemObjectBase::IsAttachHitObj(CObjectBase* obj) const
{
	// すでにリストに追加されているか確認をする
	auto find = std::find
	(
		mRecoveryObjects.begin(),
		mRecoveryObjects.end(),
		obj
	);
	return find != mRecoveryObjects.end();
}