#ifndef CSTAGESELECTIONSTAGE_H
#define CSTAGESELECTIONSTAGE_H
#include "CStageBase.h"

// ステージ選択ステージ
class CStageSelectionStage : public CStageBase
{
public:
	// コンストラクタ
	CStageSelectionStage();
	// デストラクタ
	~CStageSelectionStage();

	// ステージ読み込み
	void Load() override;
	// ステージ破棄
	void Unload() override;
private:
};
#endif