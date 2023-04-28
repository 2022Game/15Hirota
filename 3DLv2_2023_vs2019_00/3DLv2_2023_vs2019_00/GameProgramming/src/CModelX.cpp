#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "CModelX.h"
#include "glut.h"
#include "CVector.h"

CModelX::CModelX()
	:mpPointer(nullptr)
{
	//mToken��������
	memset(mToken, 0, sizeof(mToken));
}

CModelX::~CModelX()
{
	if (mFrame.size() > 0)
	{
		delete mFrame[0];
	}
}

CModelXFrame::~CModelXFrame()
{
	if (mpMesh != nullptr)
	{
		delete mpMesh;
		mpMesh = nullptr;
	}
	{
		//�q�t���[����S�ĉ������
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++) {
			delete* itr;
		}
		//���O�̃G���A���������
		SAFE_DELETE_ARRAY(mpName);
	}
}

//�R���X�g���N�^
CMesh::CMesh()
	:mVertexNum(0)
	,mpVertex(nullptr)
	,mFaceNum(0)
	,mpVertexIndex(nullptr)
	,mNormalNum(0)
	,mpNormal(nullptr)
{}

//�f�X�g���N�^
CMesh::~CMesh(){
	SAFE_DELETE_ARRAY(mpVertex);
	SAFE_DELETE_ARRAY(mpVertexIndex);
	SAFE_DELETE_ARRAY(mpNormal);
}

char* CModelX::Token()
{
	return mToken;
}

/*
Init
Mesh�̃f�[�^����荞��
*/
void CMesh::Init(CModelX* model){
	model->GetToken();	//{ or ���O
	if (!strchr(model->Token(), '{')) {
		//���O�̏ꍇ�A����{
		model->GetToken();	//{
	}

	//���_���̎擾
	mVertexNum = atoi(model->GetToken());
	//���_�����G���A�m��
	mpVertex = new CVector[mVertexNum];
	// ���_�����R���\�[���ɏo��
	//printf("VertexNum:%d\n", mVertexNum);
	//���_�����f�[�^����荞��
	for (int i = 0; i < mVertexNum; i++) {
		mpVertex[i].X(atof(model->GetToken()));
		mpVertex[i].Y(atof(model->GetToken()));
		mpVertex[i].Z(atof(model->GetToken()));
		//printf(" %10f %10f %10f\n", mpVertex[i].X(), mpVertex[i].Y(), mpVertex[i].Z());
	}
	//�ʐ��ǂݍ���
	mFaceNum = atoi(model->GetToken());
	//���_����1�ʂ�3���_
	mpVertexIndex = new int[mFaceNum * 3];
	//printf("FaceNum:%d\n", mFaceNum);
	for (int i = 0; i < mFaceNum * 3; i += 3) {
		model->GetToken();	//���_���ǂݔ�΂�
		mpVertexIndex[i] = atoi(model->GetToken());
		mpVertexIndex[i + 1] = atoi(model->GetToken());
		mpVertexIndex[i + 2] = atoi(model->GetToken());
		//printf(" %2d %2d %2d\n", mpVertexIndex[i], mpVertexIndex[i + 1], mpVertexIndex[i + 2]);
	}
	model->GetToken();	//MeshNormals
	if (strcmp(model->Token(), "MeshNormals") == 0) {
		model->GetToken();	//{
		//�@���f�[�^���擾
		mNormalNum = atoi(model->GetToken());
		//�@���̃f�[�^��z��Ɏ�荞��
		CVector* pNormal = new CVector[mNormalNum];
		for (int i = 0; i < mNormalNum; i++) {
			pNormal[i].X(atof(model->GetToken()));
			pNormal[i].Y(atof(model->GetToken()));
			pNormal[i].Z(atof(model->GetToken()));
		}
		//�@�������ʐ��~3
		mNormalNum = atoi(model->GetToken()) * 3;	//FaceNum
		int ni;
		//���_���ɖ@���f�[�^��ݒ肷��
		mpNormal = new CVector[mNormalNum];
		//printf("NormalNum:%d\n", mNormalNum);
		for (int i = 0; i < mNormalNum; i += 3) {
			model->GetToken();	//3
			ni = atoi(model->GetToken());
			mpNormal[i] = pNormal[ni];

			//�ۑ�...
			ni = atoi(model->GetToken());
			mpNormal[i + 1] = pNormal[ni];

			ni = atoi(model->GetToken());
			mpNormal[i + 2] = pNormal[ni];
			//�ۑ�...
			/*printf(" %10f %10f %10f\n %10f %10f %10f\n %10f %10f %10f\n",
				mpNormal[i].X(), mpNormal[i].Y(), mpNormal[i].Z(),
				mpNormal[i + 1].X(), mpNormal[i + 1].Y(), mpNormal[i + 1].Z(),
				mpNormal[i + 2].X(), mpNormal[i + 2].Y(), mpNormal[i + 2].Z());*/
		}
		delete[] pNormal;
		model->GetToken();	//}
	}//End of MeshNormalas
}

