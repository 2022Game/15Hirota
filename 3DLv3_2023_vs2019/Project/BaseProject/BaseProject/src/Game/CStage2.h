#ifndef CSTAGE2_H
#define CSTAGE2_H
#include "CStageBase.h"

class CField1;

// ステージ1 「大きな平原」
class CStage2 : public CStageBase
{
public:
	// コンストラクタ
	CStage2();
	// デストラクタ
	~CStage2();

	// ステージ読み込み
	void Load() override;
	// ステージ破棄
	void Unload() override;

private:
	CField1* mpField1;
};
#endif