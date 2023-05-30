#ifndef CSHOUGAIBUTUKIMMICK_H
#define CSHOUGAIBUTUKIMMICK_H
#include "CTask.h"
#include "CShougaibutuA.h"

class CShougaibutuGimmick : public CTask
{
private:
	std::vector<CShougaibutuA*> mShougaibutuAs;
	CModel* mpShougaibutuA;

	//初期化処理
	void Init();
	//コインを生成してリストに追加
	void CreateShougaibutuA(CVector& pos, CVector& rot, CVector& scale);
public:
	CShougaibutuGimmick();
	~CShougaibutuGimmick();

	//更新処理
	void Update();
};
#endif