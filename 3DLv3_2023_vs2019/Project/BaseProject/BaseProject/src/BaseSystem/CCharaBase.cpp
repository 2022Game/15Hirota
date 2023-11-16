#include "CCharaBase.h"

CCharaBase::CCharaBase(ETag tag, ETaskPriority prio)
	: CObjectBase(tag, prio)
{
}

CCharaBase::~CCharaBase()
{
}

// 被ダメージ処理
void CCharaBase::TakeDamage(int damage)
{

}

// 最大ステータスを取得
const CharaStatus& CCharaBase::MaxStatus() const
{
	return mCharaMaxStatus;
}

// 現在ステータスを取得
const CharaStatus& CCharaBase::Status() const
{
	return mCharaStatus;
}

// エネミー最大ステータス
const CharaStatus& CCharaBase::MaxEnemyStatus() const
{
	return mCharaMaxStatus_Enemy;
}

// エネミー現在ステータス
const CharaStatus& CCharaBase::EnemeyStatus() const
{
	return mCharaStatus_Enemy;
}
