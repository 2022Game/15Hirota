#pragma once
#include "CObjectBase.h"
#include "CharaStatus.h"

/// <summary>
/// キャラクターのベースクラス
/// </summary>
class CCharaBase : public CObjectBase
{
public:
	CCharaBase(ETag tag, ETaskPriority prio, int sortOrder = 0,
		ETaskPauseType pause = ETaskPauseType::eGame);
	virtual ~CCharaBase();

	// 被ダメージ処理
	// damage == 受けるダメージ
	virtual void TakeDamage(int damage);

	// 回復処理
	// recovery == 回復
	virtual void TakeRecovery(int recovery);
	
	virtual void TakeInvincible();


	// 最大ステータスを取得
	const CharaStatus& MaxStatus() const;
	// 現在のステータスを取得
	const CharaStatus& Status() const;

protected:
	CharaStatus mCharaMaxStatus;	// 最大ステータス
	CharaStatus mCharaStatus;		// 現在ステータス
};
