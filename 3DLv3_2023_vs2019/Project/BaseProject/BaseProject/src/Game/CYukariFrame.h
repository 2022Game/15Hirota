#ifndef CYUKARIFRAME_H
#define CYUKARIFRAME_H
class CImage;

#include "CUIBase.h"
#include "CVector.h"

class CYukariFrame : public CUIBase
{
private:
	CImage* mpFrameImage;
	CVector2 mCenterRatio;
	float mScale;
	bool mIsShow;

public:
	// コンストラクタ
	CYukariFrame();
	// デストラクタ
	~CYukariFrame();

	// フレームを削除
	void Kill() override;

	// 中心位置の割合を設定
	void SetCenterRatio(const CVector2& ratio);

	// ワールド座標を設定
	void SetWorldPos(const CVector& worldPos);

	// 更新処理
	void Update();
};
#endif