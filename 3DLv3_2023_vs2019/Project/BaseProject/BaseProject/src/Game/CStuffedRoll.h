#ifndef CSTUFFEDROLL_H
#define CSTUFFEDROLL_H

#include "CTask.h"

class CText;
class CImage;
class CFont;

// スタッフロールクラス
class CStuffedRoll : public CTask
{
public:
	// コンストラクタ
	CStuffedRoll();
	// デストラクタ
	~CStuffedRoll();

	// インスタンスのポインタ取得
	static CStuffedRoll* Instance();

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;
private:
	
	// インスタンス
	static CStuffedRoll* spInstance;

	// テキストを移動させる処理
	void ScrollTextUp(CText* pText, float& yPos, float speed);

	// フォントテキスト
	CFont* mpFont;
	// テキスト
	std::vector<CText*> mStuffedRolls;
	std::vector<float> mTextYPositions;

	struct StafData
	{
		std::string stuffName;
		float startTime;
	};
	static const StafData STAFF_DATA[];

	float mStaffRollTime;
};
#endif