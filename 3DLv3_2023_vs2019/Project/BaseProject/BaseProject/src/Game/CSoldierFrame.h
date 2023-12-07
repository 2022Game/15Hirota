#ifndef CSOLDIERFRAME_H
#define CSOLDIERFRAME_H
class CImage;

#include "CUIBase.h"

class CSoldierFrame :public CUIBase
{
private:
	CImage* mpFrameImage;		// 枠画像

public:
	// コンストラクタ
	CSoldierFrame();
	// デストラクタ
	~CSoldierFrame();

	// 更新処理
	void Update();

};

#endif