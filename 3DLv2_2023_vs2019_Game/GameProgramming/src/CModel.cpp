#include "CModel.h"
//�W�����͂̃C���N���[�h
#include <stdio.h>
//CVector�̃C���N���[�h
#include "CVector.h"
#include "CTriangle.h"
#include "CTexture.h"
#include "CTransform.h"

//������s1�ƕ�����s2�̔�r
//s1��s2�����������0��
//�������Ȃ����0�ȊO��Ԃ�
int strcmp(const char* s1, const char* s2)
{
	int i = 0;
	//�����������Ԃ͌J��Ԃ�
	//�ǂ��炩�̕������I���ɂȂ�ƃ��[�v�̏I���
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	//�����Ȃ������0
	return s1[i] - s2[i];
}

std::vector<CTriangle> CModel::Triangles()const
{
	return mTriangles;
}

//���f���t�@�C���̓���
//Load(���f���t�@�C�����A�}�e���A���t�@�C����)
void CModel::Load(char* obj, char* mtl) {

	//���_�f�[�^�̕ۑ�(CVector�^)
	std::vector<CVector> vertex;
	//�@���f�[�^�̕ۑ�
	std::vector<CVector> normal;
	//�e�N�X�`���}�b�s���O�̕ۑ�
	std::vector<CVector> uv;



	//�t�@�C���|�C���^�ϐ��̍쐬
	FILE* fp;
	//�t�@�C������f�[�^�����
	//���̓G���A���쐬����
	char buf[256];

		//�t�@�C���̃I�[�v�� "mtl"
		//fopen(�t�@�C�����A���[�h)
		//�I�[�v���ł��Ȃ��Ƃ���NULL��Ԃ�
		fp = fopen(mtl, "r");
	//�t�@�C���I�[�v���G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[�o�͂��Ė߂�
		printf("%s file open error\n", mtl);
		return;
	}
	//�}�e���A���C���f�b�N�X
	int idx = 0;
	//f�t�@�C������1�s����
	//fgets(���̓G���A�A�G���A�T�C�Y�A�t�@�C���|�C���^)
	//�t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//�f�[�^�𕪊�����
		char str[4][64] = { "","","","" };
		//�����񂩂�f�[�^���S�ϐ��֑������
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//�擪��newmtl�̎��A�}�e���A����ǉ�����
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial* pm = new CMaterial();
			//�}�e���A�����̐ݒ�
			pm->Name(str[1]);
			//�}�e���A���̉ϒ��z��ɒǉ�
			mpMaterials.push_back(pm);
			//�z��̒������擾
			idx = mpMaterials.size() - 1;
		}
		//�擪��kd�̎��ADiffuse��ݒ肷��
		else if (strcmp(str[0], "Kd") == 0) {
			mpMaterials[idx]->Diffuse()[0] = atof(str[1]);
			mpMaterials[idx]->Diffuse()[1] = atof(str[2]);
			mpMaterials[idx]->Diffuse()[2] = atof(str[3]);
		}
		//�擪��d�̎��Ad�l��ݒ肷��
		else if (strcmp(str[0], "d") == 0) {
			mpMaterials[idx]->Diffuse()[3] = atof(str[1]);
		}
		//�擪��map_Kd�̎��A�e�N�X�`������͂���
		else if (strcmp(str[0], "map_Kd") == 0) {
			mpMaterials[idx]->Texture()->Load(str[1]);
		}
		//���͂����l���R���\�[���ɏo�͂���
		//printf("%s", buf); �ォ�������
	}
	//�t�@�C���̃N���[�Y
	fclose(fp);

	//	�t�@�C���̃I�[�v�� "obj"
	//fopen(�t�@�C�����A���[�h)
	//�I�[�v���ł��Ȃ��Ƃ���NULL��Ԃ�
	fp = fopen(obj, "r");
	//�t�@�C���I�[�v���G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[���o�͂��Ė߂�
		printf("%s file open error\n", obj);
		return;
	}
	//�t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {

		//�f�[�^�𕪊�����
		char str[4][64] = { "","","","" };
		//�����񂩂�f�[�^4�ϐ��֑������
		//sscanf(������A�ϊ��w��q�A�ϐ�)
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);

		//������̔�r
		//strcmp(������1�A������Q)
		// ������P�ƕ�����Q�������Ƃ�0�A�قȂ�Ƃ�0�ȊO��Ԃ�
		// �擪��v�̎��A���_��vertex�ɒǉ�����
		if (strcmp(str[0], "v") == 0) {
			//�ϒ��z��verte�ɒǉ�
			//atof(������)�@�����񂩂�float�^�̒l��Ԃ�
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		else if (strcmp(str[0], "vn") == 0) {
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		//�擪��vt�̎��Auv�ɒǉ�����
		else if (strcmp(str[0], "vt") == 0) {
			//�ϒ��z��uv�ɒǉ�
			//atof(������) �����񂩂�float�^�̒l��Ԃ�
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}
		//�擪��f�̎��A�O�p�`���쐬���Ēǉ�����
		else if (strcmp(str[0], "f") == 0) {
			//���_�Ɩ@���̔ԍ��쐬
			int v[3], n[3];
			//�e�N�X�`���}�b�s���O�̗L���𔻒�
			if (strstr(str[1], "//")) {
				//���_�Ɩ@���̔ԍ��擾
				sscanf(str[1], "%d//%d", &v[0], &n[0]);
				sscanf(str[2], "%d//%d", &v[1], &n[1]);
				sscanf(str[3], "%d//%d", &v[2], &n[2]);

				//�O�p�`�쐬
				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//�}�e���A���ԍ��̎擾
				t.MaterialIdx(idx);
				//�ϒ��z��mTriangles�ɎO�p�`��ǉ�
				mTriangles.push_back(t);
			}
			else {
				//�e�N�X�`���}�b�s���O�L��
				int u[3];//�e�N�X�`���}�b�s���O�̔ԍ�
				//���_�Ɩ@���̔ԍ��擾�̔ԍ��擾
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]);
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);
				//�O�p�`�쐬
				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//�e�N�X�`���}�b�s���O�̐ݒ�
				t.UV(uv[u[0] - 1], uv[u[1] - 1], uv[u[2] - 1]);
				//�}�e���A���ԍ��̐ݒ�
				t.MaterialIdx(idx);
				//�ϒ��z��mTriangles�ɎO�p�`��ǉ�
				mTriangles.push_back(t);
			}
		}
		//�擪��usemtl�̎��A�}�e���A���C���f�b�N�X���擾����
		else if (strcmp(str[0], "usemtl") == 0) {
			//�ϒ��z����ォ���r
			for (idx = mpMaterials.size() - 1; idx > 0; idx--) {
				//�������O�̃}�e���A��������΃��[�v�I��
				if (strcmp(mpMaterials[idx]->Name(), str[1]) == 0) {
					break;//���[�v����o��
				}
			}
		}

		//�ϒ��z��mTriangles�ɎO�p�`��ǉ�
		//���͂����l���R���\�[���ɏo�͂���
