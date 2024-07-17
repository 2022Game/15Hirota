#ifndef COPERATIONINSTRUCTIONSUI_H
#define COPERATIONINSTRUCTIONSUI_H

#include "CUIBase.h"
#include "CVector.h"

class CImage;

// 操作説明UIクラス
class COperationInstructionsUI : public CUIBase
{
public:
	// コンストラクタ
	COperationInstructionsUI(std::string path);
	// デストラクタ
	~COperationInstructionsUI();

	// タスクを切るする
	void Kill() override;

	// 画像のセンターサイズを設定
	void SetCenterRatio(const CVector2& ratio);

	// ワールド座標を設定
	void SetWorldPos(const CVector& worldPos);

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;

private:
	// パス名
	std::string mPath;
	//// UI画像
	//std::vector<CImage*> mUIimages;
	// TUI画像
	CImage* mpTUI;
	// ENTERUI画像
	CImage* mpEnterUI;
	// バック画像
	CImage* mpBG;
	struct UIData
	{
		std::string UIName;	// テキスト名
	};
	static const UIData UI_DATA[];

	// 中心位置の割合
	CVector2 mCenterRatio;
	// 画像のスケール値
	float mScale;
};
#endif