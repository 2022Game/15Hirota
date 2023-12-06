#ifndef CMODEL_H
#define CMODEL_H
//vector�̃C���N���[�h
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#include "CVertex.h"
#include "CResource.h"

/*
���f���N���X
���f���f�[�^�̓��͂�\��
*/
class CModel : public CResource
{
	friend CResourceManager;
public:
	std::vector<CTriangle> Triangles() const;
	//�`��
	void Render();
	//�`��
	//Render(�s��)
	void Render(const CMatrix& m);
private:
	~CModel();
	//���f���ǂݍ���
	bool Load(std::string path) override;
	//�}�e���A���ǂݍ���
	bool LoadMaterial(std::string path);
	void CreateVertexBuffer();
	//�}�e���A���|�C���^�̉ϒ��z��
	std::vector<CMaterial*> mpMaterials;
	//�O�p�`�̉ϒ��z��
	std::vector<CTriangle> mTriangles;
	//���_�̔z��
	CVertex* mpVertexes;
};

#include "CVertex.h"
#include <vector>

class CModelTest
{
public:
	CModelTest();
	void Render();

	CVertex mVertex[6];
	std::vector<CVertex> mVector;

};

#endif
