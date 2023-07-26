#ifndef CSIKAKUGIMMICK_H
#define CSIKAKUGIMMICK_H

#include "CTask.h"
#include "CSikaku.h"
#include "CTransform.h"
#include "CModel.h"
#include "CCharacter3.h"

class CSikakuGimmick :public CTask
{
public:
	CSikakuGimmick();
	~CSikakuGimmick();

	//�ʒu�̎擾
	const CVector& Position() const;
	//Position(�ʒu)
	void Position(const CVector& v);

	//�X�V����
	void Update();
private:
	CColliderMesh mColliderMesh;	//Field�̓����蔻��p�R���C�_
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

	int mMoveCounter;	//�ړ��J�E���^�[
	int mMoveDirection;	//���]�J�E���g
	bool mReverseMove; // �ړ������𔽓]������t���O
};
#endif