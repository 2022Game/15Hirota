#ifndef CSTAGE1_H
#define CSTAGE1_H
#include "CStageBase.h"

// �X�e�[�W1�u�����}�b�v�v
class CStage1 : public CStageBase
{
public:
	// �R���X�g���N�^
	CStage1();
	// �f�X�g���N�^
	~CStage1();

	// �X�e�[�W�ǂݍ���
	void Load() override;
	// �X�e�[�W�j��
	void Unload() override;

	void Render();
private:
};
#endif