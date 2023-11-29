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

	ePlayer,			// プレイヤー
	eEnemy,				// エネミー

	eWeapon,			// プレイヤーの武器
	eEnemyWeapon,		// 敵の武器

	eBakuhatu,
	eGauge,
	eEnemyFrame,


	eCamera,			// カメラ
	
	Num
};
// オブジェクト識別用のタグの初期化リスト
using Tags = std::initializer_list<ETag>;
