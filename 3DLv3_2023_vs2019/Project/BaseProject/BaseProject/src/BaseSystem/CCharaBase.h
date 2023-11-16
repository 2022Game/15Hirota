#pragma once
#include "CObjectBase.h"
#include "CharaStatus.h"

/// <summary>
/// キャラクターのベースクラス
/// </summary>
class CCharaBase : public CObjectBase
{
public:
	CCharaBase(ETag tag, ETaskPriority prio);
	virtual ~CCharaBase();

	// 被ダメージ処理
	// damage == 受けるダメージ
	virtual void TakeDamage(int damage);

	// 最大ステータスを取得
	const CharaStatus& MaxStatus() const;		// プレイヤー最大ステータス
	// 現在のステータスを取得
	const CharaStatus& Status() const;			// プレイヤー現在ステータス

	// エネミー最大ステータスを取得
	const CharaStatus& MaxEnemyStatus() const;	// エネミー最大ステータス
	// エネミー現在ステータスを取得
	const CharaStatus& EnemeyStatus() const;	// エネミー現在ステータス

protected:
	CharaStatus mCharaMaxStatus;	// プレイヤー最大ステータス
	CharaStatus mCharaStatus;		// プレイヤー現在ステータス

	CharaStatus mCharaMaxStatus_Enemy;	// 敵の最大ステータス
	CharaStatus mCharaStatus_Enemy;		// 敵のステータス
};
