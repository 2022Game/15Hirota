#include "CBootMenuScene.h"
#include "CText.h"
#include "CInput.h"
#include "CSceneManager.h"

// �R���X�g���N�^
CBootMenuScene::CBootMenuScene()
	: CSceneBase(EScene::eBootMenu)
	, mSelectIndex(0)
{
	// ���j���[��񃊃X�g���쐬
	mMenuInfoList =
	{
		{ "�����C��", EScene::eNone },
		{ "�^�C�g�����", EScene::eTitle },
		{ "�Q�[�����", EScene::eGame },
		{ "�X�^�b�t���[�����",EScene::eStuffedRoll},
		{ "", EScene::eNone },
		{ "���f�o�b�O", EScene::eNone },
		{ "�Փ˔���e�X�g", EScene::eColTest },
	};

	// ��Ԑ擪�̍��ڂ��I���ł��Ȃ����ڂł���΁A���̍��ڂ������I���ɕύX
	if (mMenuInfoList[mSelectIndex].scene == EScene::eNone)
	{
		SelectNextMenu();
	}
}

// �f�X�g���N�^
CBootMenuScene::~CBootMenuScene()
{
}

// �V�[���ǂݍ���
void CBootMenuScene::Load()
{
	// �N�����j���[�͔w�i���F
	System::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// ���j���[�\���p�̃e�L�X�g��ǉ�
	mpText = new CText
	(
		nullptr, 24,
		CVector2(100.0f, 100.0f),
		CVector2(WINDOW_WIDTH, WINDOW_HEIGHT),
		CColor::white
	);
}

// ���̍��ڂ�I��
void CBootMenuScene::SelectNextMenu()
{
	// �I���\�ȍ��ڂ�����܂ŁA���֐i�߂�
	// �ieNone�̍��ڂ͑I��s�j
	while (true)
	{
		mSelectIndex = (mSelectIndex + 1) % mMenuInfoList.size();
		if (mMenuInfoList[mSelectIndex].scene != EScene::eNone)
		{
			break;
		}
	}
}

// �O�̍��ڂ�I��
void CBootMenuScene::SelectPrevMenu()
{
	// �I���\�ȍ��ڂ�����܂ŁA�O�ɖ߂�
	// �ieNone�̍��ڂ͑I��s�j
	while (true)
	{
		mSelectIndex = (mSelectIndex - 1 + mMenuInfoList.size()) % mMenuInfoList.size();
		if (mMenuInfoList[mSelectIndex].scene != EScene::eNone)
		{
			break;
		}
	}
}

// �X�V
void CBootMenuScene::Update()
{
	// �u���v�L�[�őO�̍��ڂɖ߂�
	if (CInput::PushKey(VK_UP))
	{
		SelectPrevMenu();
	}
	// �u���v�L�[�Ŏ��̍��ڂ֐i�߂�
	else if (CInput::PushKey(VK_DOWN))
	{
		SelectNextMenu();
	}

	// �\�����郁�j���[�����e�L�X�g�ɐݒ�
	std::string str = "";
	int size = mMenuInfoList.size();
	for (int i = 0; i < size; i++)
	{
		MenuInfo& info = mMenuInfoList[i];
		str += (i == mSelectIndex) ? ">> " : "   ";
		str += info.name + "\n";
	}
	mpText->SetText(str.c_str());

	// �uEnter�v�L�[�������́A�uSPACE�v�L�[����������A
	// �I���������j���[�̃V�[���ֈڍs
	if (CInput::PushKey(VK_RETURN) || CInput::PushKey(VK_SPACE))
	{
		MenuInfo& select = mMenuInfoList[mSelectIndex];
		CSceneManager::Instance()->LoadScene(select.scene);
	}
}