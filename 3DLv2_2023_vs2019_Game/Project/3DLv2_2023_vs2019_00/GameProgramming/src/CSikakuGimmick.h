#ifndef CSIKAKUGIMMICK_H
#define CSIKAKUGIMMICK_H

#include "CTask.h"
#include "CSikaku.h"
#include "CTransform.h"

class CSikakuGimmick :public CTask
{
private:
	std::vector<CSikaku*> mSikakus;	//���X�g
	std::vector<CSikaku*> mMovingSikakus; // �ړ����������l�p�̃��X�g
	CModel* mpSikakuModel;	//���f���f�[�^
	CSikaku* mMovingSikaku;  // �ړ����������l�p��ێ����郁���o�ϐ�

	//����������
	void Init();
	//���X�g�ɒǉ�
	void CreateSikaku(CVector& pos, CVector& rot, CVector& scale);

protected:
	CVector mPosition;	//�ʒu

	int mMoveCounter;	//���]�t���O
	int mMoveDirection;	//���]�J�E���g
	bool mReverseMove; // �ړ������𔽓]������t���O

public:
	CSikakuGimmick();
	~CSikakuGimmick();

	//�ʒu�̎擾
	const CVector& Position() const;
	//Position(�ʒu)
	void Position(const CVector& v);

	//�X�V����
	void Update();
};
#endif