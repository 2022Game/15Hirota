#ifndef CSTAGE3_H
#define CSTAGE3_H
#include "CStageBase.h"

class CField_Worlds_1;
class CField_Worlds_1_FallCol;
class CStageTime;

// �X�e�[�W3�u�����}�b�v�v
class CStage3 : public CStageBase
{
public:
	// �R���X�g���N�^
	CStage3();
	// �f�X�g���N�^
	~CStage3();

	// �X�e�[�W�ǂݍ���
	void Load() override;
	// �X�e�[�W�j��
	void Unload() override;

private:
	CField_Worlds_1* mpField_Worlds_1;	// �t�B�[���h
	CField_Worlds_1_FallCol* mpFallCol;
};
#endif