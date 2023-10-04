#ifndef CMATERIAL_H
#define CMATERIAL_H
#include "CTexture.h"
#include "CModelX.h"
#define MATERIAL_NAME_LEN 64 //���O�̒���

class CMyShader;
/*
�}�e���A���N���X
�}�e���A���̃f�[�^������
*/
class CMaterial {
	friend CMyShader;
private:
	//�}�e���A�����̒��_��
	int mVertexNum;
	//�g�U���̐FRGBA
	float mDiffuse[4];
	float mPower;
	float mSpecular[3];
	float mEmissive[3];

	//�e�N�X�`���t�@�C����
	char* mpTextureFilename;
	//�}�e���A����
	char mName[MATERIAL_NAME_LEN + 1];
	//�e�N�X�`��
	CTexture mTexture;

public:
	//�e�N�X�`���̎擾
	CTexture* Texture();
	//�}�e���A���𖳌��ɂ���
	void Disabled();
	//�f�t�H���g�R���X�g���N�^
	CMaterial();
	CMaterial(CModelX* model);
	~CMaterial();
	//�}�e���A����L���ɂ���
	void Enabled();
	//�}�e���A���̖��O�̎擾
	char* Name();
	//�}�e���A���̖��O��ݒ肷��
	//Name(�}�e���A���̖��O)
	void Name(char* name);
	//mDiffuse�z��̎擾
	float* Diffuse();
	//���_���̐ݒ�
	//VertexNum(���_��)
	void VertexNum(int num);
	//���_���̎擾
	int VertexNum();
};

#endif

