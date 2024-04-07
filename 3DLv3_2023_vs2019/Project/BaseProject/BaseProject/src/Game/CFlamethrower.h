#pragma once
#include "CTask.h"
#include "CObjectBase.h"
#include <list>

class CFlame;

// �Ή����˃N���X
class CFlamethrower : public CTask
{
public:
	// �R���X�g���N�^
	CFlamethrower(CObjectBase* owner, const CMatrix* attach,
		const CVector& offsetPos = CVector::zero,
		const CMatrix& offsetRot = CMatrix::identity);
	// �f�X�g���N�^
	~CFlamethrower();

	// ���𔭎ˊJ�n
	void Start();
	// ���𔭎˒�~
	void Stop();

	// ���𔭎˂��Ă��邩�ǂ���
	bool IsThrowing() const;

	// ���ˎ��̃I�t�Z�b�g�ʒu��ݒ�
	void SetThrowOffsetPos(const CVector& pos);
	// ���ˎ��̃I�t�Z�b�g��]�l��ݒ�
	void SetThrowOffsetRot(const CMatrix& rot);


	// �X�V
	void Update() override;

private:
	// ���̃G�t�F�N�g���쐬
	void CreateFlame();

	// ���̔��ˈʒu���擾
	CVector GetThrowPos() const;
	// ���̔��˕������擾
	CVector GetThrowDir() const;

	// ���˂������̃G�t�F�N�g�̃��X�g
	std::list<CFlame*> mFlames;
	CObjectBase* mpOwner;		// ���̃G�t�F�N�g�̎�����
	const CMatrix* mpAttachMtx;	// �G�t�F�N�g���A�^�b�`����s��
	CVector mThrowOffsetPos;	// ���ˎ��̃I�t�Z�b�g�ʒu
	CMatrix mThrowOffsetRot;	// ���ˎ��̃I�t�Z�b�g��]�l
	float mElapsedTime;			// �o�ߎ��Ԍv���p
	bool mIsThrowing;			// ���𔭎˂��Ă��邩
};