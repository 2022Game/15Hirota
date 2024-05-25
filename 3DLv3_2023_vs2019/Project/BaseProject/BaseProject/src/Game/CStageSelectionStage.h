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

	CVector GetPlayerStartPosition();

	// �X�e�[�W�ǂݍ���
	void Load() override;
	// �X�e�[�W�j��
	void Unload() override;

	// �X�V
	void Update() override;
private:
	// �X�e�[�W�̃f�[�^
	struct StageData
	{
		int stageNo;	// �X�e�[�W�ԍ�
		CVector btnPos;	// �X�e�[�W�̃{�^���̔ԍ�
		int prevStageNo;// �O�̃X�e�[�W�̔ԍ�
		int nextStageNo;// ���̃X�e�[�W�̔ԍ�
	};
	// �X�e�[�W�̃f�[�^�̃e�[�u��
	static const StageData STAGE_DATA[];

	// ���݂̃X�e�[�W�ԍ�
	int mSelectStageNo;
};
#endif