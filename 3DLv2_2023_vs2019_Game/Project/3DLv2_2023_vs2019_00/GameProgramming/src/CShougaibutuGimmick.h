#ifndef CSHOUGAIBUTUKIMMICK_H
#define CSHOUGAIBUTUKIMMICK_H
#include "CTask.h"
#include "CShougaibutuA.h"

class CShougaibutuGimmick : public CTask
{
private:
	std::vector<CShougaibutuA*> mShougaibutuAs;
	CModel* mpShougaibutuA;

	//����������
	void Init();
	//�R�C���𐶐����ă��X�g�ɒǉ�
	void CreateShougaibutuA(CVector& pos, CVector& rot, CVector& scale);
public:
	CShougaibutuGimmick();
	~CShougaibutuGimmick();

	//�X�V����
	void Update();
};
#endif