void CModelX::Load(char* file) {
	//
	//�t�@�C���T�C�Y���擾����
	//
	FILE* fp;	//�t�@�C���|�C���^�ϐ��̍쐬

	fp = fopen(file, "rb");	//�t�@�C�����I�[�v������
	if (fp == NULL) {	//�G���[�`�F�b�N
		printf("fopen error:%s\n", file);
		return;
	}
	//�t�@�C���̍Ō�ֈړ�
	fseek(fp, 0L, SEEK_END);
	//�t�@�C���T�C�Y�̎擾
	int size = ftell(fp);
	//�t�@�C���T�C�Y�{1�o�C�g���̗̈���m��
	char* buf = mpPointer = new char[size + 1];
	//
	//�t�@�C������3D���f���̃f�[�^��ǂݍ���
	//
	//�t�@�C���̐擪�ֈړ�
	fseek(fp, 0L, SEEK_SET);
	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���f�[�^��ǂݍ���
	fread(buf, size, 1, fp);
	//�Ō��\0��ݒ肷��(������̏I�[)
	buf[size] = '\0';

	//������̍Ō�܂ŌJ��Ԃ�
	while (*mpPointer != '\0') {
		GetToken();
		//�P�ꂪFrame�̏ꍇ
		if (strcmp(mToken, "Frame") == 0) {
			//�t���[�����쐬����
			new CModelXFrame(this);
		}
	}

	//fclose(fp);	//�t�@�C�����N���[�Y����

	SAFE_DELETE_ARRAY(buf);	//�m�ۂ����̈���������
}

/*
GetToke
������f�[�^����A�P�����擾����
*/
char* CModelX::GetToken() {
	char* p = mpPointer;
	char* q = mToken;
	//�^�u(\t)��()���s()\r(\n),;"�̋�؂蕶���ȊO�ɂȂ�܂œǂݔ�΂�
	while (*p != '\0' && IsDelimiter(*p)) p++;
	if (*p == '{' || *p == '}') {
		//{�܂���}�Ȃ�mToken�ɑ�������̕�����
		*q++ = *p++;
	}
	else {
		//�^�u(\t)��()(\r)(\n),;"�̋�؂蕶���A
		//�܂��́A}�̕����ɂȂ�܂�mToken�ɑ������
		while (*p != '\0' && !IsDelimiter(*p) && *p != '}')
			*q++ = *p++;
	}

	*q = '\0';	//mToken�̍Ō��\0����
	mpPointer = p;	//���̓ǂݍ��ރ|�C���g���X�V����

	//����mToken��\\�̏ꍇ�́A�R�����g�Ȃ̂ŉ��s����܂œǂݔ�΂�
	/*
	strcmp(������1�A������2)
	������P�ƕ�����Q���������ꍇ�A0��Ԃ��܂�
	������P�ƕ�����Q���������Ȃ��ꍇ�A0��Ԃ��܂�
	*/
	if (!strcmp("//", mToken)) {
		//���s�܂œǂݔ�΂�
		while (*p != '\0' && !strchr("\r\n", *p)) p++;
		//�ǂݍ��݈ʒu�̍X�V
		mpPointer = p;
		//�P����擾����(�ċN�Ăяo��)
		return GetToken();
	}
	return mToken;
}

bool CModelX::IsDelimiter(char c)
{
	//isspace(c)
	//c���󔒂Ȃ�0�ȊO��Ԃ�
	if (isspace(c) != 0)
		return true;
	/*
	strchr(������A����)
	�������������ւ̃|�C���^��Ԃ�
	������Ȃ�������NULL��Ԃ�
	*/
	if (strchr(",;\"", c) != NULL)
		return true;
	//��؂蕶���ł͂Ȃ�
	return false;
}

/*
SkipNode
�m�[�h��ǂݔ�΂�
*/
void CModelX::SkipNode() {
	//�������I�������I��
	while (*mpPointer != '\0') {
		GetToken();	//���̒P��擾
		//{�����������烋�[�v�I��
		if (strchr(mToken, '{'))break;
	}
	int count = 1;
	//�������I��邩�A�J�E���g��0�ɂȂ����I��
	while (*mpPointer != '\0' && count > 0) {
		GetToken();	//���̒P��擾
		//{��������ƃJ�E���g�A�b�v
		if (strchr(mToken, '{'))count++;
		//{��������ƃJ�E���g�_�E��
		else if (strchr(mToken, '}'))count--;
	}
}

/*
CModelXFrame
model:CModelX�C���X�^���X�ւ̃|�C���^
�t���[�����쐬����
�ǂݍ��ݒ���Frame��������΁A�t���[�����쐬���A
�q�t���[���ɒǉ�����
*/
CModelXFrame::CModelXFrame(CModelX* model)
	:mpName(nullptr)
	, mpMesh(nullptr)
	, mIndex(0)
{
	//���݂̃t���[���z��̗v�f�����擾���ݒ肷��
	mIndex = model->mFrame.size();
	//CModelX�̃t���[���z��ɒǉ�����
	model->mFrame.push_back(this);
	//�ϊ��s���P�ʍs��ɂ���
	mTransformMatrix.Identity();
	//���̒P��(�t���[�����̗\��)���擾����
	model->GetToken();	//frame name
	//�t���[�������G���A���m�ۂ���
	mpName = new char[strlen(model->mToken) + 1];
	//�t���[�������R�s�[����
	strcpy(mpName, model->mToken);
	//���̒P��({�̗\��)���擾����
	model->GetToken();	//{
	
	//�������Ȃ��Ȃ�����I���
	while (*model->mpPointer != '\0') {
		//���̒P��擾
		model->GetToken();	//Frame
		//}�������̏ꍇ�͏I��
		if (strchr(model->mToken, '}'))break;
		//�V���ȃt���[���̏ꍇ�́A�q�t���[���ɒǉ�
		if (strcmp(model->mToken, "Frame") == 0) {
			//�t���[�����쐬���A�q�t���[���̔z��ɒǉ�
			mChild.push_back(new CModelXFrame(model));
		}
		else if (strcmp(model->mToken,"FrameTransformMatrix") == 0) {
			model->GetToken(); {
				for (int i = 0; i < mTransformMatrix.Size(); i++) {
					mTransformMatrix.M()[i] = atof(model->GetToken());
				}
				model->GetToken();
			}
		}
		else if (strcmp(model->mToken, "Mesh") == 0) {
			mpMesh = new CMesh();
			mpMesh->Init(model);
		}
		else {
			//��L�ȊO�̗v�f�͓ǂݔ�΂�
			model->SkipNode();
		}
	}

//�f�o�b�O�o�[�W�����̂ݗL��
#ifdef _DEBUG
	//printf("%s\n", mpName);
	//mTransformMatrix.Print();
#endif
}

/*
Render
��ʂɕ`�悷��
*/
void CMesh::Render(){
	/*���_�f�[�^�A�@���f�[�^�̔z���L���ɂ���*/
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	/*���_�f�[�^�A�@���f�[�^�̏ꏊ���w�肷��*/
	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
	glNormalPointer(GL_FLOAT, 0, mpNormal);

	/*���_�̃C���f�b�N�X�̏ꏊ���w�肵�Đ}�`��`�悷��*/
	glDrawElements(GL_TRIANGLES, 3 * mFaceNum,
		GL_UNSIGNED_INT, mpVertexIndex);

	/*���_�f�[�^�A�@���f�[�^�̔z��𖳌��ɂ���*/
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

/*
Render
��ʂɕ`�悷��
*/
void CModelXFrame::Render(){
	if (mpMesh != nullptr)
		mpMesh->Render();
}

/*
Render
�S�Ẵt���[���̕`�揈�����Ăяo��
*/
void CModelX::Render() {
	for (size_t i = 0; i < mFrame.size(); i++) {
		mFrame[i]->Render();
	}
}