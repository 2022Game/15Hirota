#ifndef CSTAGESELECTIONSTAGE_H
#define CSTAGESELECTIONSTAGE_H
#include "CStageBase.h"

// �X�e�[�W�I���X�e�[�W
class CStageSelectionStage : public CStageBase
{
public:
	// �R���X�g���N�^
	CStageSelectionStage();
	// �f�X�g���N�^
	~CStageSelectionStage();

	// �X�e�[�W�ǂݍ���
	void Load() override;
	// �X�e�[�W�j��
	void Unload() override;
private:
};
#endif