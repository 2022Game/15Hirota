#ifndef CRESULTANNOUNCEMENT_H
#define CRESULTANNOUNCEMENT_H

#include "CTask.h"
#include <vector>
class CImage;

// リザルト画面表示
// リザルト画面選択メニュー
class CResultAnnouncement : public CTask
{
public:
	// コンストラクタ
	CResultAnnouncement();
	// デストラクタ
	~CResultAnnouncement();

	// 開く
	void Open();
	// 閉じる
	void Close();

	// マウスカーソルを検知する
	void HandleMouseInput();

	bool IsOpened() const;

	// どのメニューにするか
	void Decide(int select);

	void Update() override;
	void Render() override;

private:
	// リザルトの画像
	CImage* mpResultsMenu;
	std::vector<CImage*> mResultsMenuItems;

	enum Result
	{
		A,
		B,
		C,
	};
	std::vector<std::pair<Result, CImage*>> mABCItems;
	int mSelectIndex;
	bool mIsOpened;
	float mElapsedTime;
	float mAlpha;
};
#endif