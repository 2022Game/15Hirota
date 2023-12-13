#ifndef CMODEL_H
#define CMODEL_H
//vector�̃C���N���[�h
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#include "CVertex.h"
#include "CResource.h"
#include "CColor.h"

/*
���f���N���X
���f���f�[�^�̓��͂�\��
*/
class CModel : public CResource
{
	friend CResourceManager;
public:
	std::vector<CTriangle> Triangles() const;

	// �J���[��ݒ�
	void SetColor(const CColor& color);
	// �J���[���擾
	const CColor& GetColor() const;
	// �A���t�@�l�ݒ�
	void SetAlpha(float alpha);
	// �A���t�@�l�擾
	float GetAlpha() const;

	//�`��
	void Render();
	//�`��
	//Render(�s��)
	void Render(const CMatrix& m);
private:
	CModel();
	~CModel();
	//���f���ǂݍ���
	bool Load(std::string path, bool dontDelete) override;
	//�}�e���A���ǂݍ���
	bool LoadMaterial(std::string path, bool dontDelete);
	void CreateVertexBuffer();
	//�}�e���A���|�C���^�̉ϒ��z��
	std::vector<CMaterial*> mpMaterials;
	//�O�p�`�̉ϒ��z��
	std::vector<CTriangle> mTriangles;
	//���_�̔z��
	CVertex* mpVertexes;
	//���f���̃J���[
	CColor mColor;
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
