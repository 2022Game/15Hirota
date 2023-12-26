#pragma once

// Taskの優先順序
enum class ETaskPriority
{
	eNone = -1,

	// 3D関連
	eBackground,	// 背景
	eDefault,		// デフォルト
	eEnemyGauge,	// エネミーのゲージ
	eEnemyUi,		// エネミーのUI

	ePlayer,		// プレイヤー
	eEnemy,			// エネミー

	eWeapon,		// プレイヤー武器
	eEnemyWeapon,	// 敵の武器

	eEffect,
	eTransparent,	// 透明オブジェクト

	eCamera,		// カメラ

	// 2D関連
	eUI,			// UI関連のデフォルト
	eSystem,		// システム関連
	eDebug,			// デバッグ関連

	Num,

	// 2D関連のタスクの開始位置
	Start2d = eUI,
};