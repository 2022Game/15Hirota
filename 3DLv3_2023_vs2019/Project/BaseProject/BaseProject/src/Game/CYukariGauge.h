#ifndef CYUKARIGAUGE_H
#define CYUKARIGAUGE_H
#include "CUIBase.h"
#include "CBillBoardImage.h"
#include "CObjectBase.h"
class CBillBoardImage;

class CYukariGauge :public CUIBase

{
private:
	CBillBoardImage* mpBarImage;	// バー画像

	int mMaxValue;				// 最大値
	int mValue;					// 現在値
public:
	// コンストラクタ
	CYukariGauge();
	// デストラクタ
	~CYukariGauge();

	//void Setup(const CVector& pos, const CVector& dir);

	// 最大値を設定
	void SetMaxValue(int value);
	// 現在地を設定
	void SetValue(int value);

	// バーの表示位置の割合を設定
	// (HPであれば、残りHPが最大HPと比べて何パーセント残っているかを設定)
	void SetPor(float per);

	// 更新処理
	void Update();

};
#endif