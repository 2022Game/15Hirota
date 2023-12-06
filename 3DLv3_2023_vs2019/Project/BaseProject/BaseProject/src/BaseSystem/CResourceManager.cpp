#include "CResourceManager.h"
#include "CModel.h"
#include "CModelX.h"
#include "CTexture.h"

//�e���v���[�g�̑O�錾
template CModel* CResourceManager::Load(std::string name, std::string path);
template CModelX* CResourceManager::Load(std::string name, std::string path);
template CTexture* CResourceManager::Load(std::string name, std::string path);
template CModel* CResourceManager::Load(std::string path);
template CModelX* CResourceManager::Load(std::string path);
template CTexture* CResourceManager::Load(std::string path);
template CModel* CResourceManager::Get(std::string name);
template CModelX* CResourceManager::Get(std::string name);
template CTexture* CResourceManager::Get(std::string name);

//CResourceManager�̃C���X�^���X
CResourceManager* CResourceManager::mpInstance = nullptr;

//�R���X�g���N�^
CResourceManager::CResourceManager()
{
}

//�f�X�g���N�^
CResourceManager::~CResourceManager()
{
	//�ǂݍ��ݍς݂̃��f���f�[�^��j��
	for (auto& res : mResources)
	{
		delete res.second;
	}
	mResources.clear();

	mpInstance = nullptr;
}

//�C���X�^���X�擾
CResourceManager* CResourceManager::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CResourceManager();
	}
	return mpInstance;
}

//�C���X�^���X��j��
void CResourceManager::ClearInstance()
{
	SAFE_DELETE(mpInstance);
}

// ���\�[�X�ǂݍ���
template <class T>
T* CResourceManager::Load(std::string name, std::string path)
{
	// ���Ƀ��\�[�X���ǂݍ��ݍς݂ł���΁A
	// �ǂݍ��ݍς݂̃��\�[�X��Ԃ�
	auto& list = Instance()->mResources;
	auto find = list.find(name);
	if (find != list.end())
	{
		return dynamic_cast<T*>(find->second);
	}

	// ���\�[�X�ǂݍ���
	CResource* res = new T();
	if (res == nullptr) return nullptr;
	if (!res->Load(path))
	{
		// �ǂݍ��ݎ��s
		delete res;
		return nullptr;
	}

	// ���\�[�X�̃��X�g�ɒǉ�
	list.insert(make_pair(name, res));

	// �ǂݍ��񂾃��\�[�X��Ԃ�
	return dynamic_cast<T*>(res);
}

// ���\�[�X�ǂݍ���
template <class T>
T* CResourceManager::Load(std::string path)
{
	return Load<T>(path, path);
}

// �ǂݍ��ݍς݂̃��\�[�X���擾
template <class T>
T* CResourceManager::Get(std::string name)
{
	// ���\�[�X���ǂݍ��ݍς݂łȂ���΁A
	// nullptr��Ԃ�
	auto& list = mpInstance->mResources;
	auto find = list.find(name);
	if (find == list.end()) return nullptr;

	// �ǂݍ���ł��郊�\�[�X��Ԃ�
	return dynamic_cast<T*>(find->second);
}