//		printf("%s", buf);

	}
	//�t�@�C���̃N���[�Y
	fclose(fp);

	CreateVertexBuffer();
}

void CModel::CreateVertexBuffer()
{
	mpVertexes = new CVertex[mTriangles.size() * 3];
	int idx = 0;
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		for (int j = 0; j < mTriangles.size(); j++)
		{
			if (i == mTriangles[j].MaterialIdx())
			{
				mpMaterials[i]->VertexNum(mpMaterials[i]->VertexNum() + 3);
				mpVertexes[idx].mPosition = mTriangles[j].V0();
				mpVertexes[idx].mNormal = mTriangles[j].N0();
				mpVertexes[idx++].mTextureCoords = mTriangles[j].U0();
				mpVertexes[idx].mPosition = mTriangles[j].V1();
				mpVertexes[idx].mNormal = mTriangles[j].N1();
				mpVertexes[idx++].mTextureCoords = mTriangles[j].U1();
				mpVertexes[idx].mPosition = mTriangles[j].V2();
				mpVertexes[idx].mNormal = mTriangles[j].N2();
				mpVertexes[idx++].mTextureCoords = mTriangles[j].U2();
			}
		}
	}
}

void CModel::Render()
{
	//�ϒ��z��̗v�f�������J��Ԃ�
	for (int i = 0; i < mTriangles.size(); i++) {
		//�}�e���A���̓K�p
		mpMaterials[mTriangles[i].MaterialIdx()]->Enbled();
		//�ϒ��z��ɓY�����ŃA�N�Z�X����
		mTriangles[i].Render();
		//�}�e���A���𖳌�
		mpMaterials[mTriangles[i].MaterialIdx()]->Disabled();
	}
}


//�`��
//Render(�s��)
void CModel::Render(const CMatrix &m)
{
	//�s��̑ޔ�
	glPushMatrix();
	//�����s����|����
	glMultMatrixf(m.M());
	//���_���W�̈ʒu��ݒ�
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(CVertex), (void*)&mpVertexes[0].mPosition);
	//�@���x�N�g���̈ʒu��ݒ�
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(CVertex), (void*)&mpVertexes[0].mNormal);
	//�e�N�X�`���}�b�s���O�̈ʒu��ݒ�
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CVertex), (void*)&mpVertexes[0].mTextureCoords);

	int first = 0;//�`��ʒu
	//�}�e���A�����ɕ`�悷��
	for (size_t i = 0; i < mpMaterials.size(); i++) {
		//�}�e���A����K�p����
		mpMaterials[i]->Enbled();
		//�`��ʒu����̃f�[�^�ŎO�p�`��`�悵�܂�
		glDrawArrays(GL_TRIANGLES, first, mpMaterials[i]->VertexNum());
		//�}�e���A���𖳌��ɂ���
		mpMaterials[i]->Disabled();
		//�`��ʒu���ړ�
		first += mpMaterials[i]->VertexNum();
	}
	//�s���߂�
	glPopMatrix();

	//���_���W�̔z��𖳌��ɂ���
	glDisableClientState(GL_VERTEX_ARRAY);
	//�@���̔z��𖳌��ɂ���
	glDisableClientState(GL_NORMAL_ARRAY);
	//�e�N�X�`���}�b�s���O�̔z��𖳌��ɂ���
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

CModel::~CModel()
{
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		delete mpMaterials[i];
	}
	delete[] mpVertexes;
}