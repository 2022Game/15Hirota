#ifndef CSIKAKUGIMMICK_H
#define CSIKAKUGIMMICK_H

#include "CTask.h"
#include "CSikaku.h"
#include "CTransform.h"

class CSikakuGimmick :public CTask
{
private:
	std::vector<CSikaku*> mSikakus;	//リスト
	CModel* mpSikakuModel;	//モデルデータ

	//初期化処理
	void Init();
	//リストに追加
	void CreateSikaku(CVector& pos, CVector& rot, CVector& scale);

	CVector mPosition;	//位置
	CVector mVelocity;	//重力加速度

public:
	CSikakuGimmick();
	~CSikakuGimmick();

	const CVector& Position();
	void Velosity(const CVector& v);

	//更新処理
	void Update();
};
#endif