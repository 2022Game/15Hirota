#ifndef CTREASURECHESTUI_H
#define CTREASURECHESTUI_H

#include "CUIBase.h"
#include "CVector.h"

class CImage;

class CTreasureChestUI : public CUIBase
{
public:
	// コンストラクタ
	CTreasureChestUI();
	// デストラクタ
	~CTreasureChestUI();

	void Kill() override;

	void SetCenterRatio(const CVector2& ratio);

	void SetWorldPos(const CVector& worldPos);

	// 更新処理
	void Update();

private:
	CImage* mpUI;			// UI画像
	CVector2 mCenterRatio;	// 中心位置の割合
	float mScale;			// 画像のスケール値
};
#endif