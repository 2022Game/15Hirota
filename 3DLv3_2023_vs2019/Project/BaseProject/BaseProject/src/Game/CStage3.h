#ifndef CSTAGE3_H
#define CSTAGE3_H
#include "CStageBase.h"

class CStageTime;

// �X�e�[�W3�u�����V���b�g�E�t���A�v
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

};
#endif