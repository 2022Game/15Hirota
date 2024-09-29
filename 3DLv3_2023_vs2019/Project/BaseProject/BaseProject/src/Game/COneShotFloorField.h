#ifndef CONESHOTFLOORFIELD_H
#define CONESHOTFLOORFIELD_H

#include "CObjectBase.h"
#include "CColliderMesh.h"
#include "CColliderSphere.h"

// �u�A���W�����v�X�e�[�W�v
class COneShotFloorField : public CObjectBase
{
public:
	// �R���X�g���N�^
	COneShotFloorField();
	// �f�X�g���N�^
	~COneShotFloorField();

	// �X�V����
	void Update() override; 
	// �`�揈��
	void Render() override;

private:
	// �X�e�[�W�̃��f��
	CModel* mpStageModel;
	// ���C�����f��
	CModel* mpLineModel;
	// �X�e�[�W�̃R���C�_�[
	CColliderMesh* mpStageFloorCol;
};
#endif