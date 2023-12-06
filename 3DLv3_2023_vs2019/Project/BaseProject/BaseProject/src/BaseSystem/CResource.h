#pragma once
class CResourceManager;

// ���\�[�X�Ǘ�����N���X�̃x�[�X�N���X
class CResource
{
	friend CResourceManager;

public:
	// �Q�ƃJ�E���g���Z
	void Referenced();
	// ���\�[�X���
	virtual void Release();

protected:
	// �R���X�g���N�^
	CResource();
	// �f�X�g���N�^
	virtual ~CResource();
	// ���\�[�X�ǂݍ���
	virtual bool Load(std::string path) = 0;

	int mReferenceCount;	// �Q�ƃJ�E���g
};