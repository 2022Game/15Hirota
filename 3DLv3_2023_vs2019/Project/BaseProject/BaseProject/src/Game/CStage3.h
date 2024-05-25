#ifndef CSTAGE3_H
#define CSTAGE3_H
#include "CStageBase.h"

class CField_Worlds_1;
class CField_Worlds_1_FallCol;
class CStageTime;

// ステージ3「平原マップ」
class CStage3 : public CStageBase
{
public:
	// コンストラクタ
	CStage3();
	// デストラクタ
	~CStage3();

	// ステージ読み込み
	void Load() override;
	// ステージ破棄
	void Unload() override;

private:
	CField_Worlds_1* mpField_Worlds_1;	// フィールド
	CField_Worlds_1_FallCol* mpFallCol;
};
#endif