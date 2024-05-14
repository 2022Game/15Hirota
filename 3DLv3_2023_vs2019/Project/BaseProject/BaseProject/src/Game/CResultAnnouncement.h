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

	//インスタンスのポインタの取得
	static CResultAnnouncement* Instance();

	// 開く
	void Open();
	// 閉じる
	void Close();

	// マウスカーソルを検知する
	void HandleMouseInput();

	bool IsOpened() const;
	bool IsResultOpened() const;

	// どのメニューにするか
	void Decide(int select);

	void Update() override;
	void Render() override;

private:
	static CResultAnnouncement* spInstance;
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
	bool mResultOpened;
	float mElapsedTime;
	float mAlpha;
};
#endif