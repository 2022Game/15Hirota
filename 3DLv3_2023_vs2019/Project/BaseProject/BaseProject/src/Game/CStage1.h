#ifndef CSTAGE1_H
#define CSTAGE1_H
#include "CStageBase.h"

// ステージ1「平原マップ」
class CStage1 : public CStageBase
{
public:
	// コンストラクタ
	CStage1();
	// デストラクタ
	~CStage1();

	// ステージ読み込み
	void Load() override;
	// ステージ破棄
	void Unload() override;

	void Render();
private:
};
#endif