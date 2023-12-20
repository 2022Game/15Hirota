#ifndef CSOLDIERFRAME_H
#define CSOLDIERFRAME_H
class CImage;

#include "CUIBase.h"
#include "CVector.h"

class CSoldierFrame :public CUIBase
{
private:
	CImage* mpFrameImage;		// 枠画像
	CVector2 mCenterRatio;		// 中心位置の割合

public:
	// コンストラクタ
	CSoldierFrame();
	// デストラクタ
	~CSoldierFrame();

	// フレームを削除
	void Kill() override;

	// 中心位置の割合を設定
	void SetCenterRatio(const CVector2& ratio);

	// 更新処理
	void Update();

};

#endif