#ifndef CEXSTAGE_H
#define CEXSTAGE_H

#include "CStageBase.h"

class CEXStageField;
class CStageTime;
class CStageSky;

// EX�X�e�[�W
class CEXStage : public  CStageBase
{
public:
	CEXStage();
	~CEXStage();

	void Load() override;
	void Update() override;
	void Unload() override;

private:
	CEXStageField* mpStage;

	CStageSky* mpSky;

	float mElapsedTime;
};
#endif