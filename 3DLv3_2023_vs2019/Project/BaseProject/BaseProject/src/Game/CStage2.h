#ifndef CSTAGE2_H
#define CSTAGE2_H
#include "CStageBase.h"

class CField1;

// �X�e�[�W1 �u�傫�ȕ����v
class CStage2 : public CStageBase
{
public:
	// �R���X�g���N�^
	CStage2();
	// �f�X�g���N�^
	~CStage2();

	// �X�e�[�W�ǂݍ���
	void Load() override;
	// �X�e�[�W�j��
	void Unload() override;

private:
	CField1* mpField1;
};
#endif