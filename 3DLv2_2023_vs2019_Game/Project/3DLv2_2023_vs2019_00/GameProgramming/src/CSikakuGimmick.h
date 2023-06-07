#ifndef CSIKAKUGIMMICK_H
#define CSIKAKUGIMMICK_H

#include "CTask.h"
#include "CSikaku.h"
#include "CTransform.h"

class CSikakuGimmick :public CTask
{
private:
	std::vector<CSikaku*> mSikakus;	//���X�g
	CModel* mpSikakuModel;	//���f���f�[�^

	//����������
	void Init();
	//���X�g�ɒǉ�
	void CreateSikaku(CVector& pos, CVector& rot, CVector& scale);

	CVector mPosition;	//�ʒu
	CVector mVelocity;	//�d�͉����x

public:
	CSikakuGimmick();
	~CSikakuGimmick();

	const CVector& Position();
	void Velosity(const CVector& v);

	//�X�V����
	void Update();
};
#endif