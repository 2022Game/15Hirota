#ifndef CMODELX_H	//�C���N���[�h
#define CMODELX_H

#include <vector>		//�x�N�g���N���X�̃C���N���[�h(���I�z��)
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h

#define MODEL_FILE "res\\���O�i.x"	//���̓t�@�C����

//�錾
class CModelX;
class CModelXFrame;
class CMesh;
class CVector;
class CMaterial;	//�}�e���A���錾
class CSkinWeights;	//�X�L���E�F�C�g�N���X
class CAnimationSet;	//�A�j���[�V�����Z�b�g�N���X
class CAnimation;		//�A�j���[�V�����N���X
class CAnimationKey;	//�A�j���[�V�����L�[�N���X

#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0]))

/*
IsDelimiter(c)
c��\t \r \n �X�y�[�X�Ȃǂ̋󔒕���
�܂���,;�Ȃǂ̕����ł����
��؂蕶���Ƃ���true��Ԃ�
*/

//���Ȉ�J�����}�N����
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a;a = nullptr;}
/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/



//CModelXFrame�̒�`
class CModelXFrame {
	friend CModelX;
	friend CAnimation;
	friend CAnimationSet;
public:
	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	//�f�X�g���N�^
	~CModelXFrame();
	void Render();
	int Index();
	//�����s��̍쐬
	void AnimateCombined(CMatrix* parent);
	const CMatrix& CombinedMatrix();
private:
	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix mTransformMatrix;			//�ϊ��s��
	char* mpName;						//�t���[�����O
	int mIndex;							//�t���[���ԍ�
	CMesh* mpMesh;						//Mesh�f�[�^
	CMatrix mCombinedMatrix;			//�����s��
};

class CModelX {
	friend CModelXFrame;
	friend CSkinWeights;
	friend CAnimationSet;
	friend CAnimation;
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
	//�t���[�����ɊY������t���[���̃A�h���X��Ԃ�
	CModelXFrame* FindFrame(char* name);
	std::vector<CAnimationSet*>& AnimationSet();
	void AnimateFrame();
	std::vector<CModelXFrame*>& Frames();
	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	void SetSkinWeightFrameIndex();
	//���_�A�j���[�V������K�p
	void AnimateVertex();
	//�}�e���A���z��̎擾
	std::vector<CMaterial*>& Material();
	//�}�e���A���̌���
	CMaterial* FindMaterial(char* name);
private:
	std::vector<CModelXFrame*> mFrame;	//�t���[���̔z��
	std::vector<CAnimationSet*> mAnimationSet;	//�A�j���[�V�����Z�b�g�̔z��
	//�}�e���A���z��
	std::vector<CMaterial*> mMaterial;
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
	//�X�L���E�F�C�g�Ƀt���[���ԍ���ݒ肷��
	void SetSkinWeightFrameIndex(CModelX* model);
	//���_�ɃA�j���[�V�����K�p
	void AnimateVertex(CModelX* model);
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

	CVector* mpAnimateVertex;	//�A�j���[�V�����p���_
	CVector* mpAnimateNormal;	//�A�j���[�V�����p�@��
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

/*
CAnimationSet
�A�j���[�V�����Z�b�g
*/
class CAnimationSet {
	friend CModelX;
public:
	CAnimationSet(CModelX* model);
	~CAnimationSet();
	void Time(float time);	//���Ԃ̐ݒ�
	void Weight(float weight);	//�d�݂̐ݒ�
	void AnimateMatrix(CModelX* model);
	std::vector<CAnimation*>& Animation();
	float Time();
	float MaxTime();
private:
	//�A�j���[�V�����Z�b�g��
	char* mpName;
	//�A�j���[�V����
	std::vector<CAnimation*> mAnimation;
	float mTime;	//���ݎ���
	float mWeight;	//�d��
	float mMaxTime;	//�ő厞��
};

/*
CAnimation
�A�j���[�V�����N���X
*/
class CAnimation {
	friend CAnimationSet;
	friend CModelX;
public:
	CAnimation(CModelX* model);
	~CAnimation();
private:
	char *mpFrameName;	//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
	int mKeyNum;	//�L�[��(���Ԑ�)
	CAnimationKey* mpKey;	//�L�[�̔z��
};

/*
CAnimationKey
�A�j���[�V�����L�[�N���X
*/
class CAnimationKey {
	friend CAnimation;
	friend CAnimationSet;
private:
	//����
	float mTime;
	//�s��
	CMatrix mMatrix;
};

#endif