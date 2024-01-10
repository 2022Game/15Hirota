#pragma once
#include <initializer_list>

// オブジェクト識別用のタグ
enum class ETag
{
	eNone = -1,

	eField,				// フィールドを構成するオブジェクト
	eRideableObject,	// 乗ることができるオブジェクト
	eItem,				// アイテムのオブジェクト
	eGoalObject,		// クリア条件のオブジェクト
	eJumpingObject,		// ジャンプするオブジェクト

	ePlayer,			// プレイヤー
	eEnemy,				// エネミー
	eSoldier,

	eWeapon,			// プレイヤーの武器
	eEnemyWeapon,		// 敵の武器
	eBulletLine,		// 弾丸の線

	eBakuhatu,
	eGauge,
	eEnemyFrame,


	eCamera,			// カメラ
	
	Num
};
// オブジェクト識別用のタグの初期化リスト
using Tags = std::initializer_list<ETag>;
