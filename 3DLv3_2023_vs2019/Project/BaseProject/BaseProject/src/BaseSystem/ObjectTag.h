#pragma once
#include <initializer_list>

// オブジェクト識別用のタグ
enum class ETag
{
	eNone = -1,

	eField,				// フィールドを構成するオブジェクト
	eRideableObject,	// 乗ることができるオブジェクト
	eItemRecover,		// 回復アイテムのオブジェクト
	eItemInvincible,	// 無敵アイテム
	eAttackObject,		// 攻撃力アップモデル
	eMedal,				// メダルアイテム
	eGoalObject,		// クリア条件のオブジェクト
	eJumpingObject,		// ジャンプするオブジェクト

	ePlayer,			// プレイヤー
	eEnemy,				// エネミー
	eSoldier,

	eWeapon,			// プレイヤーの武器
	eEnemyWeapon,		// 敵の武器
	eBullet,			// 弾丸
	eFlame,				// 炎
	eSlash,				// 斬撃

	eBakuhatu,
	eGauge,
	eEnemyFrame,

	eEffect,	// エフェクト
	eBillboard,	// ビルボードイメージ

	eCamera,			// カメラ
	
	Num
};
// オブジェクト識別用のタグの初期化リスト
using Tags = std::initializer_list<ETag>;
