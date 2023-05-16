#ifndef CMODELX_H	//�C���N���[�h
#define CMODELX_H

#include <vector>		//�x�N�g���N���X�̃C���N���[�h(���I�z��)
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h

//�錾
class CModelX;
class CModelXFrame;
class CMesh;
class CVector;
class CMaterial;	//�}�e���A���錾
class CSkinWeights;	//�X�L���E�F�C�g�N���X

/*
IsDelimiter(c)
c��\t \r \n �X�y�[�X�Ȃǂ̋󔒕���
�܂���,;�Ȃǂ̕����ł����
��؂蕶���Ƃ���true��Ԃ�
*/

#define MODEL_FILE "res\\sample.blend.x"	//���̓t�@�C����

//���Ȉ�J�����}�N����
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a;a = nullptr;}
/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/

//CModelXFrame�̒�`
class CModelXFrame {
	friend CModelX;
public:
	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	//�f�X�g���N�^
	~CModelXFrame();
	void Render();
private:
	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix mTransformMatrix;			//�ϊ��s��
	char* mpName;						//�t���[�����O
	int mIndex;							//�t���[���ԍ�
	CMesh* mpMesh;						//Mesh�f�[�^
};

class CModelX {
	friend CModelXFrame;
	friend CSkinWeights;
public:
	~CModelX();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	CModelX();
	//�t�@�C���ǂݍ���
	void Load(char* file);
	void Render();
	//�P��̎��o��
	char* GetToken();
	char* Token();
	bool EOT();	//�g�[�N���������Ȃ�����ture
private:
	std::vector<CModelXFrame*> mFrame;	//�t���[���̔z��	
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�t
	//c����؂蕶���Ȃ�true��Ԃ�
	bool IsDelimiter(char c);
};

//CMesh�N���X�̒�`��ǉ�����
class CMesh {
	friend CModelX;
	friend CModelXFrame;
public:
	//�R���X�g���N�^
	CMesh();
	//�f�X�g���N�^
	~CMesh();
	//�ǂݍ��ݏ���
	void Init(CModelX* model);
	void Render();
private:
	int mVertexNum;		//���_��
	CVector* mpVertex;	//���_�f�[�^
	int mFaceNum;		//�ʐ�
	int* mpVertexIndex;	//�ʂ��\�����钸�_�C���f�b�N�X
	int mNormalNum;		//�@��
	CVector* mpNormal;	//�@���x�N�g��
	int mMaterialNum;	//�}�e���A����
	int mMaterialIndexNum;	//�}�e���A���ԍ���(�ʐ�)
	int* mpMaterialIndex;	//�}�e���A���ԍ�

	std::vector<CMaterial*> mMaterial;	//�}�e���A���f�[�^
	std::vector<CSkinWeights*>mSkinWeights;	//�X�L���E�F�C�g
};

/*
CSkinWeights
�X�L���E�F�C�g�N���X
*/
class CSkinWeights {
	friend CModelX;
	friend CMesh;
public:
	CSkinWeights(CModelX* model);
	~CSkinWeights();
	const int& FrameIndex();
	const CMatrix& Offset();
private:
	char* mpFrameName;	//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
	int mIndexNum;		//���_�ԍ���
	int* mpIndex;		//���_�ԍ��z��
	float* mpWeight;	//���_�E�F�C�g�z��
	CMatrix mOffset;	//�I�t�Z�b�g�}�g���b�N�X
};
#endif
