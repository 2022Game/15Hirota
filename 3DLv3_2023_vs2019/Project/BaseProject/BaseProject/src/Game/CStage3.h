#ifndef CSTAGE3_H
#define CSTAGE3_H
#include "CStageBase.h"

class CFinalStageField;
class CFinalStageFallCol;
class CStageTime;
class CStageSky;

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
	CFinalStageField* mpFinalStage;
	CFinalStageFallCol* mpFinalStageFallCol;

	CStageSky* mpSky;
};
#endif