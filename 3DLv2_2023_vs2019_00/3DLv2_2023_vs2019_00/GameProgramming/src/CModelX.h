#ifndef CMODELX_H	//�C���N���[�h
#define CMODELX_H

#include <vector>		//�x�N�g���N���X�̃C���N���[�h(���I�z��)
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h

//�錾
class CModelX;
class CModelXFrame;
class CMesh;
class CVector;

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
private:
	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix mTransformMatrix;			//�ϊ��s��
	char* mpName;						//�t���[�����O
	int mIndex;							//�t���[���ԍ�
	CMesh* mpMesh;						//Mesh�f�[�^
};

class CModelX {
	friend CModelXFrame;
public:
	~CModelX();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	CModelX();
	//�t�@�C���ǂݍ���
	void Load(char* file);
	//�P��̎��o��
	char* GetToken();
	char* Token();
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
private:
	int mVertexNum;		//���_��
	CVector* mpVertex;	//���_�f�[�^
	int mFaceNum;		//�ʐ�
	int* mpVertexIndex;	//�ʂ��\�����钸�_�C���f�b�N�X
	
};
#endif
