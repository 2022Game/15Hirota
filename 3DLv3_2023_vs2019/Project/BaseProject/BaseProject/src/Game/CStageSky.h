#ifndef CSTAGESKY_H
#define CSTAGESKY_H

#include "CObjectBase.h"
#include "CModel.h"

// �X�e�[�W�p�̋�I�u�W�F�N�g
class CStageSky : public CObjectBase
{
public:
	CStageSky();
	~CStageSky();

	void Update() override;
	void Render() override;	
private:
	CModel* mpStageSky;
};
#endif