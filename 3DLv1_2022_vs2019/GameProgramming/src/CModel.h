#ifndef CMODEL_H
#define CMODEL_H
//vector�̃C���N���[�h
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#include "CVertex.h"

/*
���f���N���X
���f���f�[�^�̓��͂�\��
*/
class CModel {
public:
	//���f���t�@�C���̓���
	//Load(���f���t�@�C�����A�}�e���A���t�@�C����)
	void Load(char* obj, char* mtl);
	//�`��
	//Render(�s��)
	void Render(const CMatrix& m);
	//�`��
	void Render();

	~CModel();

private:
	//�O�p�`�̉ϒ��z��
	std::vector<CTriangle> mTriangles;
	//�@���f�[�^�̉ϒ��z��
	std::vector<CTriangle> mNormal;
	//�}�e���A���|�C���^�̉ϒ��z��
	std::vector<CMaterial*> mpMaterials;
	//���_�̔z��
	CVertex* mpVertexes;
	void CreateVertexBuffer();
};

#endif