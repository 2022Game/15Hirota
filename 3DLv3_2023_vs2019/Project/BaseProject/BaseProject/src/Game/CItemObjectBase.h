#ifndef CITEMOBJECTBASE_H
#define CITEMOBJECTBASE_H
#include "CObjectBase.h"
class CCharaBase;

// オブジェクト継承

class CItemObjectBase : public CObjectBase
{
public:
	CItemObjectBase();
	virtual ~CItemObjectBase();

	// 回復開始
	virtual void RecoverStart();
	// 回復終了
	virtual void RecoverEnd();

protected:
	// 回復がヒットしたオブジェクトを追加
	void AddAttachHitObj(CObjectBase* obj);
	// すでに回復がヒットしているオブジェクトかどうか
	bool IsAttachHitObj(CObjectBase* obj) const;

	// 回復アイテムヒット済みのオブジェクトリスト
	std::list<CObjectBase*> mRecoveryObjects;
	
};
#endif