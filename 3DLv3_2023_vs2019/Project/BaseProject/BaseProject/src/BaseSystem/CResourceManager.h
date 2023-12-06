#pragma once
#include <string>
#include <map>
#include "CResource.h"

// ���\�[�X�Ǘ��N���X
class CResourceManager
{
public:
	// �C���X�^���X��j��
	static void ClearInstance();

	// ���\�[�X�ǂݍ���
	template <class T>
	static T* Load(std::string name, std::string path);
	// ���\�[�X�ǂݍ���
	template <class T>
	static T* Load(std::string path);
	// �ǂݍ��ݍς݂̃��\�[�X���擾
	template <class T>
	static T* Get(std::string name);

private:
	// �R���X�g���N�^
	CResourceManager();
	// �f�X�g���N�^
	~CResourceManager();

	// �C���X�^���X���擾
	static CResourceManager* Instance();

	// CResourceManager�̃C���X�^���X
	static CResourceManager* mpInstance;
	// �ǂݍ��ݍς݂̃��\�[�X�̃��X�g
	std::map<std::string, CResource*> mResources;
};